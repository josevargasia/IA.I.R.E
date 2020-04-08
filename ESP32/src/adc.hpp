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

#include "system_definitions.hpp"

/* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    #define ADC_MAX_NUM_SAMPLE_PROM  30        /**< maximum number of samples to calculate average. */
    
    
    const int ADC_PRESS_SENSOR = 35;
    const int ADC_CO2_SENSOR = 34;

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    
    /**
     * @brief ADC data structure.
     */
    typedef struct
    {
        uint32_t values[5];         /**< Save values sampled for ADC. */
        uint32_t values_mv[5];      /**< Save values sampled for ADC in mV. */
        
        uint32_t values_2[5][ADC_MAX_NUM_SAMPLE_PROM]; /**< Save values sampled for avergae. */
        uint32_t values_2_count;    /**< Count samples for avergae. */
        uint32_t values_2_prom[5];  /**< Save the average of sample. */

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

#endif /* _ADC_H */