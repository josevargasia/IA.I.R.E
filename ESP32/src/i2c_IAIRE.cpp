/* ************************************************************************** */
/**
 * @file i2c_IAIRE.cpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing I2C driver.
 */
/* ************************************************************************** */

#include "system_definitions.hpp"


TwoWire *_i2cPort;  /**< The generic connection to user's chosen I2C hardware. */


void I2C_Init(TwoWire &wirePort, uint32_t i2cSpeed){
    _i2cPort = &wirePort;           /**< Grab which port the user wants to use. */
    _i2cPort->begin();
    _i2cPort->setClock(i2cSpeed);   /**< Grab which speed the user wants to use. */
}

void writeRegister8(uint8_t address, uint8_t reg, uint8_t value){
    _i2cPort->beginTransmission(address);
    _i2cPort->write(reg);
    _i2cPort->write(value);
    _i2cPort->endTransmission();
}

uint8_t readRegister8(uint8_t address, uint8_t reg) {
    _i2cPort->beginTransmission(address);
    _i2cPort->write(reg);
    _i2cPort->endTransmission(false);
    _i2cPort->requestFrom((uint8_t)address, (uint8_t)1); /**< Request 1 byte. */
    if (_i2cPort->available()){
        return(_i2cPort->read()); /**< Return 8-bit value readed. */
    }
    return (0); /**< Fail. */
}