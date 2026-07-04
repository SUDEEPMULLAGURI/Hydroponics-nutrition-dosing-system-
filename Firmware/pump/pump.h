#ifndef PUMP_H
#define PUMP_H

/******************************************************************************
 * File        : pump.h
 * Description : Generic Pump Driver
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "pump_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Pump Status
 ******************************************************************************/

typedef enum
{
    PUMP_STATUS_IDLE = 0,

    PUMP_STATUS_RUNNING,

    PUMP_STATUS_COMPLETED,

    PUMP_STATUS_DISABLED,

    PUMP_STATUS_ERROR

} PumpStatus_t;

/******************************************************************************
 * Pump Runtime Information
 ******************************************************************************/

typedef struct
{
    bool running;

    bool manualMode;

    bool dosingMode;

    uint32_t startTime;

    uint32_t stopTime;

    uint32_t durationMs;

    uint32_t totalRuntimeMs;

    PumpStatus_t status;

} PumpState_t;

/******************************************************************************
 * Initialization
 ******************************************************************************/

bool Pump_Init(void);

/******************************************************************************
 * Periodic Task
 * Call every loop()
 ******************************************************************************/

bool Pump_Update(void);

/******************************************************************************
 * Manual Pump Control
 ******************************************************************************/

bool Pump_Start(PumpId_t pump);

bool Pump_Stop(PumpId_t pump);

bool Pump_Toggle(PumpId_t pump);

/******************************************************************************
 * Timed Dosing
 ******************************************************************************/

bool Pump_StartDose(PumpId_t pump,
                    uint32_t durationMs);

/******************************************************************************
 * State Queries
 ******************************************************************************/

bool Pump_IsRunning(PumpId_t pump);

PumpStatus_t Pump_GetStatus(PumpId_t pump);

const PumpState_t* Pump_GetState(PumpId_t pump);

/******************************************************************************
 * Runtime Information
 ******************************************************************************/

uint32_t Pump_GetRuntime(PumpId_t pump);

void Pump_ResetRuntime(PumpId_t pump);

/******************************************************************************
 * Emergency Control
 ******************************************************************************/

void Pump_StopAll(void);

#ifdef __cplusplus
}
#endif

#endif /* PUMP_H */