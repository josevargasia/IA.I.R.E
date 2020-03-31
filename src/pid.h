
#ifndef _PID_H    /* Guard against multiple inclusion */
#define _PID_H


#include "system_definitions.h"


#ifdef __cplusplus
extern "C" {
#endif

    
    #define     k_ctrl  15
    #define     tao     20
    #define     theta   30 
    #define     T       40


    typedef struct
    {
        /* The application's current state */
         
        float q0;
        float q1;
        float q2;
        
        uint16_t timeout;                   /**< Timeout. */
        
    } PID_DATA;

    extern PID_DATA pidData;    /**< Manage all variables that bluetooth can use. */
    
void pid_init(void);

void pid_task(float SetP);

#ifdef __cplusplus
}
#endif

#endif /* _PID_H */

