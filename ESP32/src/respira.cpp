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
    respiraData.state = RESPIRA_EXPIRATION;
    respiraData.n_stand_by = 0;
    pinMode(ASSISTED_LED_PIN,OUTPUT);
    pinMode(ALARM_LED_PIN,OUTPUT);
    pinMode(CPAP_LED_PIN,OUTPUT);
    pinMode(STBY_LED_PIN,OUTPUT);
    pinMode(INSPIRATION_LED_PIN,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
    pinMode(START_STOP_PIN,INPUT);
}

void respira_task(void){
    uint8_t break_sw;

    switch(respiraData.state){
        case RESPIRA_INSPIRATION:
        {
            // digitalWrite(PWM_ENABLE_PIN,H_BRIDGE_ENABLE);
            digitalWrite(PWM_BREAK_PIN,PWM_BREAK_OFF);
            digitalWrite(INSPIRATION_LED_PIN,INSPIRATION_ON);

            if(respiraData.mode == RESPIRA_MODE_CPAP ){

                pidData.SetP = configData.pressure_max;
            }
            else{
                pidData.SetP = respiraData.sp_insp;
            }
            pid_insp_task();

            if(respiraData.mode == RESPIRA_MODE_CONTROL ||
               respiraData.mode == RESPIRA_MODE_ASIST || 
               respiraData.mode == RESPIRA_MODE_CPAP_ASIST){
                
                if(respiraData.t_out_inps == 0){
                    respiraData.t_out_exp = respiraData.t_exp;
                    respiraData.state = RESPIRA_EXPIRATION;
                    break_sw = 0;
                }  
            }
            
            break;
        }
        
        case RESPIRA_EXPIRATION:
        {
            
            
            digitalWrite(PWM_ENABLE_PIN,H_BRIDGE_ENABLE);
            digitalWrite(EXPIRATION_LED_PIN,EXPIRATION_ON);
            
            if (respiraData.mode == RESPIRA_MODE_CPAP ||
                respiraData.mode == RESPIRA_MODE_CPAP_ASIST){                
                pidExpData.SetP = configData.pressure_max;
            }
            else{
                pidExpData.SetP = respiraData.sp_exp;
            }
            if((float)adcData.values_mv[0] <= respiraData.sp_exp + pressure2mv(5)){
                if(!break_sw){
                    break_sw = 1;
                    pwm_duty_set((uint32_t)(4.21*mv2pressure(respiraData.sp_exp)-1.4316));
                }
                else{
                    pid_exp_task();
                }
                digitalWrite(PWM_BREAK_PIN,PWM_BREAK_OFF);
            }
            else{
                digitalWrite(PWM_BREAK_PIN,PWM_BREAK_ON);
            }

            if (respiraData.mode == RESPIRA_MODE_CONTROL ||
              respiraData.mode == RESPIRA_MODE_ASIST){
                if(respiraData.t_out_exp == 0){
                    respiraData.t_out_inps = respiraData.t_insp;
                    respiraData.state = RESPIRA_INSPIRATION;
                }    
            }
            
            if (respiraData.mode == RESPIRA_MODE_ASIST ||
              respiraData.mode == RESPIRA_MODE_CPAP_ASIST){

                adc_get_sample_average();  
                if((float)adcData.values_2_prom[0] <= respiraData.sp_exp - respiraData.sensib){
                    respiraData.t_out_inps = respiraData.t_insp;
                    respiraData.state = RESPIRA_INSPIRATION;
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

    respira_status();
}

void respira_status(void){
    uint8_t chkSum, index_response_frame=0;
    char response_frame[20];

    if(digitalRead(START_STOP_PIN) != respiraData.stdby_sw_last_state){
        respiraData.stdby_sw_last_state = digitalRead(START_STOP_PIN);
        respiraData.n_stand_by = !respiraData.n_stand_by;
        index_response_frame += sprintf(&response_frame[index_response_frame], "p,O%d,Z", respiraData.n_stand_by);
        chkSum = BLUETOOTH_process_chksum(response_frame,index_response_frame);

        //response
        index_response_frame += sprintf(&response_frame[index_response_frame], "%02X,",chkSum);
        BLUETOOTH_send_frame(response_frame);
    }

    if(respiraData.n_stand_by && respiraData.state == RESPIRA_STAND_BY){
        respiraData.state = RESPIRA_EXPIRATION;
        digitalWrite(STBY_LED_PIN,LOW);
    }

    else if(!respiraData.n_stand_by && respiraData.state != RESPIRA_STAND_BY){
        respiraData.state = RESPIRA_STAND_BY;
        digitalWrite(STBY_LED_PIN,HIGH);
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