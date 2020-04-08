
#include "system_definitions.hpp"

CONFIG_DATA configData;    /**< Manage all variables that application can be use to configure system. */

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

void loop() {
  
  //ADC TASK
  adc_task();

  //BLUETOOTH TASK
  BLUETOOTH_Task();    

  //BREATHE TASK
  respira_task();

}

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