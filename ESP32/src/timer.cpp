/* ************************************************************************** */
/**
 * @file timer.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing Timers driver.
 */
/* ************************************************************************** */
#include "system_definitions.hpp"


//TIMER ISR
hw_timer_t * timer0 = NULL;   /**< Handle timer ISR. */
hw_timer_t * timer1 = NULL;   /**< Handle timer ISR. */


void timer_init(void){
    timer_ID0_init_us(1000);       // For timeouts
    timer_ID1_init_us(100);        // For ADC
}

void timer_ID0_init_us (uint32_t period_us){
    //Serial.println("start timer 0");
    timer0 = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer0, &Timer0_ISR, true); // edge (not level) triggered 
    timerAlarmWrite(timer0, period_us, true); // 1000000 * 1 us = 1 s, autoreload true
    timerAlarmEnable(timer0); // enable

}

void IRAM_ATTR Timer0_ISR(void){    // 1 ms
  //Serial.println(String("Timer0_ISR() ")+String(millis()));
  
  if(bluetoothData.timeout_led_blink)
    bluetoothData.timeout_led_blink--;
  
  if(bluetoothData.timeout)
    bluetoothData.timeout--;

  if(pidData.timeout)
    pidData.timeout--;

  if(respiraData.t_out_inps)
    respiraData.t_out_inps--;
    
  if(respiraData.t_out_exp)
    respiraData.t_out_exp--;
}

void timer_ID1_init_us (uint32_t period_us){
    //Serial.println("start timer 1");
    timer1 = timerBegin(1, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
    timerAttachInterrupt(timer1, &Timer1_ISR, true); // edge (not level) triggered 
    timerAlarmWrite(timer1, period_us, true); // 1000000 * 1 us = 1 s, autoreload true
    timerAlarmEnable(timer1); // enable

}

void IRAM_ATTR Timer1_ISR(void){  // 100 us
  if(adcData.delay_samples)
    adcData.delay_samples--;

}