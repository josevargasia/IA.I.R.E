/* ************************************************************************** */
/**
 * @file adc.h
 * @author Ingenier�a Apropiada
 * @date 26/03/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */

#ifndef _ADC_HPP    /* Guard against multiple inclusion */
#define _ADC_HPP


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <Arduino.h>
#include <esp_adc_cal.h>

/* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    #define ADC_MAX_NUM_SAMPLE_PROM  30//30        /**< maximum number of samples to calculate average. */
    
    
    const int ADC_PRESS_SENSOR = 35;
    const int ADC_CO2_SENSOR = 34;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    typedef enum
    {
        /* Application's state machine's initial state. */
        ADC_STATE_INIT=0,           /**< Initial state. */
        ADC_STATE_TASK_HANDLER,
        ADC_STATE_DUMMY,
    } ADC_STATES;

    /**
     * @brief ADC data structure.
     */
    typedef struct
    {
        ADC_STATES state;

        uint32_t values[5];         /**< Save values sampled for ADC. */
        uint32_t values_mv[5];      /**< Save values sampled for ADC in mV. */
        
        uint32_t values_2[5][ADC_MAX_NUM_SAMPLE_PROM]; /**< Save values sampled for avergae. */
        uint32_t values_2_count;    /**< Count samples for avergae. */
        uint32_t values_2_prom[5];  /**< Save the average of sample. */

        uint16_t delay_samples;

    } ADC_DATA;

    extern ADC_DATA adcData;    /**< Manage all variables that ADC driver can use. */


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    /**
     * @brief Function to ged ADC samples.
     * 
     * Get ADC samples in mV and put into structure ADC_DATA.
     * 
     */
    void adc_get_samples(void);
    
    /**
     * @brief Function to ged ADC samples average.
     * @code
     *      adc_get_sample_average();
     * @endcode
     */
    void adc_get_sample_average(void);

    uint32_t analogRead_cal(uint8_t channel, adc_atten_t attenuation);

    void adc_init(void);

    void adc_task(void);

#endif /* _ADC_H */