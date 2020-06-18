/* ************************************************************************** */
/** Library for application of PWM
 * @file pwm.cpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing PWM driver.
 */
/* ************************************************************************** */


#include "Arduino.h"

#define H_BRIDGE_ENABLE      0
#define H_BRIDGE_DISABLE     1
#define PWM_PIN              5
#define PWM_ENABLE_PIN       18
#define PWM_BREAK_PIN        15
#define PWM_BREAK_ON         0
#define PWM_BREAK_OFF        1

/**
 * @brief PWM data structure.
 */
typedef struct{
    int pwmFreq;        /**< PWM Frequency. */
    int pwmLedCh;       /**< PWM Channel. */
    int pwmResolution;  /**< PWM Resolution. */
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
