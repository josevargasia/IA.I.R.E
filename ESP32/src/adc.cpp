/* ************************************************************************** */
/**
 * @file adc.c
 * @author Ingenier�a Apropiada
 * @date 26/03/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "adc.hpp"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

ADC_DATA adcData;

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

void adc_get_samples(void){
        
    adcData.values[0] = analogRead(ADC_PRESS_SENSOR);
    adcData.values[1] = analogRead(ADC_CO2_SENSOR);
    
    adcData.values_mv[0] = (adcData.values[0]*3300)/4095;
    adcData.values_mv[1] = (adcData.values[1]*3300)/4095;
    
    adcData.values_2[0][adcData.values_2_count] = adcData.values_mv[0];
    adcData.values_2[1][adcData.values_2_count++] = adcData.values_mv[1];
    
    if(adcData.values_2_count >= ADC_MAX_NUM_SAMPLE_PROM){
        adcData.values_2_count = 0;
    }
    
}

void adc_get_sample_average(void){
    
    adcData.values_2_prom[0] = 0;
    adcData.values_2_prom[1] = 0;
    int i;
    for(i = 0; i < ADC_MAX_NUM_SAMPLE_PROM; i++){
        adcData.values_2_prom[0] += adcData.values_2[0][i];
        adcData.values_2_prom[1] += adcData.values_2[1][i];
    }
    adcData.values_2_prom[0] /= ADC_MAX_NUM_SAMPLE_PROM; 
    adcData.values_2_prom[1] /= ADC_MAX_NUM_SAMPLE_PROM; 
    // get_sample_ppm_CO2();
    
}
/* *****************************************************************************
 End of File
 */
