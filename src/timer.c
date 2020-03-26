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
