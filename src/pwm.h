/* ************************************************************************** */
/**
 * @file pwm.h
 * @author Ingenierķa Apropiada
 * @date 26/03/2020
 * @brief File containing PWM driver.
 */
/* ************************************************************************** */

#ifndef _PWM_H    /* Guard against multiple inclusion */
#define _PWM_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

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




    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    void pwm_init(void);
    void pwm_ID5_init(void);
    void pwm_ID5_duty_set(uint8_t duty);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PWM_H */

/* *****************************************************************************
 End of File
 */
