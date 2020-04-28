#include "system_definitions.hpp"

PWM_DATA pwmData;

void pwm_init(void){
    pinMode(PWM_ENABLE_PIN,OUTPUT);
    
    pwmData.pwmFreq = 5000;
    pwmData.pwmLedCh = 5;
    pwmData.pwmResolution = 8;

    ledcSetup(pwmData.pwmLedCh,pwmData.pwmFreq,pwmData.pwmResolution);
    ledcAttachPin(PWM_PIN,pwmData.pwmLedCh);    
}

void pwm_duty_set(uint32_t duty_value){
    volatile uint32_t duty_raw = 255 * (100 - duty_value)/100;
    // uint32_t duty_raw = (255 / 100) * duty_value;
    ledcWrite(pwmData.pwmLedCh,duty_raw);
}

void pwm_set_frec(uint32_t frec_value){
    pwmData.pwmFreq = frec_value;
    ledcSetup(pwmData.pwmLedCh,pwmData.pwmFreq,pwmData.pwmResolution);
    // uint32_t period_us = 1000000/frec_value; 
    // PR2 =  period_us * ((SYS_CLK_BUS_PERIPHERAL/1000000)/4);  //
}
