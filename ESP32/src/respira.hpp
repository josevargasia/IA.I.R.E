/* ************************************************************************** */
/**
 * @file respira.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing breathing driver.
 */
/* ************************************************************************** */
#include <Arduino.h>

#define RESPIRA_MODE_CONTROL    0
#define RESPIRA_MODE_ASIST      1
#define RESPIRA_MODE_CPAP       2
#define RESPIRA_MODE_CPAP_ASIST 3

#define CONTROL_ON          0
#define CONTROL_OFF         1
#define CPAP_ON             1
#define CPAP_OFF            0
#define INSPIRATION_ON      1
#define INSPIRATION_OFF     0
#define EXPIRATION_ON       0
#define EXPIRATION_OFF      1

/**
* @brief Use enum for define states of states machine.
*/
typedef enum
{
    RESPIRA_INSPIRATION = 0,
    RESPIRA_EXPIRATION,
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