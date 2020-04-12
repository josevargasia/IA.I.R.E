#include "Arduino.h"

typedef struct{
    int pwmFreq;
    int pwmLedCh;
    int pwmResolution;
    int pwmPin;
}PWM_DATA;

extern PWM_DATA pwmData;

void pwm_init(void);
void pwm_duty_set(uint32_t duty_value);
void pwm_set_frec(uint32_t frec_value);
