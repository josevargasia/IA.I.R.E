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

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
HBRIDGE_DATA hbridgeData;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
void MotorOn(void){
    HBridge_IN1_StateSet(0);
    HBridge_IN2_StateSet(1);
    OC5CONbits.ON = 1;          // ON PWM
}

void MotorOff(void){
    OC5CONbits.ON = 0;          // OFF PWM
    HBridge_IN1_StateSet(0);
    HBridge_IN2_StateSet(0);
}

void MotorBreak(void){
    HBridge_IN1_StateSet(0);
    HBridge_IN2_StateSet(0);
    OC5CONbits.ON = 1;
}

void SetTimeRamp(uint16_t _time){
    hbridgeData.timeout = _time/20;
}
    
void MotorRamp(void){
    hbridgeData.counter++;
    if(hbridgeData.counter <= 20){
        pwm_ID5_duty_set(hbridgeData.setted_ramp*hbridgeData.counter);
    }
    
    else{
        hbridgeData.counter = 0;
    }
}

void HBRIDGE_Task(void){
    if(hbridgeData.timeout==0){
        
        pwm_ID5_duty_set(30);
        
        T2CONbits.ON = 1;
        MotorOn();
    }
}
/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


/*  A brief description of a section can be given directly below the section
    banner.
 */

/* *****************************************************************************
 End of File
 */
