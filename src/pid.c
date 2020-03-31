/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "pid.h"
#include "pwm.h"



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

PID_DATA pidData;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

void pid_init(void){
    
    float kp, ti, td;
        
    kp = (1.2*tao)/(k_ctrl*theta);
    ti=2*theta;
    td=0.5*theta; 
    
    pidData.q0 = kp*(1+T/(2*ti)+td/T);
    pidData.q1 = -kp*(1-T/(2*ti)+(2*td)/T);
    pidData.q2 = (kp*td)/T;
    
    pidData.timeout = 100;
}

void pid_task(float SetP){
  
  //*************************************************************************//
   //*****************   SINTONIA POR ZIEGLER y NICHOLS    *******************//
   //*************************************************************************//
    if (pidData.timeout == 0){
        pidData.timeout = 100;
        float yM, e, e_1, e_2, u, u_1, ctrl_duty;



        // Calculo do controle PID digital

        //Comienzo la ley de control

        yM = (float)adcData.values_mv[0];
        e = SetP-yM;

        // Controle PID
        u = u_1 + pidData.q0*e + pidData.q1*e_1 + pidData.q2*e_2; //Ley del controlador PID discreto

        if (u >= 3300.0)        //Saturo la accion de control 'uT' en un tope maximo y minimo
            u = 3300.0;

        if (u <= 0.0)
            u = 0.0;

        //escalizo la u de mV a bits, en el caso del PWM ser a 1Khz con una resolucion de 10
        //el valor máximo del pwm es de 1000
        ctrl_duty=u*100/3300;

        //Retorno a los valores reales
        e_2=e_1;
        e_1=e;
        u_1=u;

        //La accion calculada la transformo en PWM
        pwm_ID5_duty_set(ctrl_duty);

    }
}

/* *****************************************************************************
 End of File
 */
