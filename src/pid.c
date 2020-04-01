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

#include "system_definitions.h"



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
        
    kp = ((float)1.2*(float)tao)/((float)k_ctrl*(float)theta);
    ti=(float)2*(float)theta;
    td=(float)0.5*(float)theta; 
    
    kp = 0.8;
    ti = 120;
    td = 1; 
    
    pidData.q0 = (float)kp*(1+(float)T/(2*(float)ti)+(float)td/T);
    pidData.q1 = -(float)kp*(1-(float)T/(2*(float)ti)+(2*(float)td)/T);
    pidData.q2 = ((float)kp*(float)td)/(float)T;
    
    pidData.timeout = 100;
}

float yM, e, e_1, e_2, u, u_1, ctrl_duty;

void pid_task(float SetP){
  
  //*************************************************************************//
   //*****************   SINTONIA POR ZIEGLER y NICHOLS    *******************//
   //*************************************************************************//
    if (pidData.timeout == 0){
        pidData.timeout = T;
        
        // Calculo do controle PID digital

        //Comienzo la ley de control

        adc_get_sample_average();
        
        yM = (float)adcData.values_2_prom[1];
        e = SetP-yM;

        // Controle PID
        u = u_1 + pidData.q0*e + pidData.q1*e_1 + pidData.q2*e_2; //Ley del controlador PID discreto

        if (u >= 1700.0)        //Saturo la accion de control 'uT' en un tope maximo y minimo
            u = 1700.0;

        if (u <= 0.0)
            u = 0.0;

        //escalizo la u de mV a bits, en el caso del PWM ser a 1Khz con una resolucion de 10
        //el valor máximo del pwm es de 1000
        ctrl_duty=u*100/1700;

        //Retorno a los valores reales
        e_2=e_1;
        e_1=e;
        u_1=u;

        //La accion calculada la transformo en PWM
        configData.pwm5_duty = ctrl_duty;
        pwm_ID5_duty_set(ctrl_duty);

    }
}

/* *****************************************************************************
 End of File
 */
