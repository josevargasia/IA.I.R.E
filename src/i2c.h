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

    #define EEPROM_PAGE_LENGTH      128

    #define EEPROM_SLAVE_ADDRESS_1  0xA0    // 1010 0000
    #define EEPROM_SLAVE_ADDRESS_2  0xA8    // 1010 1000

    //Length in bytes of numeric values 
    #define MAX_32_BITS     4
    #define MAX_16_BITS     2
    #define MAX_8_BITS      1

    //length of numeric values
    #define INT32       32
    #define INT16       16
    #define INT8        8

    //**************************************************
    // First address part - From 0x0000 to 0xFFFF
    //**************************************************
    
    //-------------------- PAGE 0 ----------------------------------------------
    
    #define MAX_PRESSURE_MAX        MAX_16_BITS
    #define MAX_INSPIRATION_TIME    MAX_16_BITS     
    #define MAX_EXPIRATION_TIME     MAX_16_BITS    
    #define MAX_PWM5_DUTY           MAX_8_BITS
    #define MAX_PWM5_FREC           MAX_32_BITS

    #define INIT_PAGE_0             0                                 // page 0 * 128
    #define ADDR_PRESSURE_MAX       INIT_PAGE_0                        
    #define ADDR_INSPIRATION_TIME   INIT_PAGE_0+MAX_PRESSURE_MAX
    #define ADDR_EXPIRATION_TIME    INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME
    #define ADDR_PWM5_DUTY          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME
    #define ADDR_PWM5_FREC          INIT_PAGE_0+MAX_PRESSURE_MAX+MAX_INSPIRATION_TIME+MAX_EXPIRATION_TIME+MAX_PWM5_DUTY

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
    uint16_t deviceAddressSlave1;

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
    
    uint8_t ext_eeprom_ready_ID_1(char direccion);
    
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

    
    void write_string_eeprom(uint32_t address, char * string, uint16_t string_length);

    void write_string_eeprom_w(uint32_t address, char * string, uint16_t string_length);

    void read_string_eeprom(uint32_t address, char * string, uint16_t string_length);

    char read_string_eeprom_w(uint32_t address);

    void write_int_eeprom(uint32_t address, uint32_t number, uint8_t int_length);

    uint32_t read_int_eeprom(uint32_t address, uint8_t int_length);

    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */

/* *****************************************************************************
 End of File
 */
