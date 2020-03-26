/* ************************************************************************** */
/**
 * @file app.h
 * @author Ingenierķa Apropiada
 * @date 26/03/2020
 * @brief File containing principal state machine.
 *
 */
/* ************************************************************************** */

#ifndef _APP_H    /* Guard against multiple inclusion */
#define _APP_H


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
    /**
    * @brief Use enum for define states of states machine in app.
    *
    */
    typedef enum
    {
        /* Application's state machine's initial state. */
        APP_STATE_INIT=0,
        APP_STATE_SERVICE_TASKS,


    } APP_STATES;
    
    
    
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
        /* The application's current state */
        APP_STATES state;           /**< States of states machine in app. */
        
        char bufferDisplay[50];
        
        uint16_t test_timeout;
        uint8_t test_led_timeout;
        uint16_t timeout_1seg;

    } APP_DATA;

    extern APP_DATA appData;
    
    
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
     * @brief Init application state machine
     * 
     */
    void APP_init(void);
    
    /**
     * @brief Application task, in this task you can put all system tasks.
     * 
     */
    void APP_Task(void);
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_H */

/* *****************************************************************************
 End of File
 */
