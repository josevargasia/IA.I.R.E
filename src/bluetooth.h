/* ************************************************************************** */
/**
 * @file bluetooth.h
 * @author Ingeniería Apropiada
 * @date 27/03/2020
 * @brief File containing Bluetooth driver.
 */
/* ************************************************************************** */

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H


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
    #define BLUETOOTH_FRAME_SEND_TIME   500       // in ms
    /**
    * @brief Use enum for define states of states machine.
    */
    typedef enum
    {
        /* Application's state machine's initial state. */
        BLUETOOTH_STATE_INIT=0,           /**< Initial state. */
        BLUETOOTH_STATE_SERVICE_TASKS,    /**< State to manage secondary system tasks. */
        BLUETOOTH_STATE_WRITE,
        BLUETOOTH_STATE_READ,
                
                
        FRAME_STATE_HEADER_INIT_1,
        FRAME_STATE_HEADER_INIT_2,
        FRAME_STATE_HEADER_BODY,
        FRAME_STATE_HEADER_END_1,
    } BLUETOOTH_STATES;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Bluetooth data structure.
     */
    typedef struct
    {
        /* The application's current state */
        BLUETOOTH_STATES state;           /**< States of states machine. */
        
        uint16_t timeout;               /**< Timeout. */
        
        char readBuff[100];
        uint8_t index_readBuff;
        BLUETOOTH_STATES frame_state;
    } BLUETOOTH_DATA;

    extern BLUETOOTH_DATA bluetoothData;    /**< Manage all variables that bluetooth can use. */
    


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /**
     * @brief Init bluetooth state machine
     */
    void BLUETOOTH_init(void);
    
    /**
     * @brief Bluetooth task.
     */
    void BLUETOOTH_Task(void);
    
    void BLUETOOTH_process_frame(char * frame, uint8_t len);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
