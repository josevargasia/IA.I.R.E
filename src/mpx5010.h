/* ************************************************************************** */
/** Library for application of MPX5010 Pressure Sensor
 * 
 * @Company Ingeniería Apropiada
 * 
 */
/* ************************************************************************** */

#ifndef _MPX5010_H    /* Guard against multiple inclusion */
#define _MPX5010_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

#define PRESS_WINDOW_SIZE 5 /**< Size of the data buffer for the pressure data*/

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/**
 * @Description This type is a structure that contains the variables required 
 * the sensor.
 */
typedef struct
{
    float measValue; /**< Saves the pressure data value. */
    uint16_t valuesWindow[PRESS_WINDOW_SIZE]; /**< Buffer with the last measured ADC values. */
    uint16_t values_mv[5];      /**< Save values sampled for ADC in mV. */
    
    //uint16_t values_2[5][ADC_MAX_NUM_SAMPLE_PROM]; /**< Save values sampled for avergae. */
    uint16_t values_2_count;    /**< Count samples for avergae. */
    uint32_t values_2_prom[5];  /**< Save the average of sample. */

} PRESS_DATA;

extern PRESS_DATA pressData;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************
/**
  @Function
    int ExampleFunctionName ( int param1, int param2 ) 

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
void pressure_get_value(uint16_t intVal, uint8_t unit);
void pressure_prom_int_values(uint16_t *addValue);




#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
