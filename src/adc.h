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

#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H


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
#define PORT_AN0    0b0000000000000001
#define PORT_AN1    0b0000000000000010
#define PORT_AN2    0b0000000000000100
#define PORT_AN3    0b0000000000001000
#define PORT_AN4    0b0000000000010000
#define PORT_AN5    0b0000000000100000
#define PORT_AN6    0b0000000001000000
#define PORT_AN7    0b0000000010000000
#define PORT_AN8    0b0000000100000000
#define PORT_AN9    0b0000001000000000
#define PORT_AN10   0b0000010000000000
#define PORT_AN11   0b0000100000000000
#define PORT_AN12   0b0001000000000000
#define PORT_AN13   0b0010000000000000
#define PORT_AN14   0b0100000000000000
#define PORT_AN15   0b1000000000000000


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************
    typedef struct
    {
        uint16_t values[5];
        uint16_t values_mv[5];
        
        uint16_t values_2[5][1000];
        uint16_t values_2_count;
        uint32_t values_2_prom[5];

    } ADC_DATA;

    extern ADC_DATA adcData;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    void adc_init (void);
    void adc_set_ports(uint8_t number, uint32_t ports);
    void adc_get_samples();
    void adc_get_samples_mV(uint16_t *adcValues, uint8_t number);
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ADC_H */

/* *****************************************************************************
 End of File
 */
