/* ************************************************************************** */
/**
 * @file mg811.hpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing MG811 driver.
 */
/* ************************************************************************** */

#include <Arduino.h>


#define DC_GAIN             8.5    /**< Define the DC gain of amplifier. */
#define ZERO_POINT_VOLTAGE  0.236  /**< Define the output of the sensor in volts when the concentration of CO2 is 400PPM. */
#define REACTION_VOLTGAE    0.030  /**< Define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2. */

extern uint32_t value_ppm_CO2;     /**< Calculated CO2 ppm value. */
extern float CO2Curve[3];          /**< Data format:{ x, y, slope}, a line is formed which is "approximately equivalent" to the original curve. */

/**
 * @brief Function to get ppm CO2.
 * Calculate the CO2 ppm value.
 */
void get_sample_ppm_CO2(void);