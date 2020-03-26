/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
void __ISR(_TIMER_4_VECTOR, ipl2) IntTimer4Handler(void)    // 1ms
{
    adc_get_samples();
    
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
    
    IFS0bits.T4IF = 0; //Reset Timer4 interrupt flag and Return from ISR
}

void __ISR(_UART1_VECTOR, ipl2) IntUart1Handler(void)
{
    /* Reading the transmit interrupt flag */
    if(IFS1bits.U1TXIF == 1)
    {
        char data;
        while(U1STAbits.UTXBF);
        if(circBuffPop_sci(&data, BUFFER_TX_SCI_ID1)){
			U1TXREG = data;
            U1STAbits.OERR = 0;
            IFS1bits.U1TXIF = 0;
        }else{
            IFS1bits.U1TXIF = 0;
            IEC1bits.U1TXIE = 0;
        }
    }
    
    if(IFS1bits.U1RXIF == 1)
    {
        char data;
        data = U1RXREG;
        circBuffPush_sci(data, BUFFER_RX_SCI_ID1);
        /* Clear up the interrupt flag */
        IFS1bits.U1RXIF = 0;
    }
}

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************



/* *****************************************************************************
 End of File
 */
