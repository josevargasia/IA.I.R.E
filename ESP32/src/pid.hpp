/* ************************************************************************** */
/**
 * @file pid.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing PID driver.
 */
/* ************************************************************************** */
#include <Arduino.h>


#define     k_ctrl  21      /**< Gain of system. */
#define     tao     20      /**< Tao of system. */
#define     theta   5       /**< Theta of system. */
#define     T       3       /**< Period for sample system. */

/**
 * @brief PID data structure.
 */
typedef struct
{
    float q0;           /**< Variables for PID. */
    float q1;           /**< Variables for PID. */
    float q2;           /**< Variables for PID. */
    
    float yM;           /**< System output. */
    float e;            /**< System error. */
    float e_1;          /**< System error one time before. */
    float e_2;          /**< System error two times before. */
    float u;            /**< System control. */
    float u_1;          /**< System control one time before. */
    float ctrl_duty;    /**< System control in duty cycle. */
    
    float SetP;         /**< System set point. */
    
    uint16_t timeout;    /**< Timeout. */

    float   kp;
    float   ti;
    float   td;
    
} PID_DATA;

extern PID_DATA pidData;    /**< Manage all variables that PID can use. */
extern PID_DATA pidExpData;    /**< Manage all variables that PID can use. */
    
/**
 * @brief Setup PID 
 */
void pid_init(void);

/**
 * @brief Handle Inspiration PID task 
 */
void pid_insp_task(void);

/**
 * @brief Handle Expiration PID task 
 */
void pid_exp_task(void);