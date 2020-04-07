/* ************************************************************************** */
/**
 * @file mg811.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing MG811 driver.
 */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

uint32_t value_ppm_CO2; /**< Calculated CO2 ppm value. */
float CO2Curve[3] = {2.602, (float)ZERO_POINT_VOLTAGE, ((float)REACTION_VOLTGAE/(2.602-3))};  /**< Data format:{ x, y, slope}, a line is formed which is "approximately equivalent" to the original curve. */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void get_sample_ppm_CO2(void) { /**< Calculate the CO2 ppm value. */
    /**< Input:   volts - MG811 output measured in volts*/
    /**< Output:  ppm of the target gas */
    /**< Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.*/
    
    volatile float var1 = (float)(((float)adcData.values_2_prom[1]/1000)/(float)DC_GAIN);
        
    volatile float var2 = (float)(((((float)adcData.values_2_prom[1]/1000)/(float)DC_GAIN)-CO2Curve[1])/CO2Curve[2] + CO2Curve[0]);
    
    if ( (var1) >= (float)ZERO_POINT_VOLTAGE ) {
        value_ppm_CO2 = 0;
    } else {
        value_ppm_CO2 = (uint32_t)(pow(10, (float)(var2)));
    }
}

/* *****************************************************************************
 End of File
 */
