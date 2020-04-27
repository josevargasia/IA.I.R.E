/* ************************************************************************** */
/**
 * @file respira.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing breathing driver.
 */
/* ************************************************************************** */
#include <Arduino.h>

#define RESPIRA_MODE_CONTROL  0
#define RESPIRA_MODE_ASIST 1
#define RESPIRA_MODE_CPAP 2
#define RESPIRA_MODE_CPAP_ASIST 3

#define ALARM_PIN           12
#define ASSISTED_PIN        13
#define CPAP_PIN            10
#define CONTROL_PIN         10
#define STAND_BY_PIN        11
#define INSPIRATION_PIN     9
#define EXPIRATION_PIN      9
#define BUZZER_PIN          20

#define CONTROL_ON          1
#define CONTROL_OFF         0
#define CPAP_ON             0
#define CPAP_OFF            1
#define INSPIRATION_ON      1
#define INSPIRATION_OFF     0
#define EXPIRATION_ON       0
#define EXPIRATION_OFF      1

/**
* @brief Use enum for define states of states machine.
*/
typedef enum
{
    RESPIRA_INSPIRACION = 0,
    RESPIRA_EXPIRACION,
    RESPIRA_STAND_BY,
}RESPIRA_STATES;

/**
 * @brief Respira data structure.
 */
typedef struct
{
    RESPIRA_STATES state;       /**< States of state machine. */    

    uint16_t t_insp;            /**< Inspiration time. */
    uint16_t t_exp;             /**< Expiration time. */

    float sp_insp;              /**< Inspiration pressure. */
    float sp_exp;               /**< Expiration pressure. */

    uint16_t t_out_inps;        /**< Inspiration timeout. */
    uint16_t t_out_exp;         /**< Expiration timeout. */

    uint8_t mode;               /**< Respiration modes. */
    float sensib;               /**< Sensivity value. */

    uint8_t alarm_state;        /**< Parameter that define the alarm code */
    float lim_alarm_h;          /**< Limit for high pressure alarm. */
    float lim_alarm_l;          /**< Limit for low pressure alarm. */

} RESPIRA_DATA;

extern RESPIRA_DATA respiraData;    /**< Manage all variables that bluetooth can use. */

/**
 * @brief Setup respira task
 */
void respira_init(void);

/**
 * @brief Respira task
 */
void respira_task(void);