/* ************************************************************************** */
/**
 * @file bluetooth_IAIRE.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing Bluetooth driver.
 */
/* ************************************************************************** */

#include "system_definitions.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;       /**< Manage bluetooth serial comunication. */

BLUETOOTH_DATA bluetoothData;    /**< Manage all variables that bluetooth can use. */

void BLUETOOTH_init(void){
  //BLUETOOTH SETUP
  SerialBT.register_callback(BLUETOOTH_callback_ISR);
  SerialBT.begin("IA.I.R.E"); //Bluetooth device name

  Serial.println("The device started, now you can pair it with bluetooth!");

  //TASK SETUP
  bluetoothData.state = BLUETOOTH_STATE_INIT;

}

void BLUETOOTH_send_frame(char * data){
    SerialBT.print("aa,");
    SerialBT.print(data);
    SerialBT.println("zz");
}

uint16_t BLUETOOTH_receive_frame(char * data){
    return sci_ID1_get(data);
}

void BLUETOOTH_Task(void){
    switch ( bluetoothData.state )
    {
        case BLUETOOTH_STATE_INIT:
        {   
            bluetoothData.frame_state = FRAME_STATE_HEADER_INIT_1;
            bluetoothData.index_readBuff = 0;
            bluetoothData.timeout = BLUETOOTH_FRAME_SEND_TIME;
            bluetoothData.timeout_led_blink = 250;
            bluetoothData.connection_state = BLUETOOTH_DISCONNECTED;
            bluetoothData.state = BLUETOOTH_STATE_READ;
            break;
        }
        case BLUETOOTH_STATE_READ:
        {
            char data;
            if(BLUETOOTH_receive_frame(&data)){
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
                
                //sprintf(send_frame, "m,A%d,B%d,C%d,I%0.2f,E%0.2f,", adcData.values[0], adcData.values_mv[0], adcData.values_2_prom[0], mv2pressure(respiraData.sp_insp), mv2pressure(respiraData.sp_exp));
                sprintf(send_frame, "m,A%0.2f,B%d,C%d,D%d,I%0.2f,E%0.2f,", mv2pressure((float)adcData.values_2_prom[0]), adcData.values_2_prom[1], configData.pwm5_duty ,adcData.values_2_prom[0], mv2pressure(respiraData.sp_insp), mv2pressure(respiraData.sp_exp));
                //sprintf(send_frame, "m,A15,");
                BLUETOOTH_send_frame(send_frame);
                
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

    if(bluetoothData.connection_state == BLUETOOTH_CONNECTED){
        if(bluetoothData.timeout_led_blink > 1800){
            digitalWrite(LEDPin, HIGH);
        }else{
            digitalWrite(LEDPin, LOW);
        }
        if(bluetoothData.timeout_led_blink == 0){
            bluetoothData.timeout_led_blink = 2000;
        }
    }else{
        if(bluetoothData.timeout_led_blink > 250){
            digitalWrite(LEDPin, HIGH);
        }else{
            digitalWrite(LEDPin, LOW);
        }  
        if(bluetoothData.timeout_led_blink == 0){
            bluetoothData.timeout_led_blink = 500;
        }
    }
}

void BLUETOOTH_process_frame(char * frame, uint8_t len){
    int i;
    char label;
    char data[20], response_frame[100];
    uint8_t index_data, index_response_frame = 0;
    
    //Serial.println(frame);

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
                        configData.pressure_max = pressure2mv((float)atof(data));
                        write_float_eeprom(ADDR_PRESSURE_MAX, configData.pressure_max);
                    }
                    //load
                    configData.pressure_max = read_float_eeprom(ADDR_PRESSURE_MAX);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "P%0.2f,", mv2pressure(configData.pressure_max));
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
                            //timer_ID2_set_frecuency(configData.pwm5_frec);    // TODO: descomentar
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
//                                appData.test_enable = 0;
                            }else{
//                                appData.test_enable = 1;
                            }
                            
                            //pwm_ID5_duty_set(configData.pwm5_duty);   // TODO: descomentar
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
                        respiraData.sp_insp = pressure2mv(atof(data));
                        write_float_eeprom(ADDR_PRESSURE_INS, respiraData.sp_insp);
                    }
                    //load
                    respiraData.sp_insp = read_float_eeprom(ADDR_PRESSURE_INS);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "U%0.2f,", mv2pressure(respiraData.sp_insp));
                    break;
                }
                case 'V':
                {
                    if(index_data != 0){
                        //Save
                        respiraData.sp_exp = pressure2mv(atof(data));
                        write_float_eeprom(ADDR_PRESSURE_EXP, respiraData.sp_exp);
                    }
                    //load
                    respiraData.sp_exp = read_float_eeprom(ADDR_PRESSURE_EXP);
                    //Response
                    index_response_frame += sprintf(&response_frame[index_response_frame], "V%0.2f,", mv2pressure(respiraData.sp_exp));
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    
    /*
    Serial.print("aa,");
    Serial.print(response_frame);
    Serial.println("zz");
    */
    // Send response frame
    BLUETOOTH_send_frame(response_frame);
    
}

void BLUETOOTH_callback_ISR (esp_spp_cb_event_t event, esp_spp_cb_param_t *param){

  if(event == ESP_SPP_DATA_IND_EVT ){ // Receive data
    while (SerialBT.available()) {
      //Serial.println("Read data");
      circBuffPush_sci(SerialBT.read(), BUFFER_RX_SCI_ID1);
    }
  }

  if(event == ESP_SPP_WRITE_EVT ){
    //Serial.println("Write data");
  }
  
  if(event == ESP_SPP_SRV_OPEN_EVT){
    //Serial.println("Bluetooth Connected");
    bluetoothData.timeout_led_blink = 2000;
    bluetoothData.connection_state = BLUETOOTH_CONNECTED;
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    //Serial.println("Bluetooth Disconnected");
    bluetoothData.timeout_led_blink = 500;
    bluetoothData.connection_state = BLUETOOTH_DISCONNECTED;
  }
  
}
