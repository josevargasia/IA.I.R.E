
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.hpp"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


PRESS_DATA pressData;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


// void pressure_get_value(uint16_t intVal, uint8_t unit){
//   switch(unit){
//     case 0:
//       pressData.measValue = ((float)intVal/1000-0.2)*20*10.19716/9;
//       break;
//     case 1:
//       pressData.measValue = ((float)intVal/1000-0.2)*20/9;
//       break;
//     default:
//       break;
//   }
// }

// void pressure_prom_int_values(uint16_t *addValue){
//   uint16_t promAcum = 0;
//   uint8_t i;
  
//   for(i=PRESS_WINDOW_SIZE-1;i>0;i--){
//     pressData.valuesWindow[i] = pressData.valuesWindow[i-1];
//     promAcum += pressData.valuesWindow[i];
//   }
//   pressData.valuesWindow[0] = *addValue;
//   promAcum += *addValue;
//   *addValue = promAcum/PRESS_WINDOW_SIZE;
// }

float pressure2mv(float pressure){
    float meas_mv;
    
    meas_mv = (0.0291*pressure) + 0.132;
    
    return meas_mv*1000;
}

float mv2pressure(float mv){
    float pressure;
    
    if(mv < 132){
        mv = 132;
    }
    
    pressure = (mv/1000) - 0.132;
    pressure /= 0.0291;
    return pressure;
}
/* *****************************************************************************
 End of File
 */
