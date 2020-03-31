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
#include "pwm.h"


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
    
    configData.pressure_max = read_int_eeprom(ADDR_PRESSURE_MAX, INT16);
    configData.inspiration_time = read_int_eeprom(ADDR_INSPIRATION_TIME, INT16);
    configData.expiration_time = read_int_eeprom(ADDR_EXPIRATION_TIME, INT16);
    
    configData.pwm5_frec = read_int_eeprom(ADDR_PWM5_FREC, INT32);
    if(configData.pwm5_frec < 10000 && configData.pwm5_frec > 50000){
        configData.pwm5_frec == 10000;
        write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_frec, INT32);
    }
    timer_ID2_set_frecuency(configData.pwm5_frec);
    
    configData.pwm5_duty = read_int_eeprom(ADDR_PWM5_DUTY, INT8);
    if(configData.pwm5_duty > 100){
        configData.pwm5_duty = 5;
        write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_duty, INT8);
    }
    pwm_ID5_duty_set(configData.pwm5_duty);
    
    appData.state = APP_STATE_INIT;
}

void APP_Task(void){
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {   
            sci_ID1_send("<---------- Init App ---------->\n");
            BLUETOOTH_init();
            appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            //BLUETOOTH_Task();
//            pwm_ID5_duty_set(25);
            HBRIDGE_Task();
            if(appData.test_timeout == 0){
                
                appData.test_timeout = 500;
            }
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
