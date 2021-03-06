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
  pinMode(BT_LED_PIN, OUTPUT);
  pinMode(PWM_ENABLE_PIN,OUTPUT);
  digitalWrite(PWM_ENABLE_PIN,HIGH);

  //EEPROM SETUP 
  init_eeprom();

  //APLICATION SETUP
  APP_init();

  //SERIAL SETUP
  sci_init();
  
  //TIMER SETUP
  timer_init();

  //PWM SETUP
  pwm_init();

  //ADC SETUP
  adc_init();

  //BLUETOOTH SETUP
  BLUETOOTH_init();

  //PID SETUP
  pid_init();

  //BREATHE SETUP
  respira_init();

  //MAX30102 SETUP
  MAX30102_Init();
}

/**
 * @brief Loop to handle tasks 
 */
void loop() {
  //ADC TASK
  adc_task();

  //MAX30102 TASK
  MAX30102_Tasks();

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
    respiraData.mode = read_int_eeprom(ADDR_RESPIRA_MODES,INT8);
    respiraData.lim_alarm_h = read_float_eeprom(ADDR_ALARM_HIGH);
    respiraData.lim_alarm_l = read_float_eeprom(ADDR_ALARM_LOW);
    pressData.adjustValue = read_float_eeprom(ADDR_PRESSURE_ADJUST);
    pidData.kp = read_float_eeprom(ADDR_PID_KP_INSP);
    pidData.ti = read_float_eeprom(ADDR_PID_TI_INSP);
    pidData.td = read_float_eeprom(ADDR_PID_TD_INSP);
    pidExpData.kp = read_float_eeprom(ADDR_PID_KP_EXP);
    pidExpData.ti = read_float_eeprom(ADDR_PID_TI_EXP);
    pidExpData.td = read_float_eeprom(ADDR_PID_TD_EXP);
    
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

    CO2_Zero_Point_Volt = read_float_eeprom(ADDR_C02_ZP_VOLT);
    if(CO2_Zero_Point_Volt < 1.45 || CO2_Zero_Point_Volt > 4.45){
        CO2_Zero_Point_Volt = 2.01;
        write_float_eeprom(ADDR_C02_ZP_VOLT, CO2_Zero_Point_Volt);
    }
}