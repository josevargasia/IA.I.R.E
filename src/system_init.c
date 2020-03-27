/* ************************************************************************** */
/**
 * @file system_init.c
 * @author Ingenierķa Apropiada
 * @date 26/03/2020
 * @brief File containing system initializations.
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


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void system_init (void){
    
    // Ports
    ports_init();
    
    // Timer
    timer_init();
    
    // PWM
    PWM1_init();
    
    // I2C
    i2c_init();
    
    // SCI
    sci_init();
    
    // ADC
    adc_init();
    adc_set_ports(2, PORT_AN4 | PORT_AN5);
    
    // Global Interrupt
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    __builtin_enable_interrupts();
    
    // APP init
    APP_init();
}

void ports_init (void){
    
    // GPIO
    TEST_LEDStateIOSet(PIN_OUT);
    TEST_LEDStateSet(0);
    
    PWM1StateIOSet(PIN_OUT);
    PWM1StateSet(0);
    
    // ADC
    ANSELBbits.ANSB4 = 0;   // Turn ON Anlog functions in port RB4 - AN4
    ANSELBbits.ANSB5 = 0;   // Turn ON Anlog functions in port RB5 - AN5
    
    // Ports - Peripheral Pin Select
    // UART1
    RPA15Rbits.RPA15R = 0b0011; //Assign RPA15 pin as Output pin for U1TX  
    U1RXRbits.U1RXR = 0b1101;   //Assign RPA14 pin as Input pin for U1RX
  
}


/* *****************************************************************************
 End of File
 */
