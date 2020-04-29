/* ************************************************************************** */
/**
 * @file respira.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing breathing driver.
 */
/* ************************************************************************** */
#include "system_definitions.hpp"


RESPIRA_DATA respiraData;       /**< Manage all variables that respira can use. */

void respira_init(void){
    respiraData.state = RESPIRA_INSPIRACION;
    pinMode(ASSISTED_LED_PIN,OUTPUT);
    pinMode(ALARM_LED_PIN,OUTPUT);
    pinMode(CPAP_LED_PIN,OUTPUT);
    pinMode(STBY_LED_PIN,OUTPUT);
    pinMode(INSPIRATION_LED_PIN,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
}

void respira_task(void){
    switch(respiraData.state){
        case RESPIRA_INSPIRACION:
        {
            digitalWrite(PWM_ENABLE_PIN,H_BRIDGE_ENABLE);
            digitalWrite(INSPIRATION_LED_PIN,INSPIRATION_ON);

            if(respiraData.mode == RESPIRA_MODE_CPAP ){

                pidData.SetP = configData.pressure_max;
            }
            else{
                pidData.SetP = respiraData.sp_insp;
            }
            pid_task();

            if(respiraData.mode == RESPIRA_MODE_CONTROL ||
               respiraData.mode == RESPIRA_MODE_ASIST || 
               respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
                
                if(respiraData.t_out_inps == 0){
                    respiraData.t_out_exp = respiraData.t_exp;
                    respiraData.state = RESPIRA_EXPIRACION;
                }  
            }
            
            break;
        }
        
        case RESPIRA_EXPIRACION:
        {
            digitalWrite(EXPIRATION_LED_PIN,EXPIRATION_ON);
            
            if (respiraData.mode == RESPIRA_MODE_CPAP ||
                respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
                
                pidData.SetP = configData.pressure_max;
            }
            else{
                pidData.SetP = respiraData.sp_exp;
            }
            pid_task();

            if (respiraData.mode == RESPIRA_MODE_CONTROL ||
              respiraData.mode == RESPIRA_MODE_ASIST){
                if(respiraData.t_out_exp == 0){
                    respiraData.t_out_inps = respiraData.t_insp;
                    respiraData.state = RESPIRA_INSPIRACION;
                }    
            }
            
            if (respiraData.mode == RESPIRA_MODE_ASIST ||
              respiraData.mode == RESPIRA_MODE_CPAP_ASIST){

                adc_get_sample_average();  
                if((float)adcData.values_2_prom[0] <= respiraData.sp_exp - respiraData.sensib){
                    respiraData.t_out_inps = respiraData.t_insp;
                    respiraData.state = RESPIRA_INSPIRACION;
                }    
            }
            
            break;
        }
        
        case RESPIRA_STAND_BY:
        {
            digitalWrite(PWM_ENABLE_PIN,H_BRIDGE_DISABLE);
            break;
        }
        
        default:
        {
            respiraData.state = RESPIRA_STAND_BY;
            break;
        }
    }

    if(respiraData.mode == RESPIRA_MODE_CONTROL || respiraData.mode == RESPIRA_MODE_ASIST){
        digitalWrite(CONTROL_LED_PIN,CONTROL_ON);
    }
    else{
        digitalWrite(CONTROL_LED_PIN,CONTROL_OFF);
    }

    if(respiraData.mode == RESPIRA_MODE_ASIST || respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
        digitalWrite(ASSISTED_LED_PIN,HIGH);
    }
    else
    {
        digitalWrite(ASSISTED_LED_PIN,LOW);
    }
    

    respiraData.alarm_state = 0;
    if((float)adcData.values_2_prom[0] >= respiraData.lim_alarm_h){
        respiraData.alarm_state = 1;
        digitalWrite(ALARM_LED_PIN,HIGH);
        digitalWrite(BUZZER_PIN,HIGH);
    }
    else if ((float)adcData.values_2_prom[0] <= respiraData.lim_alarm_l){
        respiraData.alarm_state = 2;
        digitalWrite(ALARM_LED_PIN,HIGH);
        digitalWrite(BUZZER_PIN,HIGH);
    }
    else{
        digitalWrite(ALARM_LED_PIN,LOW);
        digitalWrite(BUZZER_PIN,LOW);
    }
    
}