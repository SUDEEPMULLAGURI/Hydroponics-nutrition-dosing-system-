#include "ph_calibration.h"
#include <math.h>

/******************************************************************************
 * Internal Calibration State
 ******************************************************************************/

static float g_slope = -5.70f;     // default typical probe slope
static float g_offset = 21.34f;

static float g_v7 = NAN;  // voltage at pH 7
static float g_v4 = NAN;  // voltage at pH 4

/******************************************************************************
 * Convert Voltage ? pH
 ******************************************************************************/

float PH_Calibration_ConvertVoltageToPH(float voltage)
{
    return (g_slope * voltage) + g_offset;
}

/******************************************************************************
 * Setters
 ******************************************************************************/

void PH_Calibration_SetSlope(float slope)
{
    g_slope = slope;
}

void PH_Calibration_SetOffset(float offset)
{
    g_offset = offset;
}

/******************************************************************************
 * Getters
 ******************************************************************************/

float PH_Calibration_GetSlope(void)
{
    return g_slope;
}

float PH_Calibration_GetOffset(void)
{
    return g_offset;
}

/******************************************************************************
 * Store calibration points
 ******************************************************************************/

void PH_Calibration_SetPoint7(float voltage)
{
    g_v7 = voltage;
}

void PH_Calibration_SetPoint4(float voltage)
{
    g_v4 = voltage;
}

/******************************************************************************
 * Compute slope + offset using 2-point calibration
 *
 * pH4 = low acidic buffer
 * pH7 = neutral buffer
 ******************************************************************************/

bool PH_Calibration_Compute(void)
{
    if (isnan(g_v4) || isnan(g_v7))
        return false;

    // Standard pH values
    const float pH4 = 4.0f;
    const float pH7 = 7.0f;

    // slope = (pH7 - pH4) / (V7 - V4)
    g_slope = (pH7 - pH4) / (g_v7 - g_v4);

    // offset = pH7 - slope * V7
    g_offset = pH7 - (g_slope * g_v7);

    return true;
}

/******************************************************************************
 * Reset calibration
 ******************************************************************************/

void PH_Calibration_Reset(void)
{
    g_slope = -5.70f;
    g_offset = 21.34f;

    g_v7 = NAN;
    g_v4 = NAN;
}
