/* ************************************************************************** */
/**
 * @file adc.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */

#include <esp_adc_cal.h>
#include "system_definitions.hpp"

#define REF_VOLTAGE 3600  /**< ADC reference voltage in mV. */

esp_adc_cal_characteristics_t *adc_chars = new esp_adc_cal_characteristics_t; /**< ESP characteristics. */

esp_adc_cal_value_t val_type;   /**< ESP characterize. */

ADC_DATA adcData;   /**< Manage all variables that ADC driver can use. */

void adc_init(void){
    // Calibration function
    val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, REF_VOLTAGE, adc_chars);
    adcData.state = ADC_STATE_INIT;
}

void adc_get_samples(void){
    
    adcData.values_mv[0] = analogRead_cal(ADC_PRESS_SENSOR, ADC_ATTEN_DB_11);
    adcData.values_mv[1] = analogRead_cal(ADC_CO2_SENSOR, ADC_ATTEN_DB_11);
    adcData.values_mv[2] = analogRead_cal(ADC_FLOW1_SENSOR, ADC_ATTEN_DB_11);
    adcData.values_mv[3] = analogRead_cal(ADC_TEMP1_SENSOR, ADC_ATTEN_DB_11);

    /*
    adcData.values[0] = analogRead(ADC_PRESS_SENSOR);
    adcData.values[1] = analogRead(ADC_CO2_SENSOR);
    
    adcData.values_mv[0] = (adcData.values[0]*3600)/4095;
    adcData.values_mv[1] = (adcData.values[1]*3300)/4095;
    */  

    adcData.values_2[0][adcData.values_2_count] = adcData.values_mv[0];
    adcData.values_2[1][adcData.values_2_count] = adcData.values_mv[1];
    adcData.values_2[2][adcData.values_2_count] = adcData.values_mv[2];
    adcData.values_2[3][adcData.values_2_count] = adcData.values_mv[3];
    
    if(++adcData.values_2_count >= ADC_MAX_NUM_SAMPLE_PROM){
        adcData.values_2_count = 0;
    }
}

void adc_get_sample_average(void){
    
    adcData.values_2_prom[0] = 0;
    adcData.values_2_prom[1] = 0;
    adcData.values_2_prom[2] = 0;
    adcData.values_2_prom[3] = 0;
    int i;
    for(i = 0; i < ADC_MAX_NUM_SAMPLE_PROM; i++){
        adcData.values_2_prom[0] += adcData.values_2[0][i];
        adcData.values_2_prom[1] += adcData.values_2[1][i];
        adcData.values_2_prom[2] += adcData.values_2[2][i];
        adcData.values_2_prom[3] += adcData.values_2[3][i];
    }
    adcData.values_2_prom[0] /= ADC_MAX_NUM_SAMPLE_PROM; 
    adcData.values_2_prom[1] /= ADC_MAX_NUM_SAMPLE_PROM; 
    adcData.values_2_prom[2] /= ADC_MAX_NUM_SAMPLE_PROM; 
    adcData.values_2_prom[3] /= ADC_MAX_NUM_SAMPLE_PROM; 
    get_sample_ppm_CO2();  
    
}

void adc_task(void){
    switch ( adcData.state )
    {
        case ADC_STATE_INIT:
        {   
            adcData.delay_samples = 1;
            adcData.state = ADC_STATE_TASK_HANDLER;
            break;
        }
        case ADC_STATE_TASK_HANDLER:
        {   
            if(adcData.delay_samples == 0){
                adc_get_samples();
                adcData.delay_samples = 1;
            }
            break;
        }
        default:
        {
            adcData.state = ADC_STATE_INIT;
            break;
        }
    }
}

uint32_t analogRead_cal(uint8_t channel, adc_atten_t attenuation) {
  adc1_channel_t channelNum;

  /*
     Set number of cycles per sample
     Default is 8 and seems to do well
     Range is 1 - 255
   * */
  // analogSetCycles(uint8_t cycles);

  /*
     Set number of samples in the range.
     Default is 1
     Range is 1 - 255
     This setting splits the range into
     "samples" pieces, which could look
     like the sensitivity has been multiplied
     that many times
   * */
  // analogSetSamples(uint8_t samples);

  switch (channel) {
    case (36):
      channelNum = ADC1_CHANNEL_0;
      break;

    case (39):
      channelNum = ADC1_CHANNEL_3;
      break;

    case (34):
      channelNum = ADC1_CHANNEL_6;
      break;

    case (35):
      channelNum = ADC1_CHANNEL_7;
      break;

    case (32):
      channelNum = ADC1_CHANNEL_4;
      break;

    case (33):
      channelNum = ADC1_CHANNEL_5;
      break;
    
    default:
      channelNum = ADC1_CHANNEL_0;
      break;
  }

  adc1_config_channel_atten(channelNum, attenuation);
  return esp_adc_cal_raw_to_voltage(analogRead(channel), adc_chars);
}
