/* ************************************************************************** */
/**
 * @file timer.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing Timers driver.
 */
/* ************************************************************************** */


#ifndef _TIMER_H    /* Guard against multiple inclusion */
#define _TIMER_H


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

    /**
     * @brief Initialize timers configuration
     */
    void timer_init(void);
    
    /**
     * @brief Initialize timer 4 configuration in ms
     * @code
     *      timer_ID4_init_ms(1);  // 1 ms
     * @endcode
     * @param period_ms    Number of miliseconds to set Timer 4 interription, 1ms < period_ms < 100ms
     */
    void timer_ID4_init_ms (uint16_t period_ms);
    
    /**
     * @brief Initialize timer 3 configuration in us
     * @code
     *      timer_ID3_init_us(1);  // 1 us
     * @endcode
     * @param period_us    Number of microseconds to set Timer 3 interription, 1us < period_us < 3200us
     */
    void timer_ID3_init_us (uint16_t period_us);
    
    /**
     * @brief Initialize timer 2 configuration in us
     * @code
     *      timer_ID2_init_us(1);  // 1 us
     * @endcode
     * @param period_us    Number of microseconds to set Timer 2 interription, 1us < period_us < 3200us
     */    
    void timer_ID2_init_us (uint16_t period_us);
    
    /**
     * @brief Set frecuency of PWM ID 5
     * @code
     *      timer_ID2_set_frecuency(10000);  // 10kHz
     * @endcode
     * @param frec    Set frecuency of timer 2 in Hz, 10k < frec < 50k
     */ 
    void timer_ID2_set_frecuency(uint32_t frec);
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _TIMER_H */

/* *****************************************************************************
 End of File
 */
