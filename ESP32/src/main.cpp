
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

  //BLUETOOTH SETUP
  BLUETOOTH_init();

  //PID SETUP
  pid_init();
  
}

void loop() {
  
  //BLUETOOTH TASK
  BLUETOOTH_Task();    

  //BREATHE TASK
  respira_task();
    
}
