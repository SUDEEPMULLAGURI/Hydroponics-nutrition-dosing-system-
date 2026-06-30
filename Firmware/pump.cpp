/******************************************************************************
 * File        : pump.cpp
 * Description : Generic Pump Driver
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "pump.h"
#include "pump_config.h"

#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Internal Pump State
 ******************************************************************************/

typedef struct
{
    bool running;

    uint32_t startTime;

    uint32_t durationMs;

    uint32_t totalRuntimeMs;

    PumpStatus_t status;

} PumpState_t;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static PumpState_t g_pumpState[PUMP_COUNT];

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void Pump_OutputOn(PumpId_t pump);

static void Pump_OutputOff(PumpId_t pump);

static bool Pump_IsExpired(PumpId_t pump);
/******************************************************************************
 * Start Pump
 ******************************************************************************/

bool Pump_Start(PumpId_t pump)
{
    if (pump >= PUMP_COUNT)
        return false;

    const PumpConfig_t *cfg = PumpConfig_Get(pump);

    if ((cfg == nullptr) || (!cfg->enabled))
        return false;

    if (g_pumpState[pump].running)
        return true;

    Pump_OutputOn(pump);

    g_pumpState[pump].running = true;
    g_pumpState[pump].manualMode = true;
    g_pumpState[pump].dosingMode = false;

    g_pumpState[pump].startTime = millis();
    g_pumpState[pump].status = PUMP_STATUS_RUNNING;

    return true;
}
/******************************************************************************
 * Update Pump Module
 ******************************************************************************/

bool Pump_Update(void)
{
    uint32_t now = millis();

    for (uint8_t i = 0; i < PUMP_COUNT; i++)
    {
        PumpState_t *state = &g_pumpState[i];

        if (!state->running)
            continue;

        /* Timed dosing mode */

        if (state->dosingMode)
        {
            if ((int32_t)(now - state->stopTime) >= 0)
            {
                Pump_OutputOff((PumpId_t)i);

                state->running = false;

                state->totalRuntimeMs +=
                    state->durationMs;

                state->manualMode = false;
                state->dosingMode = false;

                state->status =
                    PUMP_STATUS_COMPLETED;
            }
        }
    }

    return true;
}

