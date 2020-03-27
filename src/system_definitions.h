/* ************************************************************************** */
/**
 * @file system_definitions.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing main system definitions.
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
    
#include <xc.h>             /* Defines special funciton registers, CP0 regs  */
#include <sys/attribs.h>
#include <cp0defs.h>
#include <plib.h>           /* Include to use PIC32 peripheral libraries      */

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

    #define SYS_CLK_FREQ            80000000ul  /**< System clock configured at 80MHz. */
    #define SYS_CLK_BUS_PERIPHERAL  40000000ul  /**< Peripheral bus clock configured at 40MHz. */

    #define SYS_CLK_INTERNAL_FREQ   8000000ul   /**< Internal system clock configured at 8MHz. */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_DEFINITIONS_H */

/* *****************************************************************************
 End of File
 */
