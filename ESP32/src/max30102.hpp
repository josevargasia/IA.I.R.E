/* ************************************************************************** */
/**
 * @file max30102.hpp
 * @author Ingeniería Apropiada
 * @date 09/04/2020
 * @brief File containing MAX30102 driver.
 */
/* ************************************************************************** */

#include <Arduino.h>


#define MAX30102_ADDRESS          0x57  /**< 7-bit I2C Sensor Address. */
#define MAX30102_ADDRESS_WRITING  0xAE  /**< 7-bit I2C Sensor Address + Write bit. */
#define MAX30102_ADDRESS_READING  0xAF  /**< 7-bit I2C Sensor Address + Read bit. */

#define REG_INTERRUPT_STATUS_1    0x00  /**< Register address Interrupt Status 1. */
#define REG_INTERRUPT_STATUS_2    0x01  /**< Register address Interrupt Status 2. */
#define REG_INTERRUPT_ENABLE_1    0x02  /**< Register address Interrupt Enable 1. */
#define REG_INTERRUPT_ENABLE_2    0x03  /**< Register address Interrupt Enable 2. */

#define REG_FIFO_WR_PTR           0x04  /**< Register address FIFO Write Pointer. */
#define REG_OVF_COUNTER           0x05  /**< Register address Overflow Counter. */
#define REG_FIFO_RD_PTR           0x06  /**< Register address FIFO Read Pointer. */
#define REG_FIFO_DATA             0x07  /**< Register address FIFO Data. */

#define REG_FIFO_CONFIG           0x08  /**< Register address FIFO Configuration. */
#define REG_MODE_CONFIG           0x09  /**< Register address Mode Configuration. */
#define REG_SP02_CONFIG           0x0A  /**< Register address SpO2 Configuration. */

#define REG_LED1_PA               0x0C  /**< Register address LED1 Pulse Amplitude. */
#define REG_LED2_PA               0x0D  /**< Register address LED2 Pulse Amplitude. */

#define REG_MULTILED_CONFIG1      0x11  /**< Register address Multi-LED Mode Control. */
#define REG_MULTILED_CONFIG2      0x12  /**< Register address Multi-LED Mode Control. */

#define REG_TINT                  0x1F  /**< Register address Die Temp Integer. */
#define REG_TFRAC                 0x20  /**< Register address Die Temp Fraction. */
#define REG_TEMP_EN               0x21  /**< Register address Die Temperature Configuration. */

#define MAX30102_REVISIONID       0xFE  /**< Register address Revision ID. */
#define MAX30102_PARTID           0xFF  /**< Register address Part ID - Should always be 0x15. */
#define MAX30102_RESET_MASK       0xBF  /**< Value that clears the Reset Bit. */
#define MAX30102_RESET 			  0x40  /**< Enable Reset Bit. */
#define MAX30102_SLOT1_MASK 	  0xF8  /**< Value that clears the SLOT1 Bits. */
#define MAX30102_SLOT2_MASK  	  0x8F  /**< Value that clears the SLOT2 Bits. */
#define MAX30102_EXPECTEDPARTID   0x15  /**< MAX30102 Part ID. */
#define SLOT_RED_LED              0x01  /**< Enable LED1(Red). */
#define SLOT_IR_LED               0x02  /**< Enable LED2(IR). */

#define FreqS                     25      /**< Sampling frequency. */
#define BUFFER_SIZE               FreqS*4 /**< Data buffer length. */
#define MA4_SIZE                  4       /**< Length in bytes. */
#define STORAGE_SIZE              4       /**< Length in bytes. */

/**
* @brief Use enum for define states of states machine.
*/
typedef enum {
	MAX30102_STATE_INIT = 0,             /**< Initial state. */
    MAX30102_STATE_MEASUREMENT_REQUEST,  /**< State to start a new reading. */
    MAX30102_STATE_RECEIVED_DATA,        /**< State to read data sensor. */  
    MAX30102_STATE_DATA_PROCESSING,      /**< State to calculate the value of SpO2 and Heart-Rate. */
} MAX30102_STATES;

/**
 * @brief MAX30102 data structure.
 */
typedef struct {
    MAX30102_STATES state;          /**< States of state machine. */
    uint16_t timeout_wait_sample;   /**< Waiting time to read samples. */
    uint8_t temp_int;               /**< Stores the integer value of temperature. */
    uint8_t temp_frac;              /**< Stores fractional part of temperature. */
    float data_temp;                /**< Stores the temperature data. */
    uint8_t samples_SpO2_index;     /**< Index for the vector of the SpO2 samples. */
    uint8_t samples_SpO2[5];        /**< Vector of the SpO2 samples. */
    int8_t valid_SpO2;              /**< Indicator to show if the SPO2 calculation is valid. */
    uint16_t data_SpO2;             /**< Stores the SpO2 data. */
    uint8_t samples_HR_index;       /**< Index for the vector of the Heart-Rate samples. */
    uint8_t samples_HR[5];          /**< Vector of the Heart-Rate samples. */
    int8_t valid_HR;                /**< Indicator to show if the heart rate calculation is valid. */
    uint16_t data_HR;               /**< Stores the Heart-Rate data. */
} MAX30102_DATA;
extern MAX30102_DATA MAX30102;      /**< Manage variables that MAX30102 can use. */


extern uint8_t max_sample_counter, writePointer, readPointer, numberOfSamples, activeLEDs, bytesLeftToRead, toGet;  /**< General-purpose variables. */
extern uint32_t redBuffer[BUFFER_SIZE];     /**< Red LED sensor data. */
extern uint32_t irBuffer[BUFFER_SIZE];      /**< Infrared LED sensor data. */ 
extern int32_t bufferLength;                /**< Data buffer length. */
extern int32_t spo2;                        /**< SPO2 value calculated. */
extern int32_t heartRate;                   /**< Heart-Rate value calculated. */
extern uint8_t uch_spo2_table[184];         /**< uch_spo2_table is approximated as: -45.060*ratioAverage*ratioAverage + 30.354*ratioAverage + 94.845. */
extern uint32_t tempLongRED, tempLongIR;    /**< Group the 3-bytes of the sample into an 18-bit integer. */
extern int32_t an_x[BUFFER_SIZE];           /**< IR data in process. */
extern int32_t an_y[BUFFER_SIZE];           /**< RED data in process. */
extern uint8_t count_SpO2;                  /**< Determine the case by calculating the average of 5 SpO2 samples. */
extern uint8_t count_HR;                    /**< Determine the case by calculating the average of 5 Heart-Rate samples. */

/**
 * @brief MAX30102 is ready to use?
 * @return Return sensor state  
 */
boolean max30102_ready();

/**
* @brief Clear and Setup Register
* @code
*      max30102_bitMask(REG_MODE_CONFIG, MAX30102_RESET_MASK, MAX30102_RESET);
* @endcode
* @param  reg     Register to wirte   
* @param  mask    Value that clears the Bit
* @param  thing   Value to set
*/
void max30102_bitMask(uint8_t reg, uint8_t mask, uint8_t thing);

/**
 * @brief Sensor software reset 
 */
void max30102_softReset();

/**
 * @brief Sensor setup 
 */
void MAX30102_Init();

/**
 * @brief Sensor temperature reading 
 */
void max30102_read_temperature();

/**
 * @brief Average of the SpO2 and Heart-Rate samples
 */
void max30102_average_samples();

/**
 * @brief Handle MAX30102 task 
 */
void MAX30102_Tasks();

/**
 * @brief MAXIM algorithm functions to calculate the SpO2 and Heart-Rate value 
 */
void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer,
                int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
void maxim_find_peaks( int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height,
                int32_t n_min_distance, int32_t n_max_num );
void maxim_peaks_above_min_height( int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height );
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance);
void maxim_sort_indices_descend(  int32_t  *pn_x, int32_t *pn_indx, int32_t n_size);
void maxim_sort_ascend(int32_t  *pn_x, int32_t n_size); 