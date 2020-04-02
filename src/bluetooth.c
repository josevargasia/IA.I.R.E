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
            if(sci_ID5_get(&data)){
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
                
//                sprintf(send_frame, "m,A%d,B%d,C%d,T%d,1%0.2f,2%0.2f,3%d,4%d,", adcData.values_2_prom[0], adcData.values_2_prom[0], configData.pressure_max, configData.pwm5_duty, respiraData.sp_insp, respiraData.sp_exp, respiraData.t_insp, respiraData.t_exp);
//                sprintf(send_frame, "m,A%d,B%d,C%d,", adcData.values_2_prom[0], adcData.values_2_prom[0], configData.pwm5_duty);
                sprintf(send_frame, "m,A%d.55,B%d.35,C%d,I%0.2f,E%0.2f,", adcData.values_2_prom[0], adcData.values_2_prom[0], configData.pwm5_duty, respiraData.sp_insp, respiraData.sp_exp);
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
    
    index_response_frame += sprintf(&response_frame[index_response_frame], "p,");
    
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
                        respiraData.t_insp = atoi(data);
                        write_int_eeprom(ADDR_INSPIRATION_TIME, respiraData.t_insp, INT16);
                    }
                    //load
                    respiraData.t_insp = read_int_eeprom(ADDR_INSPIRATION_TIME, INT16);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "Q%d,", respiraData.t_insp);
                    break;
                }
                case 'R':
                {
                    if(index_data != 0){
                        //Save
                        respiraData.t_exp = atoi(data);
                        write_int_eeprom(ADDR_EXPIRATION_TIME, respiraData.t_exp, INT16);
                    }
                    //load
                    respiraData.t_exp = read_int_eeprom(ADDR_EXPIRATION_TIME, INT16);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "R%d,", respiraData.t_exp);
                    break;
                }
                case 'S':
                {
                    if(index_data != 0){
                        //Save
                        configData.pwm5_frec = atoi(data);
                        if(configData.pwm5_frec >= 1000 && configData.pwm5_frec <= 50000){
                            write_int_eeprom(ADDR_PWM5_FREC, configData.pwm5_frec, INT32);
                            timer_ID2_set_frecuency(configData.pwm5_frec);
                        }
                    }
                    //load
                    configData.pwm5_frec = read_int_eeprom(ADDR_PWM5_FREC, INT32);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "S%d,", configData.pwm5_frec);
                    break;
                }
                case 'T':
                {
                    if(index_data != 0){
                        //Save
                        configData.pwm5_duty = atoi(data);
                        if(configData.pwm5_duty <= 100){
                            write_int_eeprom(ADDR_PWM5_DUTY, configData.pwm5_duty, INT8);
                            if(configData.pwm5_duty == 10){
                                TRIG_StateSet(0);
//                                appData.test_enable = 0;
                            }else{
                                TRIG_StateSet(1);
//                                appData.test_enable = 1;
                            }
                            
                            pwm_ID5_duty_set(configData.pwm5_duty);
                        }
                    }
                    //load
                    configData.pwm5_duty = read_int_eeprom(ADDR_PWM5_DUTY, INT8);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "T%d,", configData.pwm5_duty);
                    break;
                }
                case 'U':
                {
                    if(index_data != 0){
                        //Save
                        respiraData.sp_insp = atof(data);
                        write_float_eeprom(ADDR_PRESSURE_INS, respiraData.sp_insp);
                    }
                    //load
                    respiraData.sp_insp = read_float_eeprom(ADDR_PRESSURE_INS);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "U%0.2f,", respiraData.sp_insp);
                    break;
                }
                case 'V':
                {
                    if(index_data != 0){
                        //Save
                        respiraData.sp_exp = atof(data);
                        write_float_eeprom(ADDR_PRESSURE_EXP, respiraData.sp_exp);
                    }
                    //load
                    respiraData.sp_exp = read_float_eeprom(ADDR_PRESSURE_EXP);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "V%0.2f,", respiraData.sp_exp);
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
    sci_ID5_send("aa,");
    sci_ID5_send(data);
    sci_ID5_send("zz\r\n");
}
/* *****************************************************************************
 End of File
 */
