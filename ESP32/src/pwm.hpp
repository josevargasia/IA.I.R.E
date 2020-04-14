/* ************************************************************************** */
/** Library for application of PWM
 * @file pwm.cpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing PWM driver.
 */
/* ************************************************************************** */


#include "Arduino.h"

/**
 * @brief PWM data structure.
 */
typedef struct{
    int pwmFreq;        /**< PWM Frequency. */
    int pwmLedCh;       /**< PWM Channel. */
    int pwmResolution;  /**< PWM Resolution. */
    int pwmPin;         /**< PWM Control Pin. */
    int pwmEnablePin;   /**< PWM Enable Pin. */
}PWM_DATA;

extern PWM_DATA pwmData;

/**
 * @brief Init PWM driver.
 */
void pwm_init(void);

/**
 * @brief PWM setup duty
 * @param  duty_value Integer value for duty in percent.
 */
void pwm_duty_set(uint32_t duty_value);

/**
 * @brief PWM setup frequency
 * @param frec_value Integer value for frequency in Hz.
 */
void pwm_set_frec(uint32_t frec_value);
