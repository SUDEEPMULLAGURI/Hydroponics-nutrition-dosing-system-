#ifndef SYSTEM_FSM_H
#define SYSTEM_FSM_H

/******************************************************************************
 * File        : system_fsm.h
 * Description : System Finite State Machine
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "system_states.h"
#include "system_events.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * System Status
 ******************************************************************************/

typedef enum
{
    SYSTEM_STATUS_OK = 0,

    SYSTEM_STATUS_BUSY,

    SYSTEM_STATUS_INVALID_STATE,

    SYSTEM_STATUS_INVALID_EVENT,

    SYSTEM_STATUS_NOT_INITIALIZED,

    SYSTEM_STATUS_ALREADY_INITIALIZED,

    SYSTEM_STATUS_FAULT,

    SYSTEM_STATUS_ERROR

} SystemStatus_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/**
 * Initialize System FSM
 */
SystemStatus_t SystemFSM_Init(void);

/**
 * Update FSM
 * Call periodically from main().
 */
SystemStatus_t SystemFSM_Update(void);

/**
 * Post an event to the FSM.
 */
SystemStatus_t SystemFSM_PostEvent(
                    SystemEvent_t event);

/**
 * Get current state.
 */
SystemState_t SystemFSM_GetState(void);

/**
 * Get previous state.
 */
SystemState_t SystemFSM_GetPreviousState(void);

/**
 * Force state transition.
 * (Reserved for debugging / recovery)
 */
SystemStatus_t SystemFSM_SetState(
                    SystemState_t state);

/**
 * Check if controller is operational.
 */
bool SystemFSM_IsReady(void);

/**
 * Check if controller is in fault mode.
 */
bool SystemFSM_IsFaulted(void);

/**
 * Get last processed event.
 */
SystemEvent_t SystemFSM_GetLastEvent(void);

/**
 * Reset FSM.
 */
SystemStatus_t SystemFSM_Reset(void);

#ifdef __cplusplus
}
#endif

#endif
