
#include <Arduino.h>


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/**
 * @brief Initialize timers configuration
 */
void timer_init(void);

void timer_ID0_init_us (uint32_t period_ms);

void IRAM_ATTR Timer0_ISR(void);

void timer_ID1_init_us (uint32_t period_ms);

void IRAM_ATTR Timer1_ISR(void);