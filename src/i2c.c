/* ************************************************************************** */
/**
 * @file i2c.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing I2C driver.
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

void i2c_init (void){
    // I2C ID_1
    PIN_SCL1_OUT = 0;
    PIN_SDA1_OUT = 0;
    PIN_SCL1 = 1;
    PIN_SDA1 = 1;

    // I2C ID_2
    PIN_SCL2_OUT = 0;
    PIN_SDA2_OUT = 0;
    PIN_SCL2 = 1;
    PIN_SDA2 = 1;
}

// I2C ID_2
void i2c_ID_1_dly(void){
    delay_us(10);
}
void i2c_ID_1_startp(void){
  PIN_SDA1 = 1; //SDA = 1;             // i2c start bit sequence
  i2c_ID_1_dly();
  PIN_SCL1 = 1; //SCL = 1;
  i2c_ID_1_dly();
  PIN_SDA1 = 0; //SDA = 0;
  i2c_ID_1_dly();
  PIN_SCL1 = 0; //SCL = 0;
  i2c_ID_1_dly();
}

void i2c_ID_1_stopp(void){
  PIN_SDA1 = 0; //SDA = 0;             // i2c stop bit sequence
  i2c_ID_1_dly();
  PIN_SCL1 = 1; //SCL = 1;
  i2c_ID_1_dly();
  PIN_SDA1 = 1; //SDA = 1;
  i2c_ID_1_dly();
}

uint8_t i2c_ID_1_writep(uint8_t d){
unsigned char x, b;
  for(x=8; x; x--) {
    if(d & 0x80) PIN_SDA1 = 1; //SDA = 1;
    else PIN_SDA1 = 0; //SDA = 0;
  	i2c_ID_1_dly();
    PIN_SCL1 = 1; //SCL = 1;
  	i2c_ID_1_dly();
    d <<= 1;
    PIN_SCL1 = 0; //SCL = 0;
  }
  i2c_ID_1_dly();
  PIN_SDA1 = 1; //SDA = 1;
  PIN_SCL1 = 1; //SCL = 1;
  i2c_ID_1_dly();
  b = PIN_SDA1_IN; //SDA_IN;          // possible ACK bit
  PIN_SCL1 = 0; //SCL = 0;
  i2c_ID_1_dly();
  return b;
}

uint8_t i2c_ID_1_readp(uint8_t ack){
    
 unsigned char d=0,x;
  PIN_SDA1 = 1; //SDA = 1; 
  for(x=0; x<8; x++) {
    d <<= 1;
    do {
      PIN_SCL1 = 1; //SCL = 1;
    }
    while(PIN_SCL1_IN == 0/*SCL_IN==0*/);    // wait for any SCL clock stretching
    i2c_ID_1_dly();
    if(PIN_SDA1_IN/*SDA_IN*/) d |= 1;
    PIN_SCL1 = 0; //SCL = 0;
    i2c_ID_1_dly();
  } 
  if(ack) PIN_SDA1 = 0; //SDA = 0;
  else PIN_SDA1 = 1; //SDA = 1;
  i2c_ID_1_dly();             
  PIN_SCL1 = 1; //SCL = 1;
  i2c_ID_1_dly();             // send (N)ACK bit
    do {
      PIN_SCL1 = 0; //SCL = 0;
    }
    while(PIN_SCL1_IN/*SCL_IN*/==1);    // wait for any SCL clock stretching
  PIN_SDA1 = 1; //SDA = 1;
  i2c_ID_1_dly();             // send (N)ACK bit
  return d;
}

// I2C ID_2
void i2c_ID_2_dly(void){
    delay_us(10);
}

void i2c_ID_2_startp(void){
  PIN_SDA2 = 1; //SDA = 1;             // i2c start bit sequence
  i2c_ID_2_dly();
  PIN_SCL2 = 1; //SCL = 1;
  i2c_ID_2_dly();
  PIN_SDA2 = 0; //SDA = 0;
  i2c_ID_2_dly();
  PIN_SCL2 = 0; //SCL = 0;
  i2c_ID_2_dly();
}

void i2c_ID_2_stopp(void){
  PIN_SDA2 = 0; //SDA = 0;             // i2c stop bit sequence
  i2c_ID_2_dly();
  PIN_SCL2 = 1; //SCL = 1;
  i2c_ID_2_dly();
  PIN_SDA2 = 1; //SDA = 1;
  i2c_ID_2_dly();
}

uint8_t i2c_ID_2_writep(uint8_t d){
unsigned char x, b;
  for(x=8; x; x--) {
    if(d & 0x80) PIN_SDA2 = 1; //SDA = 1;
    else PIN_SDA2 = 0; //SDA = 0;
  	i2c_ID_2_dly();
    PIN_SCL2 = 1; //SCL = 1;
  	i2c_ID_2_dly();
    d <<= 1;
    PIN_SCL2 = 0; //SCL = 0;
  }
  i2c_ID_2_dly();
  PIN_SDA2 = 1; //SDA = 1;
  PIN_SCL2 = 1; //SCL = 1;
  i2c_ID_2_dly();
  b = PIN_SDA2_IN; //SDA_IN;          // possible ACK bit
  PIN_SCL2 = 0; //SCL = 0;
  i2c_ID_2_dly();
  return b;
}

uint8_t i2c_ID_2_readp(uint8_t ack){
 unsigned char d=0,x;

  PIN_SDA2 = 1; //SDA = 1; 
  for(x=0; x<8; x++) {
    d <<= 1;
    do {
      PIN_SCL2 = 1; //SCL = 1;
    }
    while(PIN_SCL2_IN == 0/*SCL_IN==0*/);    // wait for any SCL clock stretching
    i2c_ID_2_dly();
    if(PIN_SDA2_IN/*SDA_IN*/) d |= 1;
    PIN_SCL2 = 0; //SCL = 0;
    i2c_ID_2_dly();
  } 
  if(ack) PIN_SDA2 = 0; //SDA = 0;
  else PIN_SDA2 = 1; //SDA = 1;
  i2c_ID_2_dly();             
  PIN_SCL2 = 1; //SCL = 1;
  i2c_ID_2_dly();             // send (N)ACK bit
    do {
      PIN_SCL2 = 0; //SCL = 0;
    }
    while(PIN_SCL2_IN/*SCL_IN*/==1);    // wait for any SCL clock stretching
  PIN_SDA2 = 1; //SDA = 1;
  i2c_ID_2_dly();             // send (N)ACK bit
  return d;
}
/* *****************************************************************************
 End of File
 */
