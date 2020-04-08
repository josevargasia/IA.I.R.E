
#include "system_definitions.hpp"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

SCI_DATA sciData;   /**< Manage all variables that SCI driver can use. */  

char buffer_tx_sci_ID1[BUFFER_TX_SCI_ID1_SIZE];       /**< SCI buffer TX for UART comunication. */
char buffer_rx_sci_ID1[BUFFER_RX_SCI_ID1_SIZE];       /**< SCI buffer RX for UART comunication. */
char buffer_tx_sci_ID2[BUFFER_TX_SCI_ID2_SIZE];       /**< SCI buffer TX for UART comunication. */
char buffer_rx_sci_ID2[BUFFER_RX_SCI_ID2_SIZE];       /**< SCI buffer RX for UART comunication. */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

uint16_t circBuffGetCount_sci(uint8_t bufferID){
    return sciData.buffer_count[bufferID];
}

uint16_t circBuffPush_sci(char data, uint8_t bufferID){
    //__builtin_disable_interrupts();
    // next is where head will point to after this write.
    sciData.buffer_next[bufferID] = sciData.buffer_head[bufferID] + 1;
    if (sciData.buffer_next[bufferID] >= sciData.buffer_size[bufferID])
        sciData.buffer_next[bufferID] = 0;

    if (sciData.buffer_next[bufferID] == sciData.buffer_tail[bufferID])         // Check if circular buffer is full
        return 0;			// and return with an error.

    *(sciData.buffer[bufferID] + sciData.buffer_head[bufferID]) = data;             // Write data and then move
    sciData.buffer_head[bufferID] = sciData.buffer_next[bufferID];              // Head to next data offset.	
    sciData.buffer_count[bufferID]++;                   // Retun number of bytes in buffer

    //__builtin_enable_interrupts();
    return 1;	// return success to indicate successful push.
}

uint16_t circBuffPop_sci(char *data, uint8_t bufferID){   
//    __builtin_disable_interrupts();
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
//__builtin_enable_interrupts();
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
    
    Serial.begin(115200);
}

/*
void sci_ID1_sendbyte(char data){
    circBuffPush_sci(data, BUFFER_TX_SCI_ID1);
}

void sci_ID1_send(char * string){	  
	uint16_t i;
    uint16_t len = strlen(string);
	for (i = 0; i < len || (len == 0 && string[i] != 0); i++){
		sci_ID1_sendbyte(string[i]);
	}
}
*/

uint16_t sci_ID1_get(char * data){
    uint16_t ret;
    
    if(circBuffGetCount_sci(BUFFER_RX_SCI_ID1) != 0){
        ret = circBuffPop_sci(data, BUFFER_RX_SCI_ID1);
    }else{
        ret = 0;
    }
    
    return ret;
}