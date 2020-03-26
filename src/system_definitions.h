/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Ingeniería Apropiada S.A.S.

  @File Name
    system_definitions.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SYSTEM_DEFINITIONS_H    /* Guard against multiple inclusion */
#define _SYSTEM_DEFINITIONS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

//#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <xc.h>             /* Defines special funciton registers, CP0 regs  */
#include <sys/attribs.h>
#include <cp0defs.h>
#include <plib.h>

#include "main.h"
#include "system_init.h"
#include "delay.h"
#include "interrupt.h"
#include "i2c.h"
#include "sci.h"
#include "adc.h"
#include "timer.h"
#include "app.h"



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /* ************************************************************************** */
    #define SYS_CLK_FREQ            80000000ul  // 80MHz
    #define SYS_CLK_BUS_PERIPHERAL  40000000ul  // 40MHz

    #define SYS_CLK_INTERNAL_FREQ   8000000ul  // 8MHz

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_DEFINITIONS_H */

/* *****************************************************************************
 End of File
 */
