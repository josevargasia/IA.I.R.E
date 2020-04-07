#include <Arduino.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int LEDPin = 2;

//TIMER ISR
hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer(){
  SerialBT.println(String("onTimer() ")+String(millis()));
  digitalWrite(LEDPin, !digitalRead(LEDPin));
}

void setup() {
  //LED TEST SETUP
  pinMode(LEDPin, OUTPUT);
  
  //TIMER SETUP
  Serial.println("start timer ");
  timer = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
  timerAttachInterrupt(timer, &onTimer, true); // edge (not level) triggered 
  timerAlarmWrite(timer, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true
  timerAlarmEnable(timer); // enable
  
  //BLUETOOTH SETUP
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // digitalWrite(LEDPin, HIGH);
  // delay(25);
  // digitalWrite(LEDPin, LOW);
  // delay(25);
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}