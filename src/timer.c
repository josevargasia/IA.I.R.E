/* ************************************************************************** */
/**
 * @file timer.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing Timers driver.
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

void timer_init(void){
    timer_ID4_init(1);
}

void timer_ID4_init (uint16_t timer4_period_ms){ //timer4_period_ms <= 100 ms
    /* clock source set to the internal instruction cycle
     * PR4 = (timer4_period_ms * SYS_CLK_BUS_PERIPHERAL)/(TCKPS)    timer4_period_ms <= 100 ms
     * for 1 ms -> PR4 = (1/1000) *(SYS_CLK_BUS_PERIPHERAL/TCKPS)
     * PR4 = timer4_period_ms * ((SYS_CLK_BUS_PERIPHERAL/1000)/TCKPS)
     */
    T4CON = 0x00;                               // Stops the Timer and reset control reg.
    TMR4 = 0;                                   // Clear contents of the timer register
    PR4 =  timer4_period_ms * (SYS_CLK_BUS_PERIPHERAL/(256*1000));  //    
    T4CONbits.TCKPS = 0b111;                    // 111 = 256, Timer Input Clock Prescale Select bits
    T4CONbits.TCS = 0;                          // Set internal clock source 
    IPC4bits.T4IP = 2;                          // Interrupt priority
    IPC4bits.T4IS = 0;                          // Interrupt sub-priority
    IFS0bits.T4IF = 0;                          // Clear the Timer interrupt status flag
    IEC0bits.T4IE = 1;                          // Enable Timer interrupts
    T4CONbits.TON = 1;                          // Start Timer
}

/* *****************************************************************************
 End of File
 */
