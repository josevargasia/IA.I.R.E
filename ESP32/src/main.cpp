/* ************************************************************************** */
/**
 * @file main.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing main function.
 */
/* ************************************************************************** */
/** @mainpage IA.I.R.E - Ingeniería Apropiada
 *
 * @section intro_sec Introduction
 * Project for implement low cost mechanical ventilators.
 *
 * @subsection inspiramed_subsec - #InnspiraMED
 * We are part of the initiative in Colombia called #InnspiraMED, in which we are 
 * working on the implementation of ventilation equipment for COVID-19 patients.
 * 
 * @section components_sec Components Used
 * List of components used:
 * 
 * @subsection microcontroller_subsec - Microcontroller
 * - ESP-WROOM-32 (ESP32)
 * 
 * @subsection sensors_subsec - Sensors
 * - Gauge pressure: MPX5010
 * - CO2: MG811
 * - Pulse oximetry and heart-rate: MAX30102
 */


#include "system_definitions.hpp"

CONFIG_DATA configData;    /**< Manage all variables that application can be use to configure system. */

/**
 * @brief Setup system 
 */
void setup() {
  //LED TEST SETUP
  pinMode(LEDPin, OUTPUT);

  //EEPROM SETUP 
  init_eeprom();

  //SERIAL SETUP
  sci_init();
  
  //TIMER SETUP
  timer_init();

  //ADC SETUP
  adc_init();

  //BLUETOOTH SETUP
  BLUETOOTH_init();

  //APLICATION SETUP
  APP_init();

  //PID SETUP
  pid_init();

  //BREATHE SETUP
  respira_init();
}

/**
 * @brief Loop to handle tasks 
 */
void loop() {
  
  //ADC TASK
  adc_task();

  //BLUETOOTH TASK
  BLUETOOTH_Task();    

  //BREATHE TASK
  respira_task();

}

/**
 * @brief Initialize variables from EEPROM 
 */
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
    //timer_ID2_set_frecuency(configData.pwm5_frec);
    
    configData.pwm5_duty = read_int_eeprom(ADDR_PWM5_DUTY, INT8);
    if(configData.pwm5_duty > 100){
        configData.pwm5_duty = 5;
        write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_duty, INT8);
    }
    //pwm_ID5_duty_set(0);
}