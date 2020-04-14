/* ************************************************************************** */
/**
 * @file max30102.cpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing MAX30102 driver.
 */
/* ************************************************************************** */

#include "system_definitions.hpp"


uint8_t max_sample_counter, writePointer, readPointer, numberOfSamples, activeLEDs, bytesLeftToRead, toGet; /**< General-purpose variables. */
uint32_t redBuffer[BUFFER_SIZE];  /**< Red LED sensor data. */
uint32_t irBuffer[BUFFER_SIZE];   /**< Infrared LED sensor data. */  
int32_t bufferLength;             /**< Data buffer length. */
int32_t spo2 = 0;                 /**< SPO2 value calculated. */
int32_t heartRate = 0;            /**< Heart-Rate value calculated. */

/**< uch_spo2_table is approximated as: -45.060*ratioAverage*ratioAverage + 30.354*ratioAverage + 94.845. */
uint8_t uch_spo2_table[184] = {  
    95,  95,  95,  96,  96,  96,  97,  97,  97,  97,  97,  98,  98,  98,  98,  98,  99,  99,  99,  99, 
    99,  99,  99,  99, 100, 100, 100, 100, 100, 100,  94,  95,  96,  96,  96,  80,  96,  87,  93,  95, 
    96,  94,  96,  96,  95,  97,  97,  98,  98,  99,  99,  98,  98,  99,  98,  97,  97,  97,  97,  96, 
    97,  97,  96,  96,  96,  96,  95,  95,  95,  94,  94,  94,  93,  93,  93,  92,  92,  92,  91,  91, 
    90,  90,  89,  89,  89,  88,  88,  87,  87,  86,  86,  85,  85,  84,  84,  83,  82,  82,  81,  81, 
    80,  80,  79,  78,  78,  77,  76,  76,  75,  74,  74,  73,  72,  72,  71,  70,  69,  69,  68,  67, 
    66,  66,  65,  64,  63,  62,  62,  61,  60,  59,  58,  57,  56,  56,  55,  54,  53,  52,  51,  50, 
    49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  31,  30,  29, 
    28,  27,  26,  25,  23,  22,  21,  20,  19,  17,  16,  15,  14,  12,  11,  10,   9,   7,   6,   5, 
    3,   2,    1  };

uint32_t tempLongRED=0, tempLongIR=0; /**< Group the 3-bytes of the sample into an 18-bit integer. */
int32_t an_x[BUFFER_SIZE];            /**< IR data in process. */
int32_t an_y[BUFFER_SIZE];            /**< RED data in process. */
uint8_t count_SpO2;                   /**< Determine the case by calculating the average of 5 SpO2 samples. */
uint8_t count_HR;                     /**< Determine the case by calculating the average of 5 Heart-Rate samples. */
MAX30102_DATA MAX30102;               /**< Manage variables that MAX30102 can use. */

boolean max30102_ready(){
    if (readRegister8(MAX30102_ADDRESS, MAX30102_PARTID) == MAX30102_EXPECTEDPARTID) return true; /**< Sensor ready to use. */
    else return false; /**< Sensor not available. */
}
void max30102_bitMask(uint8_t reg, uint8_t mask, uint8_t thing){
    /**< Grab current register context. */
    uint8_t originalContents = readRegister8(MAX30102_ADDRESS, reg);
    /**< Zero-out the portions of the register we're interested in. */
    originalContents &= mask;
    /**< Change contents. */
    writeRegister8(MAX30102_ADDRESS, reg, originalContents|thing);
}
void max30102_softReset(){
    max30102_bitMask(REG_MODE_CONFIG, MAX30102_RESET_MASK, MAX30102_RESET);
}
void MAX30102_Init(){   
    I2C_Init(Wire, I2C_SPEED); 
    while(!max30102_ready());
    max30102_softReset();
    
    /**< REG_FIFO_CONFIG - REG_MODE_CONFIG - REG_SPO2_CONFIG. */
    writeRegister8(MAX30102_ADDRESS, REG_FIFO_CONFIG, 0x5E); /**< Average of 4 samples; Enable FIFO Rollover; Set to 18 samples to trigger an 'Almost Full' interrupt. */
    writeRegister8(MAX30102_ADDRESS, REG_MODE_CONFIG, 0x03); /**< No Shutdown; No Reset; SpO2 Mode. */
    writeRegister8(MAX30102_ADDRESS, REG_SP02_CONFIG, 0x27); /**< Full scale: 4096; 100 Samples Per Second; ADC resolution 18 Bits. */
    
    /**< LED1(RED)_PULSE_AMPLITUDE - LED2(IR)_PULSE_AMPLITUDE. */
    writeRegister8(MAX30102_ADDRESS, REG_LED1_PA, 0x3C); /**< 12mA LED CURRENT. */
    writeRegister8(MAX30102_ADDRESS, REG_LED2_PA, 0x3C); /**< 12mA LED CURRENT. */
    
    /**< Multi-LED Mode Configuration. */
    max30102_bitMask(REG_MULTILED_CONFIG1, MAX30102_SLOT1_MASK, (uint8_t)(SLOT_RED_LED));
    max30102_bitMask(REG_MULTILED_CONFIG1, MAX30102_SLOT2_MASK, (uint8_t)(SLOT_IR_LED<<4));
    
    /**< Clear FIFO (Counter and pointers). */
    writeRegister8(MAX30102_ADDRESS, REG_FIFO_WR_PTR, 0x00);
    writeRegister8(MAX30102_ADDRESS, REG_OVF_COUNTER, 0x00);
    writeRegister8(MAX30102_ADDRESS, REG_FIFO_RD_PTR, 0x00);
    
    MAX30102.state = MAX30102_STATE_INIT;    
}

void max30102_read_temperature(){
    while(!max30102_ready());
    writeRegister8(MAX30102_ADDRESS, REG_TEMP_EN, 0x01);            /**< TEMP_EN. */
    writeRegister8(MAX30102_ADDRESS, REG_INTERRUPT_ENABLE_2, 0x02); /**< DIE_TEMP_RDY_EN. */     
    delay(30);
    
    MAX30102.temp_int = readRegister8(MAX30102_ADDRESS, REG_TINT);
    MAX30102.temp_frac = readRegister8(MAX30102_ADDRESS, REG_TFRAC);  
    MAX30102.data_temp = (float)(MAX30102.temp_int) + ((float)(MAX30102.temp_frac)*0.0625);     
}

void max30102_average_samples(){
    if (MAX30102.valid_SpO2) {
        switch (count_SpO2){
            case 1: /**< Average when there is only one sample. */
                MAX30102.samples_SpO2[MAX30102.samples_SpO2_index++] = spo2;
                MAX30102.data_SpO2 = spo2;
                count_SpO2++;
            break;
            case 2: /**< Average when there are 2 samples */
                MAX30102.data_SpO2 = 0;
                MAX30102.samples_SpO2[MAX30102.samples_SpO2_index++] = spo2;
                for (uint8_t j=0; j<count_SpO2; j++) MAX30102.data_SpO2 += MAX30102.samples_SpO2[j];
                MAX30102.data_SpO2 = (uint8_t)(MAX30102.data_SpO2/2);
                count_SpO2++;
            break; 
            case 3: /**< Average when there are 3 samples. */
                MAX30102.data_SpO2 = 0;
                MAX30102.samples_SpO2[MAX30102.samples_SpO2_index++] = spo2;
                for (uint8_t j=0; j<count_SpO2; j++) MAX30102.data_SpO2 += MAX30102.samples_SpO2[j];
                MAX30102.data_SpO2 = (uint8_t)(MAX30102.data_SpO2/3);
                count_SpO2++;
            break;
            case 4: /**< Average when there are 4 samples. */
                MAX30102.data_SpO2 = 0;
                MAX30102.samples_SpO2[MAX30102.samples_SpO2_index++] = spo2;
                for (uint8_t j=0; j<count_SpO2; j++) MAX30102.data_SpO2 += MAX30102.samples_SpO2[j];
                MAX30102.data_SpO2 = (uint8_t)(MAX30102.data_SpO2/4);
                count_SpO2++;
            break;
            case 5: /**< Average when there are 5 samples. */
                MAX30102.data_SpO2 = 0;
                MAX30102.samples_SpO2[MAX30102.samples_SpO2_index] = spo2;
                for (uint8_t j=0; j<count_SpO2; j++) MAX30102.data_SpO2 += MAX30102.samples_SpO2[j];
                MAX30102.data_SpO2 = (uint8_t)(MAX30102.data_SpO2/5);
                count_SpO2++;
            break;
            case 6: /**< Moving average of 5 samples. */
                for (uint8_t j=1; j<5; j++) MAX30102.samples_SpO2[j-1] = MAX30102.samples_SpO2[j];
                MAX30102.samples_SpO2[4] = spo2;
                MAX30102.data_SpO2 = 0;
                for (uint8_t j=0; j<5; j++) MAX30102.data_SpO2 += MAX30102.samples_SpO2[j];
                MAX30102.data_SpO2 = (uint8_t)(MAX30102.data_SpO2/5);
            break;
                
            default: break;
        }
    }

    if (MAX30102.valid_HR) {
        switch (count_HR){
            case 1: /**< Average when there is only one sample. */
                MAX30102.samples_HR[MAX30102.samples_HR_index++] = heartRate;
                MAX30102.data_HR = heartRate;
                count_HR++;
            break;
            case 2: /**< Average when there are 2 samples. */
                MAX30102.data_HR = 0;
                MAX30102.samples_HR[MAX30102.samples_HR_index++] = heartRate;
                for (uint8_t j=0; j<count_HR; j++) MAX30102.data_HR += MAX30102.samples_HR[j];
                MAX30102.data_HR = (uint8_t)(MAX30102.data_HR/2);
                count_HR++;
            break; 
            case 3: /**< Average when there are 3 samples. */
                MAX30102.data_HR = 0;
                MAX30102.samples_HR[MAX30102.samples_HR_index++] = heartRate;
                for (uint8_t j=0; j<count_HR; j++) MAX30102.data_HR += MAX30102.samples_HR[j];
                MAX30102.data_HR = (uint8_t)(MAX30102.data_HR/3);
                count_HR++;
            break;
            case 4: /**< Average when there are 4 samples. */
                MAX30102.data_HR = 0;
                MAX30102.samples_HR[MAX30102.samples_HR_index++] = heartRate;
                for (uint8_t j=0; j<count_HR; j++) MAX30102.data_HR += MAX30102.samples_HR[j];
                MAX30102.data_HR = (uint8_t)(MAX30102.data_HR/4);
                count_HR++;
            break;
            case 5: /**< Average when there are 5 samples. */
                MAX30102.data_HR = 0;
                MAX30102.samples_HR[MAX30102.samples_HR_index] = heartRate;
                for (uint8_t j=0; j<count_HR; j++) MAX30102.data_HR += MAX30102.samples_HR[j];
                MAX30102.data_HR = (uint8_t)(MAX30102.data_HR/5);
                count_HR++;
            break;
            case 6: /**< Moving average of 5 samples. */
                for (uint8_t j=1; j<5; j++) MAX30102.samples_HR[j-1] = MAX30102.samples_HR[j];
                MAX30102.samples_HR[4] = heartRate;
                MAX30102.data_HR = 0;
                for (uint8_t j=0; j<5; j++) MAX30102.data_HR += MAX30102.samples_HR[j];
                MAX30102.data_HR = (uint8_t)(MAX30102.data_HR/5);
            break;
                
            default: break;
        }
    }
}

void MAX30102_Tasks(){
     
    switch(MAX30102.state){
        case MAX30102_STATE_INIT:
            bufferLength = BUFFER_SIZE;
            max_sample_counter = 0;
            activeLEDs = 2;
            MAX30102.samples_SpO2_index = 0;
            MAX30102.samples_HR_index = 0;
            count_SpO2 = 1;
            count_HR = 1;
            MAX30102.valid_SpO2 = 0;
            MAX30102.valid_HR = 0;
            while(!max30102_ready());
            MAX30102.state = MAX30102_STATE_MEASUREMENT_REQUEST;         
        break;
        
        case MAX30102_STATE_MEASUREMENT_REQUEST:
            writePointer=0; readPointer=0; numberOfSamples=0; bytesLeftToRead=0; toGet=0;
            //Clear FIFO (Counter and pointers)
            writeRegister8(MAX30102_ADDRESS, REG_FIFO_WR_PTR, 0x00);
            writeRegister8(MAX30102_ADDRESS, REG_OVF_COUNTER, 0x00);
            writeRegister8(MAX30102_ADDRESS, REG_FIFO_RD_PTR, 0x00);

            //A_FULL_EN
            writeRegister8(MAX30102_ADDRESS, REG_INTERRUPT_ENABLE_1, 0x80);
            
            MAX30102.timeout_wait_sample = 50; //50ms
            MAX30102.state = MAX30102_STATE_RECEIVED_DATA;
        break;
        
        case MAX30102_STATE_RECEIVED_DATA:
            if (MAX30102.timeout_wait_sample == 0){
                writePointer = readRegister8(MAX30102_ADDRESS, REG_FIFO_WR_PTR);
                readPointer = readRegister8(MAX30102_ADDRESS, REG_FIFO_RD_PTR);

                if (readPointer != writePointer){
                    numberOfSamples = writePointer - readPointer;
                    if (numberOfSamples < 0) numberOfSamples += 32; 

                    bytesLeftToRead = numberOfSamples * activeLEDs * 3;
                    //Get ready to read a burst of data from the FIFO register
                    _i2cPort->beginTransmission(MAX30102_ADDRESS);
                    _i2cPort->write(REG_FIFO_DATA);
                    _i2cPort->endTransmission();

                    while (bytesLeftToRead > 0){
                        toGet = bytesLeftToRead;
                        if (toGet > I2C_BUFFER_LEN){                            
                            toGet = I2C_BUFFER_LEN - (I2C_BUFFER_LEN % (activeLEDs * 3)); //Trim toGet to be a multiple of the samples we need to read
                        }

                        bytesLeftToRead -= toGet;
                        //Request toGet number of bytes from sensor
                        _i2cPort->requestFrom(MAX30102_ADDRESS, (int)toGet);

                        //Get ready to read a burst of data from the FIFO register
                        while (toGet > 0){
                            uint8_t tempRED[3], tempIR[3]; //Array of 3 bytes that we will convert into long
                           
                            //Burst read three bytes - RED
                            tempRED[2] = _i2cPort->read();  
                            tempRED[1] = _i2cPort->read();  
                            tempRED[0] = _i2cPort->read();
                            //Burst read three more bytes - IR
                            tempIR[2] = _i2cPort->read();
                            tempIR[1] = _i2cPort->read();
                            tempIR[0] = _i2cPort->read();

                            //Convert array to long
                            memcpy(&tempLongRED, tempRED, sizeof(tempLongRED));
                            tempLongRED &= 0x3FFFF; //Zero out all but 18 bits                                
                            memcpy(&tempLongIR, tempIR, sizeof(tempLongIR));
                            tempLongIR &= 0x3FFFF; //Zero out all but 18 bits

                            toGet -= activeLEDs * 3;
                        }             
                    } //End while (bytesLeftToRead > 0)
                } //End readPtr != writePtr 
                
                if (numberOfSamples!=0 && tempLongRED>3100 && tempLongIR>1900){
                    redBuffer[max_sample_counter] = (uint32_t)(round(((float)tempLongRED)/14.2835));
                    irBuffer[max_sample_counter]  = (uint32_t)(round(((float)tempLongIR)/6.6137));               
                    max_sample_counter++;
                    if (max_sample_counter<bufferLength) MAX30102.state = MAX30102_STATE_MEASUREMENT_REQUEST;
                    else                                 MAX30102.state = MAX30102_STATE_DATA_PROCESSING;      
                } else {
                    MAX30102.state = MAX30102_STATE_MEASUREMENT_REQUEST;
                    MAX30102.valid_SpO2 = 0;
                    MAX30102.valid_HR = 0;
                    MAX30102.samples_SpO2_index = 0;
                    MAX30102.samples_HR_index = 0;
                    count_SpO2 = 1;
                    count_HR = 1;
                    MAX30102.data_SpO2 = 0;
                    MAX30102.data_HR = 0;
                }
            }
        break;
        
        case MAX30102_STATE_DATA_PROCESSING:
            //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
            maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &MAX30102.valid_SpO2, &heartRate, &MAX30102.valid_HR);           
            max30102_average_samples();

            //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
            for (max_sample_counter = 25; max_sample_counter < bufferLength; max_sample_counter++){
                redBuffer[max_sample_counter - 25] = redBuffer[max_sample_counter];
                irBuffer[max_sample_counter - 25] = irBuffer[max_sample_counter];
            }
            max_sample_counter = 75; //Take 25 sets of samples before calculating the heart rate again.
            MAX30102.state = MAX30102_STATE_MEASUREMENT_REQUEST; //After gathering 25 new samples recalculate HR and SP02           
        break;
        
        default: break;
    }
}


void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer,
                int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid){ 
    uint32_t un_ir_mean;
    int32_t k, n_i_ratio_count;
    int32_t i, n_exact_ir_valley_locs_count, n_middle_idx;
    int32_t n_th1, n_npks;   
    int32_t an_ir_valley_locs[15] ;
    int32_t n_peak_interval_sum;

    int32_t n_y_ac, n_x_ac;
    int32_t n_spo2_calc; 
    int32_t n_y_dc_max, n_x_dc_max; 
    int32_t n_y_dc_max_idx = 0;
    int32_t n_x_dc_max_idx = 0; 
    int32_t an_ratio[5], n_ratio_average; 
    int32_t n_nume, n_denom;

    // calculates DC mean and subtract DC from ir
    un_ir_mean = 0; 
    for (k=0 ; k<n_ir_buffer_length ; k++)
        un_ir_mean += pun_ir_buffer[k];
    un_ir_mean = (uint32_t)(un_ir_mean/n_ir_buffer_length);

    // remove DC and invert signal so that we can use peak detector as valley detector
    for (k=0 ; k<n_ir_buffer_length ; k++)  
        an_x[k] = -1*(pun_ir_buffer[k] - un_ir_mean); 

    // 4 pt Moving Average
    for(k=0; k< BUFFER_SIZE-MA4_SIZE; k++)
        an_x[k] = (int32_t)((an_x[k]+an_x[k+1]+an_x[k+2]+an_x[k+3])/4);        
    
    // calculate threshold  
    n_th1 = 0; 
    for (k=0 ; k<BUFFER_SIZE ;k++)
        n_th1 += an_x[k];
    
    n_th1 = (int32_t)(n_th1/(BUFFER_SIZE));
    if(n_th1<30) n_th1=30; // min allowed
    if(n_th1>60) n_th1=60; // max allowed

    for (k=0; k<15; k++)
        an_ir_valley_locs[k]=0;
    // since we flipped signal, we use peak detector as valley detector
    maxim_find_peaks(an_ir_valley_locs, &n_npks, an_x, BUFFER_SIZE, n_th1, 4, 15);//peak_height, peak_distance, max_num_peaks 
    n_peak_interval_sum = 0;
    if (n_npks>=2){
        for (k=1; k<n_npks; k++) n_peak_interval_sum += (an_ir_valley_locs[k] - an_ir_valley_locs[k -1]);
        n_peak_interval_sum = (int32_t)(n_peak_interval_sum/(n_npks-1));
        float aux = ((FreqS*60)/n_peak_interval_sum);
        if(aux<78){ *pn_heart_rate = (int32_t)aux; } 
        else if (aux>=78 && aux<=93){ *pn_heart_rate = (int32_t)(0.4*aux + 46.8); }
        else if (aux>93 && aux<115){ *pn_heart_rate = (int32_t)(0.2727*aux + 58.6364); }
        else if (aux>=115){ *pn_heart_rate = (int32_t)(0.6154*aux + 19.2308); }
        *pch_hr_valid  = 1;
    } else { 
        *pn_heart_rate = -999; // unable to calculate because # of peaks are too small
        *pch_hr_valid  = 0;
    }

    //  load raw value again for SPO2 calculation : RED(=y) and IR(=X)
    for (k=0 ; k<n_ir_buffer_length ; k++ ){
        an_x[k] = pun_ir_buffer[k] ; 
        an_y[k] = pun_red_buffer[k] ; 
    }

    // find precise min near an_ir_valley_locs
    n_exact_ir_valley_locs_count = n_npks; 

    //using exact_ir_valley_locs , find ir-red DC andir-red AC for SPO2 calibration an_ratio
    //finding AC/DC maximum of raw
    n_ratio_average = 0; 
    n_i_ratio_count = 0; 
    for(k=0; k< 5; k++)
        an_ratio[k]=0;
    for (k=0; k< n_exact_ir_valley_locs_count; k++){       
        if (an_ir_valley_locs[k] > BUFFER_SIZE ){
            *pn_spo2 =  -999 ; // do not use SPO2 since valley loc is out of range
            *pch_spo2_valid  = 0; 
            return;
        }
    }
    // find max between two valley locations 
    // and use an_ratio betwen AC compoent of Ir & Red and DC compoent of Ir & Red for SPO2 
    for (k=0; k< n_exact_ir_valley_locs_count-1; k++){
        n_y_dc_max = -16777216; 
        n_x_dc_max = -16777216; 
        if (an_ir_valley_locs[k+1]-an_ir_valley_locs[k] >3){
            for (i=an_ir_valley_locs[k]; i< an_ir_valley_locs[k+1]; i++){
                if (an_x[i]> n_x_dc_max) {n_x_dc_max =an_x[i]; n_x_dc_max_idx=i;}
                if (an_y[i]> n_y_dc_max) {n_y_dc_max =an_y[i]; n_y_dc_max_idx=i;}
            }
            n_y_ac= (an_y[an_ir_valley_locs[k+1]] - an_y[an_ir_valley_locs[k]])*(n_y_dc_max_idx -an_ir_valley_locs[k]); //red
            n_y_ac=  an_y[an_ir_valley_locs[k]] + (int32_t)(n_y_ac/(an_ir_valley_locs[k+1] - an_ir_valley_locs[k])); 
            n_y_ac=  an_y[n_y_dc_max_idx] - n_y_ac;    // subracting linear DC compoenents from raw 
            n_x_ac= (an_x[an_ir_valley_locs[k+1]] - an_x[an_ir_valley_locs[k]])*(n_x_dc_max_idx -an_ir_valley_locs[k]); // ir
            n_x_ac=  an_x[an_ir_valley_locs[k]] + (int32_t)(n_x_ac/(an_ir_valley_locs[k+1] - an_ir_valley_locs[k])); 
            n_x_ac=  an_x[n_y_dc_max_idx] - n_x_ac;    // subracting linear DC compoenents from raw 
            n_nume= (int32_t)((n_y_ac *n_x_dc_max)>>7); //prepare X100 to preserve floating value
            n_denom= (int32_t)((n_x_ac *n_y_dc_max)>>7);
            if (n_denom>0  && n_i_ratio_count <5 &&  n_nume != 0){   
                an_ratio[n_i_ratio_count]= (int32_t)((n_nume*100)/n_denom); //formular is ( n_y_ac *n_x_dc_max) / ( n_x_ac *n_y_dc_max) ;
                n_i_ratio_count++;
            }
        }
    }
    // choose median value since PPG signal may varies from beat to beat
    maxim_sort_ascend(an_ratio, n_i_ratio_count);
    n_middle_idx= (int32_t)(n_i_ratio_count/2);

    if (n_middle_idx >1)
        n_ratio_average = (int32_t)((an_ratio[n_middle_idx-1] + an_ratio[n_middle_idx])/2); // use median
    else
        n_ratio_average = an_ratio[n_middle_idx];

    if(n_ratio_average>2 && n_ratio_average <184){
        n_spo2_calc = uch_spo2_table[n_ratio_average];
        *pn_spo2 = n_spo2_calc;
        *pch_spo2_valid = 1;//  float_SPO2 =  -45.060*n_ratio_average* n_ratio_average/10000 + 30.354 *n_ratio_average/100 + 94.845 ;  // for comparison with table
    } else {
        *pn_spo2 = -999 ; // do not use SPO2 since signal an_ratio is out of range
        *pch_spo2_valid = 0; 
    }
}
void maxim_find_peaks( int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height,
                int32_t n_min_distance, int32_t n_max_num ){
    maxim_peaks_above_min_height( pn_locs, n_npks, pn_x, n_size, n_min_height );
    maxim_remove_close_peaks( pn_locs, n_npks, pn_x, n_min_distance );
    *n_npks = min( *n_npks, n_max_num );    
}
void maxim_peaks_above_min_height( int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height ){
    int32_t i = 1, n_width;
    *n_npks = 0;

    while (i < n_size-1){
        if (pn_x[i] > n_min_height && pn_x[i] > pn_x[i-1]){      // find left edge of potential peaks
            n_width = 1;
            while (i+n_width < n_size && pn_x[i] == pn_x[i+n_width])  // find flat peaks
                n_width++;
            if (pn_x[i] > pn_x[i+n_width] && (*n_npks) < 15 ){        // find right edge of peaks
                pn_locs[(*n_npks)++] = i;    
                // for flat peaks, peak location is left edge
                i += n_width+1;
            } else
                i += n_width;
        } else
            i++;
    }    
}
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance){    
    int32_t i, j, n_old_npks, n_dist;

    /* Order peaks from large to small */
    maxim_sort_indices_descend( pn_x, pn_locs, *pn_npks );
    for ( i = -1; i < *pn_npks; i++ ){     
        n_old_npks = *pn_npks;
        *pn_npks = i+1;
        for ( j = i+1; j < n_old_npks; j++ ){
            n_dist =  pn_locs[j] - ( i == -1 ? -1 : pn_locs[i] ); // lag-zero peak of autocorr is at index -1
            if ( n_dist > n_min_distance || n_dist < -n_min_distance )
                pn_locs[(*pn_npks)++] = pn_locs[j];
        }
    }

    // Resort indices int32_to ascending order
    maxim_sort_ascend( pn_locs, *pn_npks );    
}
void maxim_sort_indices_descend(  int32_t  *pn_x, int32_t *pn_indx, int32_t n_size){
    int32_t i, j, n_temp;
    for (i = 1; i < n_size; i++) {
        n_temp = pn_indx[i];
        for (j = i; j > 0 && pn_x[n_temp] > pn_x[pn_indx[j-1]]; j--)
            pn_indx[j] = pn_indx[j-1];
        pn_indx[j] = n_temp;
    }    
}
void maxim_sort_ascend(int32_t  *pn_x, int32_t n_size) {
    int32_t i, j, n_temp;
    for (i = 1; i < n_size; i++) {  
        n_temp = pn_x[i];
        for (j = i; j > 0 && n_temp < pn_x[j-1]; j--)
            pn_x[j] = pn_x[j-1];
        pn_x[j] = n_temp;
    }    
}