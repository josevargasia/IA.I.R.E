/* ************************************************************************** */
/**
 * @file respira.hpp
 * @author Ingeniería Apropiada
 * @date 08/04/2020
 * @brief File containing breathing driver.
 */
/* ************************************************************************** */
#include <Arduino.h>

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
 * @brief Respira ata structure.
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