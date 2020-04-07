
#include "system_definitions.hpp"

void write_int_eeprom(uint32_t address, uint32_t number, uint8_t int_length)
{	
    uint8_t index;
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
    
    for(index = 0; index < eepromBuffLen; index++){
        EEPROM.write(address+index, eepromBuff[index]);
    }
    EEPROM.commit();
}

uint32_t read_int_eeprom(uint32_t address, uint8_t int_length)
{	
    uint8_t index;
	uint32_t number = 0;
	
	uint8_t eepromBuff[4];
	uint16_t eepromBuffLen = 0;
	
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
    
    for(index = 0; index < eepromBuffLen; index++){
        eepromBuff[index] = EEPROM.read(address+index);
    }
    
	switch(int_length){
		case 32:
		{
			number = (eepromBuff[0]<<24);
			number |= (eepromBuff[1]<<16);
			number |= (eepromBuff[2]<<8);
			number |= (eepromBuff[3]);
			break;
		}
		case 16:
		{
			number = (eepromBuff[0]<<8);
			number |= (eepromBuff[1]);
			break;
		}	
		case 8:
		{
			number = (eepromBuff[0]);
			break;
		}
		default:
			break;
	}
	
	return number;
}
