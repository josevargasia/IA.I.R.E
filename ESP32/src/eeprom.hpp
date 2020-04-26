/* ************************************************************************** */
/**
 * @file eeprom.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing Bluetooth driver.
 */
/* ************************************************************************** */

#include <Arduino.h>
#include <EEPROM.h>


#define EEPROM_SIZE     64             /**< EEPROM size address. */

//Length in bytes of numeric values 
#define MAX_32_BITS     4               /**< Length in bytes of 32 bits integer. */
#define MAX_16_BITS     2               /**< Length in bytes of 16 bits integer. */
#define MAX_8_BITS      1               /**< Length in bytes of 8 bits integer. */

//length in bits of numeric values
#define INT32       32                  /**< Length in bits of 32 bits integer. */
#define INT16       16                  /**< Length in bits of 16 bits integer. */
#define INT8        8                   /**< Length in bits of 8 bits integer. */

//-------------------- PAGE 0 ----------------------------------------------
    
#define MAX_PRESSURE_MAX        MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_INSPIRATION_TIME    MAX_16_BITS     /**< Length in bytes of numeric values. */
#define MAX_EXPIRATION_TIME     MAX_16_BITS     /**< Length in bytes of numeric values. */
#define MAX_PWM5_DUTY           MAX_8_BITS      /**< Length in bytes of numeric values. */
#define MAX_PWM5_FREC           MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_PRESSURE_INS        MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_PRESSURE_EXP        MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_RESPIRA_MODES       MAX_8_BITS      /**< Length in bytes of numeric values. */
#define MAX_SENSITIVITY         MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_ALARM_HIGH          MAX_32_BITS     /**< Length in bytes of numeric values. */
#define MAX_ALARM_LOW           MAX_32_BITS     /**< Length in bytes of numeric values. */

#define INIT_PAGE_0             0               /**< Start address of page 0 in EEPROM. */ 
#define ADDR_PRESSURE_MAX       INIT_PAGE_0     /**< Address of variable. */                    
#define ADDR_INSPIRATION_TIME   INIT_PAGE_0+MAX_PRESSURE_MAX    /**< Address of variable. */
#define ADDR_EXPIRATION_TIME    INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME   /**< Address of variable. */
#define ADDR_PWM5_DUTY          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME   /**< Address of variable. */
#define ADDR_PWM5_FREC          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY /**< Address of variable. */
#define ADDR_PRESSURE_INS       INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC   /**< Address of variable. */
#define ADDR_PRESSURE_EXP       INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS /**< Address of variable. */
#define ADDR_RESPIRA_MODES      INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS+MAX_PRESSURE_EXP /**< Address of variable. */
#define ADDR_SENSITIVITY        INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS+MAX_PRESSURE_EXP+MAX_RESPIRA_MODES /**< Address of variable. */
#define ADDR_ALARM_HIGH         INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS+MAX_PRESSURE_EXP+MAX_RESPIRA_MODES+MAX_SENSIVITY /**< Address of variable. */
#define ADDR_ALARM_LOW          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS+MAX_PRESSURE_EXP+MAX_RESPIRA_MODES+MAX_SENSIVITY+MAX_ALARM_HIGH /**< Address of variable. */


/**
 * @brief EEPROM setup 
 */
void init_eeprom(void);

/**
 * @brief Write integer of 8, 16 or 32 bits
 * @code
 *      write_int_eeprom(ADDR_PWM5_FREC, 10000, INT32);
 * @endcode
 * @param  address      Address in EEPROM to write   
 * @param  number       Integer to wirte
 * @param  int_length   Length in bits of integer  
 */
void write_int_eeprom(uint32_t address, uint32_t number, uint8_t int_length);

/**
 * @brief Read integer of 8, 16 or 32 bits
 * @code
 *      uint32_t data = read_int_eeprom(ADDR_PWM5_FREC, INT32);
 * @endcode
 * @param  address      Address in EEPROM to read   
 * @param  int_length   Length in bits of integer
 * @return Return integer readed   
 */
uint32_t read_int_eeprom(uint32_t address, uint8_t int_length);

/**
* @brief Write float
* Only save 2 decimals
* @code
*      write_float_eeprom(ADDR_PRESSURE_INS, 100.69);
* @endcode
* @param  address      Address in EEPROM to write   
* @param  number       Float to wirte
*/
void write_float_eeprom(uint32_t address, float number);

/**
* @brief Read float
* @code
*      float data = read_float_eeprom(ADDR_PRESSURE_INS);
* @endcode
* @param  address      Address in EEPROM to read   
* @return Return float readed   
*/
float read_float_eeprom(uint32_t address);