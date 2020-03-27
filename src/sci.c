/* ************************************************************************** */
/**
 * @file sci.c
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing SCI driver that manage circular buffers.
 */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

uint16_t circBuffPush_sci(char data, uint8_t bufferID){
    __builtin_disable_interrupts();
    // next is where head will point to after this write.
    sciData.buffer_next[bufferID] = sciData.buffer_head[bufferID] + 1;
    if (sciData.buffer_next[bufferID] >= sciData.buffer_size[bufferID])
        sciData.buffer_next[bufferID] = 0;

    if (sciData.buffer_next[bufferID] == sciData.buffer_tail[bufferID])         // Check if circular buffer is full
        return 0;			// and return with an error.

    *(sciData.buffer[bufferID] + sciData.buffer_head[bufferID]) = data;             // Write data and then move
    sciData.buffer_head[bufferID] = sciData.buffer_next[bufferID];              // Head to next data offset.	
    sciData.buffer_count[bufferID]++;                   // Retun number of bytes in buffer

    __builtin_enable_interrupts();
    return 1;	// return success to indicate successful push.
}

uint16_t circBuffPop_sci(char *data, uint8_t bufferID){   
    __builtin_disable_interrupts();
    // if the head isn't ahead of the tail, we don't have any characters
    if (sciData.buffer_head[bufferID] == sciData.buffer_tail[bufferID])         // check if circular buffer is empty
        return 0;           // and return with an error

    // next is where tail will point to after this read.
    sciData.buffer_next[bufferID] = sciData.buffer_tail[bufferID] + 1;
    if(sciData.buffer_next[bufferID] >= sciData.buffer_size[bufferID])
        sciData.buffer_next[bufferID] = 0;

    *data = *(sciData.buffer[bufferID] + sciData.buffer_tail[bufferID]);             // Read data and then move
    sciData.buffer_tail[bufferID] = sciData.buffer_next[bufferID];              // tail to next data offset.	
    sciData.buffer_count[bufferID]--;                   // Retun number of bytes in buffer
__builtin_enable_interrupts();
    return 1;  // return success to indicate successful push. 
}
    
void clean_buffer_sci(uint8_t bufferID){
    sciData.buffer_head[bufferID] = 0;
    sciData.buffer_tail[bufferID] = 0;
    sciData.buffer_next[bufferID] = 0;
    sciData.buffer_count[bufferID] = 0;
    memset(sciData.buffer[bufferID], 0x00, sciData.buffer_size[bufferID]);
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void sci_init(void){
    sciData.buffer[BUFFER_TX_SCI_ID1] = buffer_tx_sci_ID1;
    sciData.buffer[BUFFER_RX_SCI_ID1] = buffer_rx_sci_ID1;
    
    sciData.buffer_size[BUFFER_TX_SCI_ID1] = BUFFER_TX_SCI_ID1_SIZE;
    sciData.buffer_size[BUFFER_RX_SCI_ID1] = BUFFER_RX_SCI_ID1_SIZE;
    
    memset(sciData.buffer_head, 0x00, NUMBER_OF_SCI_BUFFERS);
    memset(sciData.buffer_tail, 0x00, NUMBER_OF_SCI_BUFFERS);
    memset(sciData.buffer_next, 0x00, NUMBER_OF_SCI_BUFFERS);
    memset(sciData.buffer_count, 0x00, NUMBER_OF_SCI_BUFFERS);
    
    sci_ID1_setup(115200, RX_INVERT_OFF, TX_INVERT_OFF, NO_PARITY_8_BIT, STOP_BIT_1);
}

/**********************************************
 ************ SCI ID1 FUNCTIONS ***************     
 **********************************************/
void sci_ID1_setup (uint32_t sci_baud, uint8_t rx_invert, uint8_t tx_invert, uint8_t parity_nbits, uint8_t stop_bits){
    // TX RA15
    // RX RA14
    
    U1MODEbits.ON = 0;
    
    // Setup
    U1MODE = 0b0000000000000000;
    U1STA = 0b0000000000000000;
    
    U1BRG = ((SYS_CLK_BUS_PERIPHERAL/16)/sci_baud) - 1;   // Baud Rate
    
    U1MODEbits.RXINV = rx_invert;
    U1STAbits.UTXINV = tx_invert;
    U1MODEbits.PDSEL = parity_nbits;
    U1MODEbits.STSEL = stop_bits;
            
    // Interrupt
    IPC7bits.U1IP = 2;      //Interrupt priority
    IPC7bits.U1IS = 0;      //Interrupt sub-priority
    
    IFS1bits.U1RXIF = 0;    //clear interrupt flag
    IEC1bits.U1RXIE = 0;    //Enable UART1 RX interrupt
    IFS1bits.U1TXIF = 0;    //clear interrupt flag
    IEC1bits.U1TXIE = 0;    //Disable UART1 TX interrupt
    
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;
    
    // Buffers    
    clean_buffer_sci(BUFFER_TX_SCI_ID1);
    clean_buffer_sci(BUFFER_RX_SCI_ID1);
}

void sci_ID1_sendbyte(char data){
    circBuffPush_sci(data, BUFFER_TX_SCI_ID1);
    IEC1bits.U1TXIE = 1;
}

void sci_ID1_send(char * string){	  
	uint16_t i;
    uint16_t len = strlen(string);
	for (i = 0; i < len || (len == 0 && string[i] != 0); i++){
		sci_ID1_sendbyte(string[i]);
	}
}

uint16_t sci_ID1_get(char * data){
    uint16_t ret;
    
    IEC1bits.U1RXIE = 0;
	ret = circBuffPop_sci(data, BUFFER_RX_SCI_ID1);
    IEC1bits.U1RXIE = 1;
    
    return ret;
}


/* *****************************************************************************
 End of File
 */