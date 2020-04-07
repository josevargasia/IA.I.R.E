
#include <Arduino.h>

typedef enum
{
    RESPIRA_INSPIRACION = 0,
    RESPIRA_EXPIRACION,
    RESPIRA_STAND_BY,
}RESPIRA_STATES;

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

void respira_init(void);
void respira_task(void);