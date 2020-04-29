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
#define REACTION_VOLTGAE    0.030  /**< Define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2. */
#define NUMBER_SAMPLES_CO2  100    /**< Defines the number of samples for the average CO2 ppm. */

extern uint8_t index_samples_ppm_CO2;  /**< Index of CO2 ppm samples vector. */
extern uint32_t samples_ppm_CO2[NUMBER_SAMPLES_CO2];  /**< Stores the CO2 ppm samples. */
extern uint32_t value_ppm_CO2;     /**< Calculated CO2 ppm value. */
extern bool flag_CO2;              /**< Flag for average. */
extern float CO2_Zero_Point_Volt;  /**< Define the output of the sensor in volts when the concentration of CO2 is 400PPM. */
extern float CO2Curve[3];          /**< Data format:{ x, y, slope}, a line is formed which is "approximately equivalent" to the original curve. */      

/**
 * @brief Function to get ppm CO2.
 * Calculate the CO2 ppm value.
 */
void get_sample_ppm_CO2(void);