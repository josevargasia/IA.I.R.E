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

#include "respira.h"


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
RESPIRA_DATA respiraData;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

void respira_init(void){
    respiraData.state = RESPIRA_INSPIRACION;
}

void respira_task(void){
    switch(respiraData.state){
        case RESPIRA_INSPIRACION:
        {
            pidData.SetP = respiraData.sp_insp;
            pid_task();
            if(respiraData.t_out_inps == 0){
                respiraData.t_out_exp = respiraData.t_exp;
                respiraData.state = RESPIRA_EXPIRACION;
            }
            break;
        }
        
        case RESPIRA_EXPIRACION:
        {
            pidData.SetP = respiraData.sp_exp;
            pid_task();
            if(respiraData.t_out_exp == 0){
                respiraData.t_out_inps = respiraData.t_insp;
                respiraData.state = RESPIRA_INSPIRACION;
            }
            break;
        }
        
        case RESPIRA_STAND_BY:
        {
            
        }
        
        default:
        {
            respiraData.state = RESPIRA_STAND_BY;
            break;
        }
    }
    
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */





/* *****************************************************************************
 End of File
 */
