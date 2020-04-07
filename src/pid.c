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
    
    kp = 0.6;
    ti = 120;
    td = 1; 
    
//    kp = 20;
//    ti = 120;
//    td = 15;
    
    pidData.q0 = (float)kp*(1+(float)T/(2*(float)ti)+(float)td/T);
    pidData.q1 = -(float)kp*(1-(float)T/(2*(float)ti)+(2*(float)td)/T);
    pidData.q2 = ((float)kp*(float)td)/(float)T;
    
    pidData.timeout = T;
}


void pid_task(void){
  
  //*************************************************************************//
   //*****************   SINTONIA POR ZIEGLER y NICHOLS    *******************//
   //*************************************************************************//
    if (pidData.timeout == 0){
        pidData.timeout = T;
        
        // Calculo do controle PID digital

        //Comienzo la ley de control

        adc_get_sample_average();
        
        pidData.yM = (float)adcData.values_2_prom[0];
        pidData.e = pidData.SetP-pidData.yM;

        // Controle PID
        //Ley del controlador PID discreto
        
        pidData.u = pidData.u_1 + pidData.q0*pidData.e + pidData.q1*pidData.e_1 + pidData.q2*pidData.e_2; 

        if (pidData.u >= 1700.0)        //Saturo la accion de control 'uT' en un tope maximo y minimo
            pidData.u = 1700.0;

        if (pidData.u <= 0.0)
            pidData.u = 0.0;

        //escalizo la u de mV a bits, en el caso del PWM ser a 1Khz con una resolucion de 10
        //el valor máximo del pwm es de 1000
        pidData.ctrl_duty = pidData.u*100/1700;

        //Retorno a los valores reales
        pidData.e_2 = pidData.e_1;
        pidData.e_1 = pidData.e;
        pidData.u_1 = pidData.u;

        //La accion calculada la transformo en PWM
        configData.pwm5_duty = pidData.ctrl_duty;
        pwm_ID5_duty_set(configData.pwm5_duty);

    }
}
/* *****************************************************************************
 End of File
 */
