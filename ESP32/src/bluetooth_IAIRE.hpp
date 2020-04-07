
#include <Arduino.h>
#include <BluetoothSerial.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */
#define BLUETOOTH_FRAME_SEND_TIME   100 //50       /**< Send time to bluetooth in miliseconds. */

#define BLUETOOTH_DISCONNECTED      0
#define BLUETOOTH_CONNECTED         1

/**
* @brief Use enum for define states of states machine.
*/
typedef enum
{
    /* Application's state machine's initial state. */
    BLUETOOTH_STATE_INIT=0,           /**< Initial state. */
    BLUETOOTH_STATE_WRITE,            /**< State to write frames to bluetooth. */
    BLUETOOTH_STATE_READ,             /**< State to read frames from bluetooth. */
            
            
    FRAME_STATE_HEADER_INIT_1,          /**< State to read header start 1. */
    FRAME_STATE_HEADER_INIT_2,          /**< State to read header start 2. */
    FRAME_STATE_HEADER_BODY,            /**< State to read body frame. */
    FRAME_STATE_HEADER_END_1,           /**< State to read header end 1. */
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
    BLUETOOTH_STATES state;             /**< States of state machine. */
        
    BLUETOOTH_STATES frame_state;       /**< States of read frame state machine. */

    uint8_t connection_state;           /**< States of connection. */

    uint16_t timeout_led_blink;         /**< Timeout led blink. */
    
    uint16_t timeout;                   /**< Timeout. */
    
    char readBuff[100];                 /**< Array to save read frame from bluetooth. */
    uint8_t index_readBuff;             /**< Index of array to save read frame from bluetooth. */
    
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

/**
 * @brief Process frame from bluetooth
 * @param  frame    Frame to process     
 * @param  len      Length of frame to process
 */
void BLUETOOTH_process_frame(char * frame, uint8_t len);

/**
 * @brief Send string to bluetooth
 * @code
 *      BLUETOOTH_send_frame("Hello...");
 * @endcode
 * @param  data Pointer of string to send to bluetooth     
 */
void BLUETOOTH_send_frame(char * data);

void BLUETOOTH_callback_ISR (esp_spp_cb_event_t event, esp_spp_cb_param_t *param);