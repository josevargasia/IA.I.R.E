/* ************************************************************************** */
/**
 * @file app.c
 * @author Ingenierķa Apropiada
 * @date 26/03/2020
 * @brief File containing principal state machine.
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

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
APP_DATA appData;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************
void APP_init(void){
    appData.state = APP_STATE_INIT;
}

void APP_Task(void){
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {   
            sci_ID1_send("<---------- Init App ---------->\n");
            appData.state = APP_STATE_SERVICE_TASKS;
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            if(appData.test_timeout == 0){
                appData.test_timeout = 250;
                sprintf(appData.bufferDisplay, "AN4: %d mV, ADC:%d, prom: %d mV", adcData.values_mv[0], adcData.values[0], adcData.values_2_prom[0]);
                sci_ID1_send(appData.bufferDisplay);
                sprintf(appData.bufferDisplay, "AN5: %d mV, ADC:%d, prom: %d mV, CO2: %d ppm", adcData.values_mv[1], adcData.values[1], adcData.values_2_prom[1], value_ppm_CO2);
                sci_ID1_send(appData.bufferDisplay);
//                sprintf(appData.bufferDisplay, "AN5: %d mV\n", adcData.values_mv[1]);
//                sci_ID1_send(appData.bufferDisplay);
            }
            break;
        }
        default:
        {
            appData.state = APP_STATE_INIT;
            break;
        }
    }
}

/* *****************************************************************************
 End of File
 */
