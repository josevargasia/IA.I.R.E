/* ************************************************************************** */
/** Library for application of MPX5010 Pressure Sensor
 * 
 * @Company Ingenier�a Apropiada
 * 
 */
/* ************************************************************************** */

#ifndef _MPX5010_HPP    /* Guard against multiple inclusion */
#define _MPX5010_HPP


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.hpp"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define PRESS_WINDOW_SIZE 5 /**< Size of the data buffer for the pressure data*/

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**
 * @Description This type is a structure that contains the variables required 
 * the sensor.
 */
typedef struct
{
    float measValue; /**< Saves the pressure data value. */
    uint16_t valuesWindow[PRESS_WINDOW_SIZE]; /**< Buffer with the last measured ADC values. */
    uint16_t values_mv[5];      /**< Save values sampled for ADC in mV. */
    
    //uint16_t values_2[5][ADC_MAX_NUM_SAMPLE_PROM]; /**< Save values sampled for avergae. */
    uint16_t values_2_count;    /**< Count samples for avergae. */
    uint32_t values_2_prom[5];  /**< Save the average of sample. */

} PRESS_DATA;

extern PRESS_DATA pressData;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************


void pressure_get_value(uint16_t intVal, uint8_t unit);
void pressure_prom_int_values(uint16_t *addValue);
float pressure2mv(float pressure);
float mv2pressure(float mv);


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
