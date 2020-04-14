/* ************************************************************************** */
/** Library for application of MPX5010 Pressure Sensor
 * @file mpx5010.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing MPX5010 sensor driver.
 */
/* ************************************************************************** */

#ifndef _MPX5010_HPP    /* Guard against multiple inclusion */
#define _MPX5010_HPP


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <Arduino.h>


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
    float measValue; /**< Saves the pressure measured value. */
    uint16_t valuesWindow[PRESS_WINDOW_SIZE]; /**< Buffer with the last measured ADC values. */

} PRESS_DATA;

extern PRESS_DATA pressData;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************


// void pressure_get_value(uint16_t intVal, uint8_t unit);
// void pressure_prom_int_values(uint16_t *addValue);

/**
 * @brief Converts pressures values to miliVolts values for MPX5010 sensor
 * @code 
 *      my_mv_value = pressure2mv(my_press_value);
 * @endcode
 * @param pressure Float that represents a pressure value.
 * @return The function returns a float value that represents the mV value for the entered pressure in the MPX5010 sensor.
 */
float pressure2mv(float pressure);

/**
 * @brief Converts miliVolts values to pressures values for MPX5010 sensor
 * @code 
 *      my_press_value = mv2pressure(my_mv_value)
 * @endcode
 * @param mv Float that represents a mv value.
 * @return The function returns a float value that represents the pressure value for the entered mv in the MPX5010.
 */
float mv2pressure(float mv);


#endif /* MPX5010_HPP */

/* *****************************************************************************
 End of File
 */
