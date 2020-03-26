/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    delay.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _DELAY_H    /* Guard against multiple inclusion */
#define _DELAY_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "system_definitions.h"


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



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************




    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    void delay_us (uint32_t us);
    void delay_ms (uint16_t ms);
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DELAY_H */

/* *****************************************************************************
 End of File
 */
