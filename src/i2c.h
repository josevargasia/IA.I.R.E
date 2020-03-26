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
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************



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


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */

/* *****************************************************************************
 End of File
 */
