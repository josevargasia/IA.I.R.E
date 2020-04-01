/* ************************************************************************** */
/**
 * @file system_init.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing system initializations.
 */
/* ************************************************************************** */

#ifndef _SYSTEM_INIT_H    /* Guard against multiple inclusion */
#define _SYSTEM_INIT_H


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

    #define PIN_IN          1               /**< Set direction GPIO PIN_IN port. */
    #define PIN_OUT         0               /**< Set direction GPIO PIN_OUT port. */

    // GPIO OUT
    #define TEST_LEDStateIOSet(value)       (TRISBbits.TRISB15 = value)     /**< Set GPIO direction port. */
    #define TEST_LEDStateGet()              PORTBbits.RB15                  /**< Get GPIO state port. */
    #define TEST_LEDStateSet(value)         (LATBbits.LATB15 = value)       /**< Set GPIO state port. */

    #define HBridge_IN1_StateIOSet(value)       (TRISBbits.TRISB3 = value)
    #define HBridge_IN1_StateGet()              PORTBbits.RB3
    #define HBridge_IN1_StateSet(value)         (LATBbits.LATB3 = value)
    
    #define HBridge_IN2_StateIOSet(value)       (TRISBbits.TRISB2 = value)
    #define HBridge_IN2_StateGet()              PORTBbits.RB2
    #define HBridge_IN2_StateSet(value)         (LATBbits.LATB2 = value)

    #define TRIG_StateIOSet(value)       (TRISBbits.TRISB11 = value)
    #define TRIG_StateGet()              PORTBbits.RB11
    #define TRIG_StateSet(value)         (LATBbits.LATB11 = value)

    // GPIO IN
    #define STATE_BLUETOOTHStateIOSet(value)       (TRISBbits.TRISB10 = value)     /**< Set GPIO direction port. */
    #define STATE_BLUETOOTHStateGet()              PORTBbits.RB10                  /**< Get GPIO state port. */
    
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
     * @brief Initialize system configuration
     */
    void system_init (void);
    
    /**
     * @brief Initialize ports configuration
     */
    void ports_init (void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_INIT_H */

/* *****************************************************************************
 End of File
 */
