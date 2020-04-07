/* ************************************************************************** */
/**
 * @file app.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing principal state machine.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

APP_DATA appData;
CONFIG_DATA configData;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


void APP_init(void){
    
    respiraData.sp_insp = read_float_eeprom(ADDR_PRESSURE_INS);
    respiraData.sp_exp = read_float_eeprom(ADDR_PRESSURE_EXP);
    respiraData.t_insp = read_int_eeprom(ADDR_INSPIRATION_TIME, INT16);
    respiraData.t_exp = read_int_eeprom(ADDR_EXPIRATION_TIME, INT16);
    
    configData.pwm5_frec = read_int_eeprom(ADDR_PWM5_FREC, INT32);
    if(configData.pwm5_frec < 10000 || configData.pwm5_frec > 50000){
        configData.pwm5_frec = 10000;
        write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_frec, INT32);
    }
    timer_ID2_set_frecuency(configData.pwm5_frec);
    
    configData.pwm5_duty = read_int_eeprom(ADDR_PWM5_DUTY, INT8);
    if(configData.pwm5_duty > 100){
        configData.pwm5_duty = 5;
        write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_duty, INT8);
    }
    pwm_ID5_duty_set(0);
    
    appData.state = APP_STATE_INIT;
}

void APP_Task(void){
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {   
            sci_ID5_send("<---------- Init App ---------->\n");
            BLUETOOTH_init();
            respira_init();
            appData.test_timeout = 1000;
            appData.test_count = 0;
            appData.test_enable = 0;
            configData.pwm5_duty = 0;
//            pwm_ID5_duty_set(0);
            appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            BLUETOOTH_Task();
            
            respira_task();
//            pid_task();
            
//            if(appData.test_timeout == 0 && appData.test_enable == 1){
//                adc_get_sample_average();
//                appData.test_adc[appData.test_count++] = adcData.values_2_prom[0];
//                if(appData.test_count > 50){
//                    pwm_ID5_duty_set(configData.pwm5_duty);
//                }
//                if(appData.test_count == 1000){
//                    appData.test_count = 0;
//                }
//                appData.test_timeout = 3;
//            }
            
//            if(appData.test_timeout == 0){
//                
//                if(configData.pwm5_duty < 100){
//                    configData.pwm5_duty++;
//                    OC3RS = (uint32_t)((configData.pwm5_duty*PR2)/100);
//                    OC3R = (uint32_t)((configData.pwm5_duty*PR2)/100);
//                }
//                appData.test_timeout = 100;
//            }
            break;
        }
        default:
        {
            appData.state = APP_STATE_INIT;
            break;
        }
    }
}


/* *****************************************************************************
 End of File
 */
