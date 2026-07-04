#ifndef PUMP_CALIBRATION_H
#define PUMP_CALIBRATION_H

/******************************************************************************
 * File        : pump_calibration.h
 * Description : Pump Calibration Manager
 * Project     : Hydroponic Nutrient Dosing Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "pump_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Pump Calibration Structure
 ******************************************************************************/

typedef struct
{
    float flowRateMlPerMin;

} PumpCalibration_t;

/******************************************************************************
 * Initialization
 ******************************************************************************/

bool PumpCalibration_Init(void);

/******************************************************************************
 * Configuration
 ******************************************************************************/

bool PumpCalibration_SetFlowRate(PumpId_t pump,
                                 float mlPerMin);

float PumpCalibration_GetFlowRate(PumpId_t pump);

/******************************************************************************
 * Conversion
 ******************************************************************************/

/* Convert desired volume into pump runtime */

uint32_t PumpCalibration_GetDuration(PumpId_t pump, float volumeMl);

/* Convert runtime into delivered volume */

float PumpCalibration_GetVolume(PumpId_t pump, uint32_t durationMs);

/******************************************************************************
 * Validation
 ******************************************************************************/

bool PumpCalibration_IsValid(PumpId_t pump);

#ifdef __cplusplus
}
#endif

#endif