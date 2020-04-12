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
            pwmData.pwmEnablePin = 1;
            pidData.SetP = respiraData.sp_insp;
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
            pidData.SetP = respiraData.sp_exp;
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
            pwmData.pwmEnablePin = 0;
        }
        
        default:
        {
            respiraData.state = RESPIRA_STAND_BY;
            break;
        }
    }
    
}