/* ************************************************************************** */
/**
 * @file mg811.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing MG811 driver.
 */
/* ************************************************************************** */


#ifndef _MG811_H    /* Guard against multiple inclusion */
#define _MG811_H


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

    #define DC_GAIN             8.5     /**< Define the DC gain of amplifier. */
    #define ZERO_POINT_VOLTAGE  0.306   /**< Define the output of the sensor in volts when the concentration of CO2 is 400PPM. */
    #define REACTION_VOLTGAE    0.030   /**< Define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2. */
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
    extern uint32_t value_ppm_CO2;  /**< Calculated CO2 ppm value. */
    extern float CO2Curve[3];       /**< Data format:{ x, y, slope}, a line is formed which is "approximately equivalent" to the original curve. */
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
     /**
     * @brief Function to get ppm CO2.
     * 
     * Calculate the CO2 ppm value.
     * 
     */
    void get_sample_ppm_CO2(void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
