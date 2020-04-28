/* ************************************************************************** */
/**
 * @file adc.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */

#include <Arduino.h>
#include <esp_adc_cal.h>


#define ADC_MAX_NUM_SAMPLE_PROM   8        /**< Maximum number of samples to calculate average. */


const int ADC_PRESS_SENSOR = 35;            /**< ADC sensor pin. */
const int ADC_CO2_SENSOR = 34;              /**< ADC sensor pin. */
const int ADC_FLOW1_SENSOR = 32;            /**< ADC sensor pin. */
const int ADC_TEMP1_SENSOR = 39;

/**
* @brief Use enum for define states of states machine in ADC task.
*/
typedef enum
{
    ADC_STATE_INIT=0,           /**< Initial state. */
    ADC_STATE_TASK_HANDLER,     /**< Task run state. */
    ADC_STATE_DUMMY,            /**< Dummy state. */
} ADC_STATES;

/**
 * @brief ADC data structure.
 */
typedef struct
{
    ADC_STATES state;

    uint32_t values[5];         /**< Save values sampled for ADC. */
    uint32_t values_mv[5];      /**< Save values sampled for ADC in mV. */
    
    uint32_t values_2[5][ADC_MAX_NUM_SAMPLE_PROM]; /**< Save values sampled for avergae. */
    uint32_t values_2_count;    /**< Count samples for avergae. */
    uint32_t values_2_prom[5];  /**< Save the average of sample. */

    uint16_t delay_samples;     /**< Timeout to get sample. */

} ADC_DATA;

extern ADC_DATA adcData;    /**< Manage all variables that ADC driver can use. */

/**
 * @brief Function to ged ADC samples.
 * 
 * Get ADC samples in mV and put into structure ADC_DATA.
 * 
 */
void adc_get_samples(void);

/**
 * @brief Function to ged ADC samples average.
 * @code
 *      adc_get_sample_average();
 * @endcode
 */
void adc_get_sample_average(void);

/**
 * @brief Function to get ADC value in mV.
 * @param  channel Number of pin to read
 * @param  attenuation Attenuation of ADC configured
 */
uint32_t analogRead_cal(uint8_t channel, adc_atten_t attenuation);

/**
 * @brief Setup ADC task. 
 */
void adc_init(void);

/**
 * @brief ADC task handler.
 */
void adc_task(void);

