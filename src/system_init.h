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

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


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

    #define TEST_LEDStateIOSet(value)       (TRISBbits.TRISB15 = value)     /**< Set GPIO direction port. */
    #define TEST_LEDStateGet()              PORTBbits.RB15                  /**< Get GPIO state port. */
    #define TEST_LEDStateSet(value)         (LATBbits.LATB15 = value)       /**< Set GPIO state port. */


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
