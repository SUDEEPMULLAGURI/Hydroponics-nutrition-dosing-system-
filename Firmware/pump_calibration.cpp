/******************************************************************************
 * File        : pump_calibration.cpp
 * Description : Pump Calibration Manager
 * Project     : Hydroponic Nutrient Dosing Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "pump_calibration.h"

#include <string.h>

/******************************************************************************
 * Default Flow Rate
 *
 * Used until user performs calibration.
 ******************************************************************************/

#define DEFAULT_FLOW_RATE_ML_PER_MIN      (100.0f)

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static PumpCalibration_t g_calibration[PUMP_COUNT];

/******************************************************************************
 * Initialize
 ******************************************************************************/

bool PumpCalibration_Init(void)
{
    for(uint8_t i = 0; i < PUMP_COUNT; i++)
    {
        g_calibration[i].flowRateMlPerMin = DEFAULT_FLOW_RATE_ML_PER_MIN;

        g_calibration[i].minimumDoseMl = 1.0f;

        g_calibration[i].maximumDoseMl = 500.0f;

        g_calibration[i].deadTimeMs = 100.0f;

        g_calibration[i].correctionFactor = 1.0f;

        g_calibration[i].calibrated = false;
    }

    return true;
}

/******************************************************************************
 * Set Flow Rate
 ******************************************************************************/

bool PumpCalibration_SetFlowRate(PumpId_t pump,
                                 float mlPerMin)
{
    if(pump >= PUMP_COUNT)
        return false;

    if(mlPerMin <= 0.0f)
        return false;

    g_calibration[pump].flowRateMlPerMin = mlPerMin;

    g_calibration[pump].calibrated = true;

    return true;
}

/******************************************************************************
 * Get Flow Rate
 ******************************************************************************/

float PumpCalibration_GetFlowRate(PumpId_t pump)
{
    if(pump >= PUMP_COUNT)
        return 0.0f;

    return g_calibration[pump].flowRateMlPerMin;
}

/******************************************************************************
 * Convert Volume -> Duration
 ******************************************************************************/

uint32_t PumpCalibration_GetDuration(PumpId_t pump,
                                     float volumeMl)
{
    if(pump >= PUMP_COUNT)
        return 0;

    PumpCalibration_t *cfg = &g_calibration[pump];

    if(cfg->flowRateMlPerMin <= 0.0f)
        return 0;

    /* Apply limits */

    if(volumeMl < cfg->minimumDoseMl)
    {
        volumeMl = cfg->minimumDoseMl;
    }

    if(volumeMl > cfg->maximumDoseMl)
    {
        volumeMl = cfg->maximumDoseMl;
    }

    /* Apply correction factor */

    volumeMl *= cfg->correctionFactor;

    /* Convert mL -> milliseconds */

    float duration =
        (volumeMl / cfg->flowRateMlPerMin) * 60000.0f;

    /* Add pump startup delay */

    duration += cfg->deadTimeMs;

    return (uint32_t)duration;
}

/******************************************************************************
 * Convert Duration -> Volume
 ******************************************************************************/

float PumpCalibration_GetVolume(PumpId_t pump,
                                uint32_t durationMs)
{
    if(pump >= PUMP_COUNT)
        return 0.0f;

    PumpCalibration_t *cfg = &g_calibration[pump];

    if(cfg->flowRateMlPerMin <= 0.0f)
        return 0.0f;

    float runtime = (float)durationMs;

    if(runtime > cfg->deadTimeMs)
    {
        runtime -= cfg->deadTimeMs;
    }
    else
    {
        runtime = 0.0f;
    }

    float volume =
        (runtime / 60000.0f) *
        cfg->flowRateMlPerMin;

    volume /= cfg->correctionFactor;

    return volume;
}

/******************************************************************************
 * Validation
 ******************************************************************************/

bool PumpCalibration_IsValid(PumpId_t pump)
{
    if(pump >= PUMP_COUNT)
        return false;

    return g_calibration[pump].calibrated;
}
