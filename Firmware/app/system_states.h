#ifndef SYSTEM_STATES_H
#define SYSTEM_STATES_H

/******************************************************************************
 * File        : system_states.h
 * Description : System State Definitions
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * System States
 ******************************************************************************/

typedef enum
{
    /* System just powered up */

    SYSTEM_STATE_POWER_ON = 0,

    /* Initialize all modules */

    SYSTEM_STATE_INITIALIZE,

    /* Verify hardware */

    SYSTEM_STATE_SELF_TEST,

    /* Load calibration and settings */

    SYSTEM_STATE_LOAD_CONFIGURATION,

    /* Ready for operation */

    SYSTEM_STATE_READY,

    /* Normal monitoring */

    SYSTEM_STATE_MONITOR,

    /* Automatic nutrient dosing */

    SYSTEM_STATE_DOSING,

    /* User calibration */

    SYSTEM_STATE_CALIBRATION,

    /* Safe fault mode */

    SYSTEM_STATE_FAULT,

    /* Controlled shutdown */

    SYSTEM_STATE_SHUTDOWN,

    /* Number of states */

    SYSTEM_STATE_COUNT

} SystemState_t;

#ifdef __cplusplus
}
#endif

#endif
