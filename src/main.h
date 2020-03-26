/* ************************************************************************** */
/**
 * @file main.h
 * @author Ingeniería Apropiada
 * @date 26/03/2020
 * @brief File containing main function.
 */
/* ************************************************************************** */
/** @mainpage IA.I.R.E
 *
 * @section intro_sec Introduction
 * Project for implement low cost mechanical ventilators.
 *
 * @section components_sec Components Used
 * List of components used:
 * 
 * @subsection microcontroller_subsec Microcontroller
 * - Microchip PIC32MX370F512L
 * 
 * @subsection sensors_subsec Sensors
 * - Presion: 
 * - CO2: 
 */

#ifndef _MAIN_H    /* Guard against multiple inclusion */
#define _MAIN_H


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

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************
    
    /**
     * @brief Main function
     * 
     * 
     */
    void main (void);

    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MAIN_H */

/* *****************************************************************************
 End of File
 */
