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

uint8_t ext_eeprom_ready_ID_1(char addr) {
   uint8_t ack;
   i2c_ID_1_startp();            // If the write command is acknowledged,
   ack = i2c_ID_1_writep(addr);  // then the device is ready.
   i2c_ID_1_stopp();
   return !ack;
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

void write_string_eeprom(uint32_t address, char * string, uint16_t string_length)
{		
    int k = 0;
    uint16_t numCharsToSend, numCharsSended = 0;
    
    // Calculate number of pages to write
    uint16_t numFirsPageToWrite = address / EEPROM_PAGE_LENGTH;                         // From which page write  
    uint16_t numLastPageToWrite = ((address + string_length) / EEPROM_PAGE_LENGTH) + 1; // Until which page write 
    
    // Calculate space available in first page to write
    uint8_t first_page_space = EEPROM_PAGE_LENGTH - (address % EEPROM_PAGE_LENGTH);     // Number of chars to write in first page
       
    // Calculate space available in last page to write
    uint8_t last_page_space = (address + string_length) % EEPROM_PAGE_LENGTH;           // Number of chars to write in last page
     
    if(numFirsPageToWrite == (numLastPageToWrite - 1)){
        numCharsToSend = string_length;
        write_string_eeprom_w(address, &string[numCharsSended], numCharsToSend);
    }else{
        for(k = numFirsPageToWrite; k < numLastPageToWrite; k++){                           // Write from first to last page
            if(k == numFirsPageToWrite){
                numCharsToSend = first_page_space;
            }else if(k == (numLastPageToWrite-1)){
                numCharsToSend = last_page_space;
            }else{
                numCharsToSend = EEPROM_PAGE_LENGTH;
            }

            write_string_eeprom_w(address, &string[numCharsSended], numCharsToSend);
            address += numCharsToSend;
            numCharsSended += numCharsToSend;
        }
    }
}

void write_string_eeprom_w(uint32_t address, char * string, uint16_t string_length)
{		
    uint16_t i;
	
    if(address > 0xFFFF){
        deviceAddressSlave1=EEPROM_SLAVE_ADDRESS_2;
    }else{
        deviceAddressSlave1=EEPROM_SLAVE_ADDRESS_1;
    }
    
    while(!ext_eeprom_ready_ID_1(deviceAddressSlave1));
    i2c_ID_1_startp();
    i2c_ID_1_writep(deviceAddressSlave1);
    i2c_ID_1_writep(address>>8);
    i2c_ID_1_writep(address);
    for(i = 0; i < string_length; i++){
        i2c_ID_1_writep(string[i]);
    }
    i2c_ID_1_stopp();
}

void read_string_eeprom(uint32_t address, char * string, uint16_t string_length)
{	
    uint16_t i;
    for(i = 0; i < string_length; i++){
        string[i] = read_string_eeprom_w(address+i);
    }	
}

char read_string_eeprom_w(uint32_t address){
    uint16_t i;
    char byteRead;
    
    if(address > 0xFFFF){
        deviceAddressSlave1=EEPROM_SLAVE_ADDRESS_2;
    }else{
        deviceAddressSlave1=EEPROM_SLAVE_ADDRESS_1;
    }
	
    while(!ext_eeprom_ready_ID_1(deviceAddressSlave1));
    i2c_ID_1_startp();
    i2c_ID_1_writep(deviceAddressSlave1);
    i2c_ID_1_writep(address>>8);
    i2c_ID_1_writep(address);
    i2c_ID_1_startp();
    i2c_ID_1_writep(deviceAddressSlave1|0x01);
    byteRead = i2c_ID_1_readp(0);
    i2c_ID_1_stopp();
    
    return byteRead;
}

void write_int_eeprom(uint32_t address, uint32_t number, uint8_t int_length)
{	
	uint8_t eepromBuff[4];
	uint16_t eepromBuffLen = 0;
    
	switch(int_length){
		case 32:
		{
			eepromBuff[0] = (uint8_t)(number>>24);
			eepromBuff[1] = (uint8_t)(number>>16);
			eepromBuff[2] = (uint8_t)(number>>8);
			eepromBuff[3] = (uint8_t)(number);
			eepromBuffLen = 4;
			break;
		}
		case 16:
		{
			eepromBuff[0] = (uint8_t)(number>>8);
			eepromBuff[1] = (uint8_t)(number);
			eepromBuffLen = 2;
			break;
		}	
		case 8:
		{
			eepromBuff[0] = (uint8_t)(number);
			eepromBuffLen = 1;
			break;
		}
		default:
			eepromBuffLen = 0;
			break;
	}
    
    write_string_eeprom(address, eepromBuff, eepromBuffLen);
	

}

uint32_t read_int_eeprom(uint32_t address, uint8_t int_length)
{	
	uint32_t number = 0;
	
	uint8_t eepromBuff[4];
	uint16_t eepromBuffLen = 0;
    
//    char der[200];
	
	switch(int_length){
		case 32:
		{
			eepromBuffLen = 4;
			break;
		}
		case 16:
		{
			eepromBuffLen = 2;
			break;
		}	
		case 8:
		{
			eepromBuffLen = 1;
			break;
		}
		default:
			eepromBuffLen = 0;
			break;
	}
    
//    sprintf(der, "int_r: LEN: %d\n",eepromBuffLen);
//    send_sci5(der);
    
    read_string_eeprom(address, eepromBuff, eepromBuffLen);
    
    
//    sprintf(der, "int_r: %d.%d.%d.%d - %d\n", eepromBuff[0],eepromBuff[1],eepromBuff[2],eepromBuff[3], eepromBuffLen);
//    send_sci5(der);
    
	   
	switch(int_length){
		case 32:
		{
			number = (eepromBuff[0]<<24);
			number |= (eepromBuff[1]<<16);
			number |= (eepromBuff[2]<<8);
			number |= (eepromBuff[3]);
            
//            sprintf(der, "int_r32: data: %d.%d.%d.%d - len: %d\n", eepromBuff[0],eepromBuff[1],eepromBuff[2],eepromBuff[3], int_length);
			break;
		}
		case 16:
		{
			number = (eepromBuff[0]<<8);
			number |= (eepromBuff[1]);
            
//            sprintf(der, "int_r16: data: %d.%d - len: %d\n", eepromBuff[0],eepromBuff[1], int_length);
			break;
		}	
		case 8:
		{
			number = (eepromBuff[0]);
            
//            sprintf(der, "int_r8: data: %d - len: %d\n", eepromBuff[0], int_length);
			break;
		}
		default:
			break;
	}
    
//    send_sci5(der);
    
//    char der[20];
//    sprintf(der, "int_r2: %u\n", number);
//    send_sci5(der);
	
	return number;
}

void write_float_eeprom(uint32_t address, float number)
{	
    write_int_eeprom(address, (uint32_t)(number*100), INT32);

}

float read_float_eeprom(uint32_t address){
    float ret;
    
    ret = (float)read_int_eeprom(address, INT32)/100;
    
    return ret;
}
/* *****************************************************************************
 End of File
 */
