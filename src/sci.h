/* ************************************************************************** */
/**
 * @file sci.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing SCI driver that manage circular buffers.
 */
/* ************************************************************************** */

#ifndef _SCI_H    /* Guard against multiple inclusion */
#define _SCI_H


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

    #define NUMBER_OF_SCI_BUFFERS       2       /**< Numer of SCI buffers. */
    
    #define BUFFER_TX_SCI_ID1           0       /**< ID of SCI buffer TX for UART1 comunication. */
    #define BUFFER_RX_SCI_ID1           1       /**< ID of SCI buffer RX for UART1 comunication. */

    #define BUFFER_TX_SCI_ID1_SIZE      200     /**< Size of SCI buffer TX for UART1 comunication. */
    #define BUFFER_RX_SCI_ID1_SIZE      200     /**< Size of SCI buffer RX for UART1 comunication. */

    #define RX_INVERT_ON            1   /**< Set INVERT UART polarity for RX pin. */
    #define RX_INVERT_OFF           0   /**< Set NO INVERT UART polarity for RX pin. */

    #define TX_INVERT_ON            1   /**< Set INVERT UART polarity for TX pin. */
    #define TX_INVERT_OFF           0   /**< Set NO INVERT UART polarity for TX pin. */

    #define NO_PARITY_8_BIT         0   /**< Set 8-bit data, no parity for UART comunication. */
    #define EVEN_PARITY_8_BIT       1   /**< Set 8-bit data, even parity for UART comunication. */
    #define ODD_PARITY_8_BIT        2   /**< Set 8-bit data, odd parity for UART comunication. */
    #define NO_PARITY_9_BIT         3   /**< Set 9-bit data, no parity for UART comunication. */

    #define STOP_BIT_1              0   /**< Set 1 Stop bits for UART comunication. */
    #define STOP_BIT_2              1   /**< Set 2 Stop bits for UART comunication. */


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    char buffer_tx_sci_ID1[BUFFER_TX_SCI_ID1_SIZE];       /**< SCI buffer TX for UART1 comunication. */
    char buffer_rx_sci_ID1[BUFFER_RX_SCI_ID1_SIZE];       /**< SCI buffer RX for UART1 comunication. */
    
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
    
    SCI_DATA sciData;   /**< Manage all variables that SCI driver can use. */    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    
    /**
     * @brief Save a character in a specific circular buffer
     * @code
     *      circBuffPush_sci(data, BUFFER_TX_SCI_ID1);
     * @endcode
     * @param data          Character to be saved in buffer
     * @param bufferID      ID of buffer to be saved
     * @return Function return 1 if data save and 0 if data can't save
     */
    uint16_t circBuffPush_sci(char data, uint8_t bufferID);
    
    /**
     * @brief Load a character in a specific circular buffer
     * @code
     *      uint16_t ret = circBuffPop_sci(&data, BUFFER_RX_SCI_ID1);
     * @endcode
     * @param  data          Pointer of character to be loaded of buffer
     * @param  bufferID      ID of buffer to be loaded
     * @return Function return 1 if data load and 0 if data can't load
     */
    uint16_t circBuffPop_sci(char *data, uint8_t bufferID);    
    
    /**
     * @brief Erase all characters in a specific circular buffer
     * @code
     *      clean_buffer_sci(BUFFER_TX_SCI_ID1);
     * @endcode
     * @param  bufferID      ID of buffer to be erased
     */
    void clean_buffer_sci(uint8_t bufferID);
    
    /**
     * @brief Initialize SCI configuration
     */
    void sci_init(void);
    
    /**
     * @brief Configure UART 1 comunication
     * @code
     *      sci_ID1_setup(115200, RX_INVERT_OFF, TX_INVERT_OFF, NO_PARITY_8_BIT, STOP_BIT_1);
     * @endcode
     * @param  sci_baud       Configure SCI baud rate
     * @param  rx_invert      Configure polariti of RX
     * @param  tx_invert      Configure polarity of TX
     * @param  parity_nbits   Configure parity and number of bits
     * @param  stop_bits      Configure stops bits
     */
    void sci_ID1_setup (uint32_t sci_baud, uint8_t rx_invert, uint8_t tx_invert, uint8_t parity_nbits, uint8_t stop_bits);
    
    /**
     * @brief Write a byte in UART1 TX port
     * @code
     *      sci_ID1_sendbyte('H');
     * @endcode
     * @param  data      Character to be put in UART1 TX port
     */
    void sci_ID1_sendbyte(char data);
    
    /**
     * @brief Write a string in UART1 TX port
     * @code
     *      sci_ID1_send("Hello world...");
     * @endcode
     * @param  string   String to be put in UART1 TX port
     */
    void sci_ID1_send(char * string);
    
    /**
     * @brief Read a byte of UART1 RX port
     * @code
     *      sci_ID1_get(&data);
     * @endcode
     * @param  data     Pointer of character to be read of UART1 RX port
     */
    uint16_t sci_ID1_get(char * data);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SCI_H */

/* *****************************************************************************
 End of File
 */
