/* ************************************************************************** */
/**
 * @file bluetooth.c
 * @author Ingeniería Apropiada
 * @date 27/03/2020
 * @brief File containing Bluetooth driver.
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

BLUETOOTH_DATA bluetoothData;    /**< Manage all variables that bluetooth can use. */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */




/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

void BLUETOOTH_init(void){
    bluetoothData.state = BLUETOOTH_STATE_INIT;
}

void BLUETOOTH_Task(void){
    switch ( bluetoothData.state )
    {
        case BLUETOOTH_STATE_INIT:
        {   
            bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_1;
            bluetoothData.index_readBuff = 0;
            bluetoothData.timeout = BLUETOOTH_FRAME_SEND_TIME;
            bluetoothData.state = BLUETOOTH_STATE_READ;
            break;
        }
        case BLUETOOTH_STATE_READ:
        {
            char data;
            if(sci_ID1_get(&data)){
//                sci_ID1_sendbyte(data);
                switch(bluetoothData.frame_state){
                    case FRAME_STATE_HEADER_INIT_1:
                    {
                        if(data == 'a'){
                            bluetoothData.index_readBuff = 0;
                            memset(bluetoothData.readBuff, 0x00, sizeof(bluetoothData.readBuff));
                            bluetoothData.readBuff[bluetoothData.index_readBuff++] = data;
                            bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_2;
                        }
                        break;
                    }
                    case FRAME_STATE_HEADER_INIT_2:
                    {
                        if(data == 'a'){
                            bluetoothData.readBuff[bluetoothData.index_readBuff++] = data;
                            bluetoothData.frame_state = FRAME_STATE_HEADER_BODY;
                        }else{
                            bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_1;
                        }
                        break;
                    }
                    case FRAME_STATE_HEADER_BODY:
                    {
                        bluetoothData.readBuff[bluetoothData.index_readBuff++] = data;
                        if(data == 'a'){
                            bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_2;
                        }else if(data == 'z'){
                            bluetoothData.frame_state = FRAME_STATE_HEADER_END_1;
                        }
                        break;
                    }
                    case FRAME_STATE_HEADER_END_1:
                    {
                        if(data == 'z'){
                            bluetoothData.readBuff[bluetoothData.index_readBuff++] = data;
                            BLUETOOTH_process_frame(bluetoothData.readBuff, bluetoothData.index_readBuff);
                        }
                        bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_1;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            
            bluetoothData.state = BLUETOOTH_STATE_WRITE;
            break;
        }
        case BLUETOOTH_STATE_WRITE:
        {
            if(bluetoothData.timeout == 0){
                char send_frame[50];
                
                
                adc_get_sample_average();
                
                sprintf(send_frame, "A%d,B%dmV,C%d,D,", value_ppm_CO2, adcData.values_2_prom[1], (uint16_t)pow(4,2));
                BLUETOOTH_send_frame(send_frame);
                
//                sprintf(appData.bufferDisplay, "AN5: %d mV, CO2: %d ppm\r\n", adcData.values_2_prom[1], value_ppm_CO2);
//                sci_ID1_send(appData.bufferDisplay);
                
                bluetoothData.timeout = BLUETOOTH_FRAME_SEND_TIME;
            }
            bluetoothData.state = BLUETOOTH_STATE_READ;
            break;
        }
        default:
        {
            bluetoothData.state = BLUETOOTH_STATE_INIT;
            break;
        }
    }
}

void BLUETOOTH_process_frame(char * frame, uint8_t len){
    int i;
    char label;
    char data[20], response_frame[100];
    uint8_t index_data, index_response_frame = 0;
    
    for(i = 0; i < len; i++){
        if(frame[i] == ','){
            i++;
            label = frame[i++];
            index_data = 0;
            while(frame[i]!= ',' && i < len && index_data < 20){
                data[index_data++] = frame[i++];
                data[index_data] = 0x00;
            }
            i--;
            switch(label){
                case 'P':
                {
                    if(index_data != 0){
                        //Save
                        configData.pressure_max = atoi(data);
                        write_int_eeprom(ADDR_PRESSURE_MAX, configData.pressure_max, INT16);
                    }
                    //load
                    configData.pressure_max = read_int_eeprom(ADDR_PRESSURE_MAX, INT16);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "P%d,", configData.pressure_max);
                    break;
                }
                case 'Q':
                {
                    if(index_data != 0){
                        //Save
                        configData.inspiration_time = atoi(data);
                        write_int_eeprom(ADDR_INSPIRATION_TIME, configData.inspiration_time, INT16);
                    }
                    //load
                    configData.inspiration_time = read_int_eeprom(ADDR_INSPIRATION_TIME, INT16);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "Q%d,", configData.inspiration_time);
                    break;
                }
                case 'R':
                {
                    if(index_data != 0){
                        //Save
                        configData.expiration_time = atoi(data);
                        write_int_eeprom(ADDR_EXPIRATION_TIME, configData.expiration_time, INT16);
                    }
                    //load
                    configData.expiration_time = read_int_eeprom(ADDR_EXPIRATION_TIME, INT16);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "R%d,", configData.expiration_time);
                    break;
                }
                case 'S':
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    
    // Send response frame
    BLUETOOTH_send_frame(response_frame);
    
}

void BLUETOOTH_send_frame(char * data){
    sci_ID1_send("aa,");
    sci_ID1_send(data);
    sci_ID1_send("zz\r\n");
}
/* *****************************************************************************
 End of File
 */
