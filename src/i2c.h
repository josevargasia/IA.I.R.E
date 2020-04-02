/* ************************************************************************** */
/**
 * @file i2c.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing I2C driver.
 */
/* ************************************************************************** */

#ifndef _I2C_H    /* Guard against multiple inclusion */
#define _I2C_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    // I2C ID_1
    #define PIN_SCL1	 TRISGbits.TRISG2   /**< Set GPIO direction port. */
    #define PIN_SDA1	 TRISGbits.TRISG3   /**< Set GPIO direction port. */

    #define PIN_SCL1_IN	 PORTGbits.RG2      /**< Get GPIO state port. */
    #define PIN_SDA1_IN	 PORTGbits.RG3      /**< Get GPIO state port. */

    #define PIN_SCL1_OUT LATGbits.LATG2     /**< Set GPIO state port. */
    #define PIN_SDA1_OUT LATGbits.LATG3     /**< Set GPIO state port. */

    // I2C ID_2
    #define PIN_SCL2	 TRISAbits.TRISA2   /**< Set GPIO direction port. */
    #define PIN_SDA2	 TRISAbits.TRISA3   /**< Set GPIO direction port. */

    #define PIN_SCL2_IN	 PORTAbits.RA2      /**< Get GPIO state port. */
    #define PIN_SDA2_IN	 PORTAbits.RA3      /**< Get GPIO state port. */

    #define PIN_SCL2_OUT LATAbits.LATA2     /**< Set GPIO state port. */
    #define PIN_SDA2_OUT LATAbits.LATA3     /**< Set GPIO state port. */

    #define EEPROM_PAGE_LENGTH      128     /**< Length of page in EEPROM used. */

    #define EEPROM_SLAVE_ADDRESS_1  0xA0    /**< EEPROM slave address 1. */ 
    #define EEPROM_SLAVE_ADDRESS_2  0xA8    /**< EEPROM slave address 2. */ 

    //Length in bytes of numeric values 
    #define MAX_32_BITS     4               /**< Length in bytes of 32 bits integer. */
    #define MAX_16_BITS     2               /**< Length in bytes of 16 bits integer. */
    #define MAX_8_BITS      1               /**< Length in bytes of 8 bits integer. */

    //length in bits of numeric values
    #define INT32       32                  /**< Length in bits of 32 bits integer. */
    #define INT16       16                  /**< Length in bits of 16 bits integer. */
    #define INT8        8                   /**< Length in bits of 8 bits integer. */

    //**************************************************
    // First address part - From 0x0000 to 0xFFFF
    //**************************************************
    
    //-------------------- PAGE 0 ----------------------------------------------
    
    #define MAX_PRESSURE_MAX        MAX_16_BITS     /**< Length in bytes of numeric values. */
    #define MAX_INSPIRATION_TIME    MAX_16_BITS     /**< Length in bytes of numeric values. */
    #define MAX_EXPIRATION_TIME     MAX_16_BITS     /**< Length in bytes of numeric values. */
    #define MAX_PWM5_DUTY           MAX_8_BITS      /**< Length in bytes of numeric values. */
    #define MAX_PWM5_FREC           MAX_32_BITS     /**< Length in bytes of numeric values. */
    #define MAX_PRESSURE_INS        MAX_32_BITS     /**< Length in bytes of numeric values. */
    #define MAX_PRESSURE_EXP        MAX_32_BITS     /**< Length in bytes of numeric values. */

    #define INIT_PAGE_0             0               /**< Start address of page 0 in EEPROM. */ 
    #define ADDR_PRESSURE_MAX       INIT_PAGE_0     /**< Address of variable. */                    
    #define ADDR_INSPIRATION_TIME   INIT_PAGE_0+MAX_PRESSURE_MAX    /**< Address of variable. */
    #define ADDR_EXPIRATION_TIME    INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME   /**< Address of variable. */
    #define ADDR_PWM5_DUTY          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME   /**< Address of variable. */
    #define ADDR_PWM5_FREC          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY /**< Address of variable. */
    #define ADDR_PRESSURE_INS       INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC   /**< Address of variable. */
    #define ADDR_PRESSURE_EXP       INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY+MAX_PWM5_FREC+MAX_PRESSURE_INS /**< Address of variable. */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
    uint16_t deviceAddressSlave1;   /**< EEPROM slave address. */

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Initialize I2C configuration
     */
    void i2c_init (void);
    
    /**
     * @brief I2C1 period for comunication
     */
    void i2c_ID_1_dly(void);
    
    /**
     * @brief I2C1 start bit sequence
     */
    void i2c_ID_1_startp(void);
    
    /**
     * @brief I2C1 stop bit sequence
     */
    void i2c_ID_1_stopp(void);
    
    /**
     * @brief Write data in I2C1 comunication port
     * @code
     *      uint8_t ack = i2c_ID_1_writep(data);
     * @endcode
     * @param  d    
     * @return Function return ACK    
     */
    uint8_t i2c_ID_1_writep(uint8_t d);
    
    /**
     * @brief Read data of I2C1 comunication port
     * @code
     *      uint8_t data = i2c_ID_1_readp(0);
     * @endcode
     * @param  ack  ACK to be put when read data, 1 for ACK and 0 for NO ACK   
     * @return Function return data read    
     */
    uint8_t i2c_ID_1_readp(uint8_t ack);
    
    /**
     * @brief Check if EEPROM is ready for comunication
     * @param  addr  Address to check   
     * @return return ACK if EEPROM is ready  
     */
    uint8_t ext_eeprom_ready_ID_1(char addr);
    
    /**
     * @brief I2C2 period for comunication
     */
    void i2c_ID_2_dly(void);
    
    /**
     * @brief I2C2 start bit sequence
     */
    void i2c_ID_2_startp(void);
    
    /**
     * @brief I2C2 stop bit sequence
     */
    void i2c_ID_2_stopp(void);
    
    /**
     * @brief Write data in I2C2 comunication port
     * @code
     *      uint8_t ack = i2c_ID_2_writep(data);
     * @endcode
     * @param  d    
     * @return Function return ACK    
     */
    uint8_t i2c_ID_2_writep(uint8_t d);
    
    /**
     * @brief Read data of I2C2 comunication port
     * @code
     *      uint8_t data = i2c_ID_2_readp(0);
     * @endcode
     * @param  ack  ACK to be put when read data, 1 for ACK and 0 for NO ACK   
     * @return Function return data read    
     */
    uint8_t i2c_ID_2_readp(uint8_t ack);

    /**
     * @brief Write string in EEPROM
     * @code
     *      write_string_eeprom(ADDR_PWM5_FREC, "Hello", 5);
     * @endcode
     * @param  address      Address in EEPROM to start write   
     * @param  string       String to wirte
     * @param  int_length   Length in bytes of string  
     */
    void write_string_eeprom(uint32_t address, char * string, uint16_t string_length);

    /**
     * @brief Write string in EEPROM, this function write a single page
     * @param  address      Address in EEPROM to write  
     * @param  string       String to write  
     * @param  string_length      Address in EEPROM to read  
     */
    void write_string_eeprom_w(uint32_t address, char * string, uint16_t string_length);

    /**
     * @brief Read string from EEPROM
     * @code
     *      read_string_eeprom(ADDR_PWM5_FREC, 10000, INT32);
     * @endcode
     * @param  address      Address in EEPROM to start read   
     * @param  string       Array to tut string readed
     * @param  int_length   Length in bytes of string to read
     */
    void read_string_eeprom(uint32_t address, char * string, uint16_t string_length);

    /**
     * @brief Read a single address in EEPROM
     * @param  address      Address in EEPROM to read  
     * @return Return value of address readed   
     */
    char read_string_eeprom_w(uint32_t address);

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

    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */

/* *****************************************************************************
 End of File
 */
