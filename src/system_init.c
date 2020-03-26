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



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

void system_init (void){
    
    // Ports
    ports_init();
    
    // Global Interrupt
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    __builtin_enable_interrupts();
    
    // Timer
    timer_init();
    
    // PWM
    
    
    // I2C
    i2c_init();
    
    // SCI
    sci_init();
    
    // ADC
    adc_init();
    adc_set_ports(2, PORT_AN4 | PORT_AN5);
    
    // APP init
    APP_init();
}

void ports_init (void){
    
    // GPIO
    TEST_LEDStateIOSet(PIN_OUT);
    TEST_LEDStateSet(0);
    
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
