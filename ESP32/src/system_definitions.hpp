
#include <Arduino.h>


#include "bluetooth_IAIRE.hpp"
#include "sci.hpp"
#include "timer.hpp"
#include "eeprom.hpp"
#include "pid.hpp"
#include "respira.hpp"
#include "adc.hpp"
#include "mpx5010.hpp"


/**
 * @brief Configuration data structure.
 */
typedef struct
{
    float pressure_max;          /**< Configure pressure. */
    uint16_t inspiration_time;      /**< Configure inspiration time. */
    uint16_t expiration_time;       /**< Configure expiration time. */
    uint8_t pwm5_duty;              /**< Configure Duty cycle of PWM pump. */
    uint32_t pwm5_frec;             /**< Configure frecuency of PWM pump. */
} CONFIG_DATA;

extern CONFIG_DATA configData;    /**< Manage all variables that application can be use to configure system. */

const int LEDPin = 2;


void APP_init(void);