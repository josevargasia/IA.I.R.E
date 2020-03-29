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
     */
    typedef struct
    {
        /* The application's current state */
        APP_STATES state;           /**< States of states machine in app. */
        
        char bufferDisplay[100];     /**< Buffer debbug for display messages in UART. */
        
        uint16_t test_timeout;      /**< Test timeout. */
        uint8_t test_led_timeout;   /**< Test timeout for led blink. */
        uint16_t timeout_1seg;      /**< Timeout for count one second in timer 4 interruption. */
        
    } APP_DATA;

    extern APP_DATA appData;    /**< Manage all variables that application can be use. */
    
    /**
     * @brief Configuration data structure.
     */
    typedef struct
    {
        uint16_t pressure_max;          /**< Configure pressure max. */
        uint16_t inspiration_time;      /**< Configure inspiration time. */
        uint16_t expiration_time;       /**< Configure expiration time. */
        uint8_t pwm5_duty;              /**< Configure Duty cycle of PWM pump. */
        uint32_t pwm5_frec;             /**< Configure frecuency of PWM pump. */
    } CONFIG_DATA;

    extern CONFIG_DATA configData;    /**< Manage all variables that application can be use to configure system. */
    
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
