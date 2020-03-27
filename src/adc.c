/* ************************************************************************** */
/**
 * @file adc.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing ADC driver.
 */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

ADC_DATA adcData;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void adc_init (void){
//    AD1PCFG = 0x00;
    
    // 1. Configure the analog port pins
//    ANSELBbits.ANSB4 = 0;   // Turn ON Anlog functions in port RB4 - AN4
//    ANSELBbits.ANSB5 = 0;   // Turn ON Anlog functions in port RB5 - AN5
    
    // Configuration bits
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CHS  = 0;
    AD1CSSL = 0;
    
    // 2. Select the analog inputs to the ADC multiplexers
    AD1CHSbits.CH0SA = 0b00101; // N/A Select AN5 in Multiplexer A
    
    
    // 3. Select the format of the ADC result using FORM
    AD1CON1bits.FORM = 0;       // Integer 16-bit
    
    // 4. Select the sample clock source
    //MANUAL CONVERSION
    AD1CON1bits.SSRC = 0b111;       //  Internal counter ends sampling and starts conversion (auto convert)
    
    // 4.1. Synchronizing ADC Operations to Internal or External Events
    //N/A
    // 4.2. Selecting Automatic or Manual Sampling
    // AUTOMATIC SAMPLING
    AD1CON1bits.ASAM = 1;           // enables Auto-Sample mode
    
    // 5. Select the voltage reference source using
    AD1CON2bits.VCFG = 0;       // VREF+ and VREF-
    
    // 6. Selecting the Scan Mode
    //SCAN MODE ENABLE
    AD1CON2bits.CSCNA = 1;      // Enable Channel Scan for Multiplexer A
    
    // 7. Setting the Number of Conversions per Interrupt
//    AD1CON2bits.SMPI = 1;       // Number of conversions before Interrupt
    
    // 8. Buffer Fill Mode 
    AD1CON2bits.BUFM = 0;       // Buffer configured as one 16-word
    
    // 9. Selecting the MUX to be Connected to the ADC
    AD1CON2bits.ALTS = 0;       // Always use Sample A input multiplexer settings
     
    // 10. Selecting the ADC Conversion Clock Source and Prescaler
    AD1CON3bits.ADRC = 0;       // Clock derived from Peripheral Bus Clock (PBCLK)
    AD1CON3bits.SAMC = 10;       //
            
//    AD1CSSLbits.CSSL4 = 1;      // Select AN4
//    AD1CSSLbits.CSSL5 = 1;      // Select AN5
    
//    set_ADC_ports(2, PORT_AN4 | PORT_AN5);
    
    
    // 11.  Turn the ADC module
    AD1CON1bits.ON = 1;
    
}

void adc_set_ports(uint8_t number, uint32_t ports){
    AD1CON2bits.SMPI = number-1;    // Number of conversion at same time
    AD1CSSL = ports;                // Ports for convert
}

void adc_get_samples(void){
        
    AD1CON1bits.SAMP = 1; // start Converting
    while (!(AD1CON1bits.DONE));// conversion done?
        
    adcData.values[0] = ADC1BUF0;
    adcData.values[1] = ADC1BUF1;
    
    adcData.values_mv[0] = (adcData.values[0]*3300)/1024;
    adcData.values_mv[1] = (adcData.values[1]*3300)/1024;
    
    adcData.values_2[0][adcData.values_2_count] = adcData.values_mv[0];
    adcData.values_2[1][adcData.values_2_count++] = adcData.values_mv[1];
    
    if(adcData.values_2_count >= ADC_MAX_NUM_SAMPLE_PROM){
        adcData.values_2_count = 0;
        adcData.values_2_prom[0] = 0;
        adcData.values_2_prom[1] = 0;
        int i;
        for(i = 0; i < ADC_MAX_NUM_SAMPLE_PROM; i++){
            adcData.values_2_prom[0] += adcData.values_2[0][i];
            adcData.values_2_prom[1] += adcData.values_2[1][i];
        }
        adcData.values_2_prom[0] /= ADC_MAX_NUM_SAMPLE_PROM; 
        adcData.values_2_prom[1] /= ADC_MAX_NUM_SAMPLE_PROM; 
        get_sample_ppm_CO2();
    }
    
}
/* *****************************************************************************
 End of File
 */
