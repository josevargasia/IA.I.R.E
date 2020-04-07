/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _RESPIRA_H    /* Guard against multiple inclusion */
#define _RESPIRA_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "system_definitions.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
      typedef enum
    {
        RESPIRA_INSPIRACION = 0,
        RESPIRA_EXPIRACION,
        RESPIRA_STAND_BY,
    }RESPIRA_STATES;
    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************
    
    typedef struct
     {
        RESPIRA_STATES state;

        uint16_t t_insp;
        uint16_t t_exp;
        
        float sp_insp;
        float sp_exp;
        
        uint16_t t_out_inps;
        uint16_t t_out_exp;

     } RESPIRA_DATA;

     extern RESPIRA_DATA respiraData;    /**< Manage all variables that bluetooth can use. */
    


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
     
    void respira_init(void);
    void respira_task(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _RESPIRA_H */

/* *****************************************************************************
 End of File
 */
