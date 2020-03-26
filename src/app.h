/* ************************************************************************** */
/**
 * @file app.h
 * @author Ingeniería Apropiada
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
    
    /**
    * @brief Use enum for define states of states machine in application.
    *
    */
    typedef enum
    {
        /* Application's state machine's initial state. */
        APP_STATE_INIT=0,           /**< Initial state. */
        APP_STATE_SERVICE_TASKS,    /**< State to manage secondary system tasks. */


    } APP_STATES;
    
    
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Application data structure.
     * 
     * 
     */
    typedef struct
    {
        /* The application's current state */
        APP_STATES state;           /**< States of states machine in app. */
        
        char bufferDisplay[50];     /**< Buffer debbug for display messages in UART. */
        
        uint16_t test_timeout;      /**< Test timeout. */
        uint8_t test_led_timeout;   /**< Test timeout for led blink. */
        uint16_t timeout_1seg;      /**< Timeout for count one second in timer 4 interruption. */

    } APP_DATA;

    extern APP_DATA appData;    /**< Manage all variables that application can be use. */
    
    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Init application state machine
     */
    void APP_init(void);
    
    /**
     * @brief Application task, in this task you can put all system tasks.
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
