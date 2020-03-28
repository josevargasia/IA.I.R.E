/* ************************************************************************** */
/**
 * @file pwm.c
 * @author Ingenierķa Apropiada
 * @date 26/03/2020
 * @brief File containing PWM driver.
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

void pwm_init(void){
    pwm_ID1_init();
}

void pwm_ID1_init(void){
    // Pin
    
    // Configuration
    OC1CON = 0;
    
    OC1CONbits.OCM = 0b110 ;    // PWM mode
    OC1CONbits.OCTSEL = 0;      // Timer2 is the clock source
    OC1RS = 50;
    OC1R = 50;
    
    OC1CONbits.ON = 1;          // ON PWM
}
/* *****************************************************************************
 End of File
 */
