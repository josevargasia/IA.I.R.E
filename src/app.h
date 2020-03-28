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
    
    #define PWM1_PERIOD  100    /**< PWM1 PERIOD. */
    
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
        
        char bufferDisplay[100];     /**< Buffer debbug for display messages in UART. */
        
        uint16_t test_timeout;      /**< Test timeout. */
        uint8_t test_led_timeout;   /**< Test timeout for led blink. */
        uint16_t timeout_1seg;      /**< Timeout for count one second in timer 4 interruption. */
        
        uint16_t PWM1_period_count;       /**< Timeout for PWM1. */
        uint16_t PWM1_duty;               /**< Duty for PWM1 in percent. */
        
    } APP_DATA;

    extern APP_DATA appData;    /**< Manage all variables that application can be use. */
    
    typedef struct
    {
        /* The application's current state */
        
        uint16_t pressure_max;
        uint16_t inspiration_time;
        uint16_t expiration_time;
        
    } CONFIG_DATA;

    extern CONFIG_DATA configData;    
    
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
    
    /**
     * @brief Init PWM1
     */
    void PWM1_init(void);
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_H */

/* *****************************************************************************
 End of File
 */
