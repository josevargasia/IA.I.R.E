/* ************************************************************************** */
/**
 * @file mg811.cpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing MG811 driver.
 */
/* ************************************************************************** */

#include "system_definitions.hpp"

uint8_t index_samples_ppm_CO2 = 0;             /**< Index of CO2 ppm samples vector. */
uint32_t samples_ppm_CO2[NUMBER_SAMPLES_CO2];  /**< Stores the ppm CO2 ppm samples. */
uint32_t value_ppm_CO2;                        /**< Calculated CO2 ppm value. */
bool flag_CO2 = true;                          /**< Flag for average. */
float CO2_Zero_Point_Volt;                     /**< Define the output of the sensor in volts when the concentration of CO2 is 400PPM. */
float CO2Curve[3] = {2.602, CO2_Zero_Point_Volt, ((float)REACTION_VOLTGAE/(2.602-3))};  /**< Data format:{ x, y, slope}, a line is formed which is "approximately equivalent" to the original curve. */

void get_sample_ppm_CO2(void) { /**< Calculate the CO2 ppm value. */
    /**< Input:   volts - MG811 output measured in volts*/
    /**< Output:  ppm of the target gas */
    /**< Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.*/
    
    volatile float var1 = (float)(((float)adcData.values_2_prom[1]/1000)/(float)DC_GAIN);        
    volatile float var2 = (float)((var1-(CO2_Zero_Point_Volt/(float)DC_GAIN))/CO2Curve[2] + CO2Curve[0]);

    if (var1 >= (CO2_Zero_Point_Volt/(float)DC_GAIN) ) {
        samples_ppm_CO2[index_samples_ppm_CO2++] = 400;
    } else {
        samples_ppm_CO2[index_samples_ppm_CO2++] = (uint32_t)(pow(10, (float)(var2)));
    }

    value_ppm_CO2 = 0;
    if(flag_CO2){
        for (int i=0; i<index_samples_ppm_CO2; i++) value_ppm_CO2 += samples_ppm_CO2[i];
        value_ppm_CO2 /= index_samples_ppm_CO2;
        if (index_samples_ppm_CO2>=NUMBER_SAMPLES_CO2) flag_CO2 = false;
    } else {
        for (int i=0; i<NUMBER_SAMPLES_CO2; i++) value_ppm_CO2 += samples_ppm_CO2[i];
        value_ppm_CO2 /= NUMBER_SAMPLES_CO2;
    }
    if (index_samples_ppm_CO2>=NUMBER_SAMPLES_CO2) index_samples_ppm_CO2 = 0;
}