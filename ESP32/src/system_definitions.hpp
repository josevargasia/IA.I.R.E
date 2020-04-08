/* ************************************************************************** */
/**
 * @file system_definitions.hpp
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing main system definitions.
 */
/* ************************************************************************** */


#ifndef _SYSTEM_DEFINITIONS_HPP    /* Guard against multiple inclusion */
#define _SYSTEM_DEFINITIONS_HPP


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
    
#include <Arduino.h>             /* Defines special funciton registers, CP0 regs  */
// #include <sys/attribs.h>

// #include "main.h"
// #include "system_init.hpp"
// #include "delay.hpp"
// #include "interrupt.hpp"
// #include "i2c.hpp"
// #include "sci.hpp"
#include "adc.hpp"
// #include "timer.hpp"
// #include "app.hpp"
// #include "mg811.hpp"
// #include "bluetooth.hpp"
// #include "hbridge.hpp"
// #include "pid.hpp"
#include "mpx5010.hpp"
#include "respira.hpp"


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
#endif /* _SYSTEM_DEFINITIONS_H */

/* *****************************************************************************
 End of File
 */
