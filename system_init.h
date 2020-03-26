/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
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

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    #define PIN_IN          1
    #define PIN_OUT         0

    #define TEST_LEDStateIOSet(value)       (TRISBbits.TRISB15 = value)
    #define TEST_LEDStateGet()              PORTBbits.RB15
    #define TEST_LEDStateSet(value)         (LATBbits.LATB15 = value)

    
    
//    #define TEST_LED        LATBbits.LATB15

    

//    #define PIN_SCL1	 TRISGbits.TRISG2
//    #define PIN_SDA1	 TRISGbits.TRISG3
//
//    #define PIN_SCL1_IN	 PORTGbits.RG2
//    #define PIN_SDA1_IN	 PORTGbits.RG3
//
//    #define PIN_SCL1_OUT LATGbits.LATG2
//    #define PIN_SDA1_OUT LATGbits.LATG3

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************




    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    void system_init (void);
    void ports_init (void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_INIT_H */

/* *****************************************************************************
 End of File
 */
