/* ************************************************************************** */
/**
 * @file i2c_IAIRE.hpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing I2C driver.
 */
/* ************************************************************************** */

#include <Arduino.h>
#include <Wire.h>

#define I2C_BUFFER_LEN          32          /**< I2C buffer length. */
#define I2C_SPEED               100000      /**< I2C protocol transmission speed. */

extern TwoWire *_i2cPort;                   /**< The generic connection to user's chosen I2C hardware. */

/**
* @brief I2C setup
* @code
*      I2C_Init(Wire, I2C_SPEED);
* @endcode
* @param  wirePort     The generic connection to user's chosen I2C hardware   
* @param  i2cSpeed     Protocol transmission speed
*/
void I2C_Init(TwoWire &wirePort, uint32_t i2cSpeed);

/**
* @brief I2C write 8-bit register
* @code
*      writeRegister8(MAX30102_ADDRESS, REG_FIFO_CONFIG, 0x5E);
* @endcode
* @param  address      Address of the I2C sensor to write   
* @param  reg          Register to wirte
* @param  value        Value to wirte
*/
void writeRegister8(uint8_t address, uint8_t reg, uint8_t value);

/**
 * @brief I2C read 8-bit register
 * @code
 *      writePointer = readRegister8(MAX30102_ADDRESS, REG_FIFO_WR_PTR);
 * @endcode
 * @param  address      Address of the I2C sensor to read   
 * @param  reg          Register to read
 * @return Return 8-bit value readed   
 */
uint8_t readRegister8(uint8_t address, uint8_t reg);