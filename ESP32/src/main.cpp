
#include "system_definitions.hpp"


void setup() {
  //LED TEST SETUP
  pinMode(LEDPin, OUTPUT);

  //SERIAL SETUP
  sci_init();
  
  //TIMER SETUP
  timer_init();

  //BLUETOOTH SETUP
  BLUETOOTH_init();
  
}

void loop() {
  
  //BLUETOOTH TASK
  BLUETOOTH_Task();    
    
}
