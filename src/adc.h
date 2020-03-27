/* ************************************************************************** */
/**
 * @file adc.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */

#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H


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

    #define ADC_MAX_NUM_SAMPLE_PROM  100        /**< maximum number of samples to calculate average. */
    
    #define PORT_AN0    0b0000000000000001      /**< Set ADC port AN0. */
    #define PORT_AN1    0b0000000000000010      /**< Set ADC port AN1. */
    #define PORT_AN2    0b0000000000000100      /**< Set ADC port AN2. */
    #define PORT_AN3    0b0000000000001000      /**< Set ADC port AN3. */
    #define PORT_AN4    0b0000000000010000      /**< Set ADC port AN4. */
    #define PORT_AN5    0b0000000000100000      /**< Set ADC port AN5. */
    #define PORT_AN6    0b0000000001000000      /**< Set ADC port AN6. */
    #define PORT_AN7    0b0000000010000000      /**< Set ADC port AN7. */
    #define PORT_AN8    0b0000000100000000      /**< Set ADC port AN8. */
    #define PORT_AN9    0b0000001000000000      /**< Set ADC port AN9. */
    #define PORT_AN10   0b0000010000000000      /**< Set ADC port AN10. */
    #define PORT_AN11   0b0000100000000000      /**< Set ADC port AN11. */
    #define PORT_AN12   0b0001000000000000      /**< Set ADC port AN12. */
    #define PORT_AN13   0b0010000000000000      /**< Set ADC port AN13. */
    #define PORT_AN14   0b0100000000000000      /**< Set ADC port AN14. */
    #define PORT_AN15   0b1000000000000000      /**< Set ADC port AN15. */


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
        uint16_t values[5];         /**< Save values sampled for ADC. */
        uint16_t values_mv[5];      /**< Save values sampled for ADC in mV. */
        
        uint16_t values_2[5][1000]; /**< Save values sampled for avergae. */
        uint16_t values_2_count;    /**< Count samples for avergae. */
        uint32_t values_2_prom[5];  /**< Save the average of sample. */

    } ADC_DATA;

    extern ADC_DATA adcData;    /**< Manage all variables that ADC driver can use. */


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Initialize ADC configuration
     */
    void adc_init (void);
    
    /**
     * @brief Configure ANx ports to sample
     * @code
     *      adc_set_ports(2, PORT_AN4 | PORT_AN5);
     * @endcode
     * @param number    Number of ports to sample
     * @param ports     Variable with ports to sample
     */
    void adc_set_ports(uint8_t number, uint32_t ports);
    
    /**
     * @brief Function to ged ADC samples.
     * 
     * Get ADC samples in mV and put into structure ADC_DATA.
     * 
     */
    void adc_get_samples(void);
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ADC_H */

/* *****************************************************************************
 End of File
 */
