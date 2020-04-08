#include <Arduino.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define NUMBER_OF_SCI_BUFFERS       2       /**< Numer of SCI buffers. */
    
#define BUFFER_TX_SCI_ID1           0       /**< ID of SCI buffer TX for UART comunication. */
#define BUFFER_RX_SCI_ID1           1       /**< ID of SCI buffer RX for UART comunication. */
#define BUFFER_TX_SCI_ID2           3       /**< ID of SCI buffer TX for UART comunication. */
#define BUFFER_RX_SCI_ID2           4       /**< ID of SCI buffer RX for UART comunication. */

#define BUFFER_TX_SCI_ID1_SIZE      200     /**< Size of SCI buffer TX for UART comunication. */
#define BUFFER_RX_SCI_ID1_SIZE      200     /**< Size of SCI buffer RX for UART comunication. */
#define BUFFER_TX_SCI_ID2_SIZE      200     /**< Size of SCI buffer TX for UART comunication. */
#define BUFFER_RX_SCI_ID2_SIZE      200     /**< Size of SCI buffer RX for UART comunication. */


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************


/**
 * @brief SCI data structure.
 */
typedef struct
{
    char * buffer[NUMBER_OF_SCI_BUFFERS];           /**< Pointer array for SCI buffers. */
    uint16_t buffer_size[NUMBER_OF_SCI_BUFFERS];    /**< Array of size for SCI buffers. */
    uint16_t buffer_tail[NUMBER_OF_SCI_BUFFERS];    /**< Array of tails index for SCI buffers. */
    uint16_t buffer_head[NUMBER_OF_SCI_BUFFERS];    /**< Array of heads index for SCI buffers. */
    uint16_t buffer_next[NUMBER_OF_SCI_BUFFERS];    /**< Array of next index for SCI buffers. */
    uint16_t buffer_count[NUMBER_OF_SCI_BUFFERS];   /**< Array of number of characters in SCI buffers. */    
}SCI_DATA;

 

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Save a character in a specific circular buffer
 * @code
 *      circBuffPush_sci(data, BUFFER_TX_SCI_ID5);
 * @endcode
 * @param data          Character to be saved in buffer
 * @param bufferID      ID of buffer to be saved
 * @return Function return 1 if data save and 0 if data can't save
 */
uint16_t circBuffPush_sci(char data, uint8_t bufferID);

/**
 * @brief Load a character in a specific circular buffer
 * @code
 *      uint16_t ret = circBuffPop_sci(&data, BUFFER_RX_SCI_ID5);
 * @endcode
 * @param  data          Pointer of character to be loaded of buffer
 * @param  bufferID      ID of buffer to be loaded
 * @return Function return 1 if data load and 0 if data can't load
 */
uint16_t circBuffPop_sci(char *data, uint8_t bufferID);    

/**
 * @brief Erase all characters in a specific circular buffer
 * @code
 *      clean_buffer_sci(BUFFER_TX_SCI_ID5);
 * @endcode
 * @param  bufferID      ID of buffer to be erased
 */
void clean_buffer_sci(uint8_t bufferID);


/**
 * @brief Initialize SCI configuration
 */
void sci_init(void);

/**
 * @brief Write a byte in UART TX port
 * @code
 *      sci_ID1_sendbyte('H');
 * @endcode
 * @param  data      Character to be put in UART TX port
 */
void sci_ID1_sendbyte(char data);

/**
 * @brief Write a string in UART TX port
 * @code
 *      sci_ID1_send("Hello world...");
 * @endcode
 * @param  string   String to be put in UART TX port
 */
void sci_ID1_send(char * string);

/**
 * @brief Read a byte of UART RX port
 * @code
 *      sci_ID1_get(&data);
 * @endcode
 * @param  data     Pointer of character to be read of UART RX port
 */
uint16_t sci_ID1_get(char * data);