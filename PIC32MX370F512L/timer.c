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
    timer_ID4_init_ms(1);       // For timeouts
    timer_ID3_init_us(100);     // For ADC
    timer_ID2_init_us(33);     // For PWM1
}

void timer_ID4_init_ms (uint16_t period_ms){ 
    /* clock source set to the internal instruction cycle
     * PR4 = (period_ms * SYS_CLK_BUS_PERIPHERAL)/(TCKPS)   
     * for 1 ms -> PR4 = (1/1000) *(SYS_CLK_BUS_PERIPHERAL/TCKPS)
     * PR4 = period_ms * ((SYS_CLK_BUS_PERIPHERAL/1000)/TCKPS)
     */
    T4CON = 0x00;                               // Stops the Timer and reset control reg.
    TMR4 = 0;                                   // Clear contents of the timer register
    PR4 =  period_ms * (SYS_CLK_BUS_PERIPHERAL/(256*1000));  //    
    T4CONbits.TCKPS = 0b111;                    // 111 = 256, Timer Input Clock Prescale Select bits
    T4CONbits.TCS = 0;                          // Set internal clock source 
    IPC4bits.T4IP = 3;                          // Interrupt priority
    IPC4bits.T4IS = 0;                          // Interrupt sub-priority
    IFS0bits.T4IF = 0;                          // Clear the Timer interrupt status flag
    IEC0bits.T4IE = 1;                          // Enable Timer interrupts
    T4CONbits.TON = 1;                          // Start Timer
}

void timer_ID3_init_us (uint16_t period_us){ 
    /* clock source set to the internal instruction cycle
     * PR3 = (period_us * SYS_CLK_BUS_PERIPHERAL)/(TCKPS)    
     * for 1 us -> PR3 = (1/1000000) *(SYS_CLK_BUS_PERIPHERAL/TCKPS)
     * PR3 = period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/TCKPS)
     */
    
    T3CON = 0x00;                               // Stops the Timer and reset control reg.
    TMR3 = 0;                                   // Clear contents of the timer register
    PR3 =  period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/8);  //    
    T3CONbits.TCKPS = 0b011;                    // 011 = 8, Timer Input Clock Prescale Select bits
    T3CONbits.TCS = 0;                          // Set internal clock source 
    IPC3bits.T3IP = 2;                          // Interrupt priority
    IPC3bits.T3IS = 0;                          // Interrupt sub-priority
    IFS0bits.T3IF = 0;                          // Clear the Timer interrupt status flag
    IEC0bits.T3IE = 1;                          // Enable Timer interrupts
    T3CONbits.TON = 1;                          // Start Timer
}

void timer_ID2_init_us (uint16_t period_us){ 
    /* clock source set to the internal instruction cycle
     * PR2 = (period_us * SYS_CLK_BUS_PERIPHERAL)/(TCKPS)    
     * for 1 us -> PR2 = (1/1000000) *(SYS_CLK_BUS_PERIPHERAL/TCKPS)
     * PR2 = period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/TCKPS)
     */
    
    T2CON = 0x00;                               // Stops the Timer and reset control reg.
    TMR2 = 0;                                   // Clear contents of the timer register
    PR2 =  period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/4);  //    
    T2CONbits.TCKPS = 0b010;                    // 010 = 4, Timer Input Clock Prescale Select bits
    T2CONbits.TCS = 0;                          // Set internal clock source 
//    IPC2bits.T2IP = 2;                          // Interrupt priority
//    IPC2bits.T2IS = 0;                          // Interrupt sub-priority
//    IFS0bits.T2IF = 0;                          // Clear the Timer interrupt status flag
//    IEC0bits.T2IE = 1;                          // Enable Timer interrupts
    T2CONbits.TON = 1;                          // Start Timer
}

void timer_ID2_set_frecuency(uint32_t frec){
    
    uint32_t period_us = 1000000/frec; 
    
    PR2 =  period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/4);  //
}

/* *****************************************************************************
 End of File
 */
