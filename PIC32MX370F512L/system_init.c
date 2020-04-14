/* ************************************************************************** */
/**
 * @file system_init.c
 * @author Ingeniería Apropiada
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
    pwm_init();
    
    // I2C
    i2c_init();
    
    // SCI
    sci_init();
    
    // ADC
    adc_init();
    adc_set_ports(2, PORT_AN4 | PORT_AN5);
    
    // PID
    pid_init();
    
    // Global Interrupt
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    __builtin_enable_interrupts();
    
    // APP init
    APP_init();
    
    // MAX30102 Init
    MAX30102_Init();
}

void ports_init (void){
    
    // GPIO OUT
    TEST_LEDStateIOSet(PIN_OUT);
    TEST_LEDStateSet(0);
    
    HBridge_IN1_StateIOSet(PIN_OUT);
    HBridge_IN1_StateSet(0);
    
    HBridge_IN2_StateIOSet(PIN_OUT);
    HBridge_IN2_StateSet(0);
    
    TRIG_StateIOSet(PIN_OUT);
    TRIG_StateSet(0);
    
    
    // GPIO IN
    STATE_BLUETOOTHStateIOSet(PIN_IN);
    
    // ADC
    ANSELBbits.ANSB4 = 0;   // Turn ON Anlog functions in port RB4 - AN4
    ANSELBbits.ANSB5 = 0;   // Turn ON Anlog functions in port RB5 - AN5
    
    // Ports - Peripheral Pin Select
    // UART1
//    RPA15Rbits.RPA15R = 0b0011; //Assign RPA15 pin as Output pin for U1TX  
//    U1RXRbits.U1RXR = 0b1101;   //Assign RPA14 pin as Input pin for U1RX
    
    // UART5
    RPE9Rbits.RPE9R = 0b0100;   //Assign RPE9 pin as Output pin for U5TX  
    U5RXRbits.U5RXR = 0b1101;   //Assign RPE8 pin as Input pin for U5RX
 
    // PWM
    RPB0Rbits.RPB0R = 0b1011;   //Assign RPD2 pin as Output pin for OC5
     
    RPD2Rbits.RPD2R = 0b1011;   //Assign RPD2 pin as Output pin for OC3
}


/* *****************************************************************************
 End of File
 */
