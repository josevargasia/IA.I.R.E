/* ************************************************************************** */
/**
 * @file timer.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing Timers driver.
 */
/* ************************************************************************** */
#include <Arduino.h>

/**
 * @brief Initialize timers configuration
 */
void timer_init(void);

/**
 * @brief Initialize timer 0 configuration in us
 * @code
 *      timer_ID0_init_us(100);  // 100 us
 * @endcode
 * @param period_us    Number of microseconds to set Timer 0 interription
 */
void timer_ID0_init_us (uint32_t period_us);

/**
 * @brief Timer 0 ISR
 */
void IRAM_ATTR Timer0_ISR(void);

/**
 * @brief Initialize timer 1 configuration in us
 * @code
 *      timer_ID1_init_us(100);  // 100 us
 * @endcode
 * @param period_us    Number of microseconds to set Timer 1 interription
 */
void timer_ID1_init_us (uint32_t period_us);

/**
 * @brief Timer 1 ISR
 */
void IRAM_ATTR Timer1_ISR(void);