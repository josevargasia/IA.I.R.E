/* ************************************************************************** */
/**
 * @file interrupt.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing interrupt handler routines.
 */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/**
* @brief Timer 3 interrupt handler routine
*/
void __ISR(_TIMER_3_VECTOR, ipl2) IntTimer3Handler(void)    // 500us
{
    adc_get_samples();
    
    IFS0bits.T3IF = 0; //Reset Timer3 interrupt flag and Return from ISR
}

/**
* @brief Timer 4 interrupt handler routine
*/
void __ISR(_TIMER_4_VECTOR, ipl3) IntTimer4Handler(void)    // 1ms
{    
    
//    adc_get_samples();
    
    appData.timeout_1seg++;
    if(appData.timeout_1seg >= 1000){
        appData.timeout_1seg = 0;
        
        if(appData.test_led_timeout > 0){
            appData.test_led_timeout = 0;
            TEST_LEDStateSet(1);
        }else{
            appData.test_led_timeout++;
            TEST_LEDStateSet(0);
        }
        
    }
    
    if(appData.test_timeout)
        appData.test_timeout--;
    
    if(bluetoothData.timeout)
        bluetoothData.timeout--;
    
    if(pidData.timeout)
        pidData.timeout--;
    
    if(respiraData.t_out_inps)
        respiraData.t_out_inps--;
    
    if(respiraData.t_out_exp)
        respiraData.t_out_exp--;
    
    if(MAX30102.timeout_wait_sample)
        MAX30102.timeout_wait_sample--;
    
    IFS0bits.T4IF = 0; //Reset Timer4 interrupt flag and Return from ISR
}

/**
* @brief UART 5 TX and RX interrupt handler routine
*/
void __ISR(_UART_5_VECTOR, ipl1) IntUart5Handler(void)
{
    /* Reading the transmit interrupt flag */
    if(IFS2bits.U5TXIF == 1)
    {
        char data;
        while(U5STAbits.UTXBF);
        if(circBuffPop_sci(&data, BUFFER_TX_SCI_ID5)){
			U5TXREG = data;
            U5STAbits.OERR = 0;
            IFS2bits.U5TXIF = 0;
        }else{
            IFS2bits.U5TXIF = 0;
            IEC2bits.U5TXIE = 0;
        }
    }
    
    if(IFS2bits.U5RXIF == 1)
    {
        char data;
        data = U5RXREG;
        circBuffPush_sci(data, BUFFER_RX_SCI_ID5);
        /* Clear up the interrupt flag */
        IFS2bits.U5RXIF = 0;
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */




/* *****************************************************************************
 End of File
 */
