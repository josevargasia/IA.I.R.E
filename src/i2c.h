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

#ifndef _I2C_H    /* Guard against multiple inclusion */
#define _I2C_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

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

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /* ************************************************************************** */
    // I2C ID_1
    #define PIN_SCL1	 TRISGbits.TRISG2
    #define PIN_SDA1	 TRISGbits.TRISG3

    #define PIN_SCL1_IN	 PORTGbits.RG2
    #define PIN_SDA1_IN	 PORTGbits.RG3

    #define PIN_SCL1_OUT LATGbits.LATG2
    #define PIN_SDA1_OUT LATGbits.LATG3

    // I2C ID_2
    #define PIN_SCL2	 TRISAbits.TRISA2
    #define PIN_SDA2	 TRISAbits.TRISA3

    #define PIN_SCL2_IN	 PORTAbits.RA2
    #define PIN_SDA2_IN	 PORTAbits.RA3

    #define PIN_SCL2_OUT LATAbits.LATA2
    #define PIN_SDA2_OUT LATAbits.LATA3
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
    /**
      @Function
        void i2c_init (void)

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Precondition
        List and describe any required preconditions. If there are no preconditions,
        enter "None."

      @Parameters
        @param param1 Describe the first parameter to the function.
    
        @param param2 Describe the second parameter to the function.

      @Returns
        List (if feasible) and describe the return values of the function.
        <ul>
          <li>1   Indicates an error occurred
          <li>0   Indicates an error did not occur
        </ul>

      @Remarks
        Describe any special behavior not described above.
        <p>
        Any additional remarks.

      @Example
        @code
        if(ExampleFunctionName(1, 2) == 0)
        {
            return 3;
        }
     */
    void i2c_init (void);
    
    void i2c_ID_1_dly(void);
    void i2c_ID_1_startp(void);
    void i2c_ID_1_stopp(void);
    uint8_t i2c_ID_1_writep(uint8_t d);
    uint8_t i2c_ID_1_readp(uint8_t ack);
    
    void i2c_ID_2_dly(void);
    void i2c_ID_2_startp(void);
    void i2c_ID_2_stopp(void);
    uint8_t i2c_ID_2_writep(uint8_t d);
    uint8_t i2c_ID_2_readp(uint8_t ack);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _I2C_H */

/* *****************************************************************************
 End of File
 */
