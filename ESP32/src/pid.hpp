
#include <Arduino.h>


    #define     k_ctrl  21
    #define     tao     20
    #define     theta   5 
    #define     T       3


typedef struct
{
    /* The application's current state */
        
    float q0;
    float q1;
    float q2;
    
    float yM;
    float e;
    float e_1;
    float e_2;
    float u;
    float u_1;
    float ctrl_duty;
    
    float SetP;
    
    uint16_t timeout;                   /**< Timeout. */
    
} PID_DATA;

extern PID_DATA pidData;    /**< Manage all variables that bluetooth can use. */
    
void pid_init(void);

void pid_task(void);