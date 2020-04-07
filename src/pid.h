
#ifndef _PID_H    /* Guard against multiple inclusion */
#define _PID_H


#include "system_definitions.h"


#ifdef __cplusplus
extern "C" {
#endif

    
    #define     k_ctrl  21
    #define     tao     20
    #define     theta   5 
    #define     T       3

//    #define     k_ctrl  12
//    #define     tao     36
//    #define     theta   9 
//    #define     T       4


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

#ifdef __cplusplus
}
#endif

#endif /* _PID_H */

float yM, e, e_1, e_2, u, u_1, ctrl_duty;