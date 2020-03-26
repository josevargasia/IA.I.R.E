/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SCI_H    /* Guard against multiple inclusion */
#define _SCI_H


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
    #define NUMBER_OF_SCI_BUFFERS       2
    
    #define BUFFER_TX_SCI_ID1           0
    #define BUFFER_RX_SCI_ID1           1

    #define BUFFER_TX_SCI_ID1_SIZE      200
    #define BUFFER_RX_SCI_ID1_SIZE      200

    #define RX_INVERT_ON            1
    #define RX_INVERT_OFF           0

    #define TX_INVERT_ON            1
    #define TX_INVERT_OFF           0

    #define NO_PARITY_8_BIT         0   // 8-bit data, no parity
    #define EVEN_PARITY_8_BIT       1   // 8-bit data, even parity
    #define ODD_PARITY_8_BIT        2   // 8-bit data, odd parity
    #define NO_PARITY_9_BIT         3   // 9-bit data, no parity

    #define STOP_BIT_1              0   // 1 Stop bits
    #define STOP_BIT_2              1   // 2 Stop bits


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */
    char buffer_tx_sci_ID1[BUFFER_TX_SCI_ID1_SIZE];       // 
    char buffer_rx_sci_ID1[BUFFER_RX_SCI_ID1_SIZE];       // 
    
    typedef struct
    {
        char * buffer[NUMBER_OF_SCI_BUFFERS];
        uint16_t buffer_size[NUMBER_OF_SCI_BUFFERS];
        uint16_t buffer_tail[NUMBER_OF_SCI_BUFFERS];
        uint16_t buffer_head[NUMBER_OF_SCI_BUFFERS];
        uint16_t buffer_next[NUMBER_OF_SCI_BUFFERS];
        uint16_t buffer_count[NUMBER_OF_SCI_BUFFERS];
    }SCI_DATA;

    // *****************************************************************************

    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    
    uint16_t circBuffPush_sci(char data, uint8_t bufferID);
    uint16_t circBuffPop_sci(char *data, uint8_t bufferID);    
    void clean_buffer_sci(uint8_t bufferID);
    
    void sci_init(void);
    
    void sci_ID1_setup (uint32_t sci_baud, uint8_t rx_invert, uint8_t tx_invert, uint8_t parity_nbits, uint8_t stop_bits);
    void sci_ID1_sendbyte(char data);
    void sci_ID1_send(char * string);
    uint16_t sci_ID1_get(char * data);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _SCI_H */

/* *****************************************************************************
 End of File
 */
