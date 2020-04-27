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
}

void respira_task(void){
    switch(respiraData.state){
        case RESPIRA_INSPIRACION:
        {
            digitalWrite(PWM_ENABLE_PIN,H_BRIDGE_ENABLE);
            digitalWrite(INSPIRATION_PIN,INSPIRATION_ON);

            if(respiraData.mode == RESPIRA_MODE_CPAP ){

                pidData.SetP = configData.pressure_max;
            }
            else{
                pidData.SetP = respiraData.sp_insp;
            }

            if(respiraData.mode == RESPIRA_MODE_CONTROL ||
               respiraData.mode == RESPIRA_MODE_ASIST || 
               respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
                
                if(respiraData.t_out_inps == 0){
                    respiraData.t_out_exp = respiraData.t_exp;
                    respiraData.state = RESPIRA_EXPIRACION;
                }  
            }

            pid_task();
            break;
        }
        
        case RESPIRA_EXPIRACION:
        {
            digitalWrite(EXPIRATION_PIN,EXPIRATION_ON);
            
            if (respiraData.mode == RESPIRA_MODE_CPAP ||
                respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
                
                pidData.SetP = configData.pressure_max;
            }
            else{
                pidData.SetP = respiraData.sp_exp;
            }

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
            
            pid_task();
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
        digitalWrite(CONTROL_PIN,CONTROL_ON);
    }
    else{
        digitalWrite(CONTROL_PIN,CONTROL_OFF);
    }

    if(respiraData.mode == RESPIRA_MODE_ASIST || respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
        digitalWrite(ASSISTED_PIN,HIGH);
    }
    else
    {
        digitalWrite(ASSISTED_PIN,LOW);
    }
    

    respiraData.alarm_state = 0;
    if((float)adcData.values_2_prom[0] >= respiraData.lim_alarm_h){
        respiraData.alarm_state = 1;
        digitalWrite(ALARM_PIN,HIGH);
        digitalWrite(BUZZER_PIN,HIGH);
    }
    else if ((float)adcData.values_2_prom[0] <= respiraData.lim_alarm_l){
        respiraData.alarm_state = 2;
        digitalWrite(ALARM_PIN,HIGH);
        digitalWrite(BUZZER_PIN,HIGH);
    }
    else{
        digitalWrite(ALARM_PIN,LOW);
        digitalWrite(BUZZER_PIN,LOW);
    }
    
}