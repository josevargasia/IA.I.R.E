/* ************************************************************************** */
/**
 * @file pid.cpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing PID driver.
 */
/* ************************************************************************** */

#include "system_definitions.hpp"

PID_DATA pidData;   /**< Manage all variables that PID can use. */
PID_DATA pidExpData;   /**< Manage all variables that PID can use. */

void pid_init(void){
    
    // INSPIRATION PID SETUP
    // float kp, ti, td;
        
    // pidData.kp = ((float)1.2*(float)tao)/((float)k_ctrl*(float)theta);
    // pidData.ti=(float)2*(float)theta;
    // pidData.td=(float)0.5*(float)theta; 
    
    // pidData.kp;
    // pidData.ti;
    // pidData.td; 
    
//    kp = 20;
//    ti = 120;
//    td = 15;
    
    pidData.q0 = (float)pidData.kp*(1+(float)T/(2*(float)pidData.ti)+(float)pidData.td/T);
    pidData.q1 = -(float)pidData.kp*(1-(float)T/(2*(float)pidData.ti)+(2*(float)pidData.td)/T);
    pidData.q2 = ((float)pidData.kp*(float)pidData.td)/(float)T;

    pidData.q0 = pidData.kp;
    pidData.q1 = (pidData.kp*T)/pidData.ti;
    pidData.q2 = (pidData.kp*pidData.td)/T;

    pidData.timeout = T;

    // EXPIRATION PID SETUP
    // float kp, ti, td;
        
    // pidExpData.kp = ((float)1.2*(float)tao)/((float)k_ctrl*(float)theta);
    // pidExpData.ti=(float)2*(float)theta;
    // pidExpData.td=(float)0.5*(float)theta; 
    
    pidExpData.kp=0.6;
    pidExpData.ti=120;
    pidExpData.td=1; 
    
//    kp = 20;
//    ti = 120;
//    td = 15;
    
    pidExpData.q0 = (float)pidExpData.kp*(1+(float)T/(2*(float)pidExpData.ti)+(float)pidExpData.td/T);
    pidExpData.q1 = -(float)pidExpData.kp*(1-(float)T/(2*(float)pidExpData.ti)+(2*(float)pidExpData.td)/T);
    pidExpData.q2 = ((float)pidExpData.kp*(float)pidExpData.td)/(float)T;

    
    pidExpData.timeout = T;

    // printf("\nI q0:%0.2f\tq1:%0.2f\tq2:%0.2f\nE q0:%0.2f\tq1:%0.2f\tq2:%0.2f\n",pidData.q0,pidData.q1,pidData.q2,pidExpData.q0,pidExpData.q1,pidExpData.q2);
}


void pid_insp_task(void){
  
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
        pwm_duty_set(configData.pwm5_duty);

    }
}

void pid_exp_task(void){
  
  //*************************************************************************//
   //*****************   SINTONIA POR ZIEGLER y NICHOLS    *******************//
   //*************************************************************************//
    if (pidExpData.timeout == 0){
        pidExpData.timeout = T;
        
        // Calculo do controle PID digital

        //Comienzo la ley de control

        adc_get_sample_average();
        
        pidExpData.yM = (float)adcData.values_2_prom[0];
        pidExpData.e = pidExpData.SetP-pidExpData.yM;

        // Controle PID
        //Ley del controlador PID discreto
        
        pidExpData.u = pidExpData.u_1 + pidExpData.q0*pidExpData.e + pidExpData.q1*pidExpData.e_1 + pidExpData.q2*pidExpData.e_2; 

        if (pidExpData.u >= 1700.0)        //Saturo la accion de control 'uT' en un tope maximo y minimo
            pidExpData.u = 1700.0;

        if (pidExpData.u <= 0.0)
            pidExpData.u = 0.0;

        //escalizo la u de mV a bits, en el caso del PWM ser a 1Khz con una resolucion de 10
        //el valor máximo del pwm es de 1000
        pidExpData.ctrl_duty = pidExpData.u*100/1700;

        //Retorno a los valores reales
        pidExpData.e_2 = pidExpData.e_1;
        pidExpData.e_1 = pidExpData.e;
        pidExpData.u_1 = pidExpData.u;

        //La accion calculada la transformo en PWM
        configData.pwm5_duty = pidExpData.ctrl_duty;
        pwm_duty_set(configData.pwm5_duty);

    }
}