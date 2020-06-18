
#include <Arduino.h>

/* ************************************************************************** */
/**
 * @file system_definitions.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing main system definitions.
 */
/* ************************************************************************** */

#include "bluetooth_IAIRE.hpp"
#include "sci.hpp"
#include "timer.hpp"
#include "eeprom.hpp"
#include "pid.hpp"
#include "respira.hpp"
#include "adc.hpp"
#include "mpx5010.hpp"
#include "i2c_IAIRE.hpp"
#include "mg811.hpp"
#include "max30102.hpp"
#include "pwm.hpp"


/**
 * @brief Configuration data structure.
 */
typedef struct
{
    float pressure_max;             /**< Configure pressure. */
    uint16_t inspiration_time;      /**< Configure inspiration time. */
    uint16_t expiration_time;       /**< Configure expiration time. */
    uint8_t pwm5_duty;              /**< Configure Duty cycle of PWM pump. */
    uint32_t pwm5_frec;             /**< Configure frecuency of PWM pump. */
} CONFIG_DATA;

extern CONFIG_DATA configData;    /**< Manage all variables that application can be use to configure system. */
extern uint16_t carac_timeout;

// #define PCB

#ifdef PCB
    #define ALARM_LED_PIN           12
    #define ASSISTED_LED_PIN        13
    #define CPAP_LED_PIN            27
    #define CONTROL_LED_PIN         27
    #define STBY_LED_PIN            14
    #define INSPIRATION_LED_PIN     26
    #define EXPIRATION_LED_PIN      26
    #define BUZZER_PIN              20
    #define BT_LED_PIN              25               /**< Led pin configuration. */
    #define START_STOP_PIN          19

#else
    #define ALARM_LED_PIN           12
    #define ASSISTED_LED_PIN        27
    #define CPAP_LED_PIN            14
    #define CONTROL_LED_PIN         14
    #define STBY_LED_PIN            26
    #define INSPIRATION_LED_PIN     25
    #define EXPIRATION_LED_PIN      25
    #define BUZZER_PIN              20
    #define BT_LED_PIN              13
    #define START_STOP_PIN          19
#endif


/**
 * @brief Initialize variables from EEPROM 
 */
void APP_init(void);