/******************************************************************************
 * File        : ph.cpp
 * Description : pH Sensor Driver
 * Project     : Smart Hydroponics Controller
 *
 * This module is responsible ONLY for:
 *  - Reading ADC
 *  - Filtering
 *  - Voltage Conversion
 *  - Calling Calibration Module
 *
 * Calibration calculations are handled in:
 *      ph_calibration.cpp
 *
 ******************************************************************************/

#include "ph.h"
#include "ph_calibration.h"
#include "pins.h"
#include "temperature.h"

#include <Arduino.h>
#include <string.h>
#include <math.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define ADC_REFERENCE_VOLTAGE        3.3f
#define ADC_RESOLUTION               4095.0f

#define PH_ADC_SAMPLES               20U
#define PH_FILTER_SIZE               10U

#define PH_MIN_VALID                 0.0f
#define PH_MAX_VALID                 14.0f

#define PH_SENSOR_TIMEOUT_MS         10000U

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static float g_phValue = NAN;

static float g_sensorVoltage = 0.0f;

static SensorStatus_t g_sensorStatus =
        SENSOR_NOT_INITIALIZED;

static uint32_t g_lastUpdateTime = 0;

/******************************************************************************
 * Moving Average Buffer
 ******************************************************************************/

static float g_filterBuffer[PH_FILTER_SIZE];

static float g_runningSum = 0.0f;

static uint8_t g_filterIndex = 0;

static uint8_t g_filterCount = 0;

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static uint16_t PH_ReadADC(void);

static float PH_ADCToVoltage(uint16_t adc);

static uint16_t PH_MedianFilter(uint16_t buffer[],
                                uint8_t size);

static void PH_FilterAdd(float value);

static float PH_FilterAverage(void);

static bool PH_CheckReading(float ph);

/******************************************************************************
 * PH_Init()
 ******************************************************************************/

bool PH_Init(void)
{
    analogReadResolution(12);

    analogSetPinAttenuation(
            PH_SENSOR_PIN,
            ADC_11db);

    memset(g_filterBuffer,
           0,
           sizeof(g_filterBuffer));

    g_runningSum = 0.0f;

    g_filterIndex = 0;

    g_filterCount = 0;

    g_phValue = NAN;

    g_sensorVoltage = 0.0f;

    g_lastUpdateTime = millis();

    g_sensorStatus = SENSOR_OK;

    return true;
}

/******************************************************************************
 * Read ADC
 ******************************************************************************/

static uint16_t PH_ReadADC(void)
{
    return analogRead(PH_SENSOR_PIN);
}

/******************************************************************************
 * ADC Counts -> Voltage
 ******************************************************************************/

static float PH_ADCToVoltage(uint16_t adc)
{
    return
    ((float)adc * ADC_REFERENCE_VOLTAGE)
    / ADC_RESOLUTION;
}
/******************************************************************************
 * Median Filter
 *
 * Removes short-duration spikes caused by electrical noise.
 ******************************************************************************/

static uint16_t PH_MedianFilter(uint16_t data[],
                                uint8_t size)
{
    uint16_t sorted[PH_ADC_SAMPLES];

    memcpy(sorted, data, sizeof(sorted));

    for(uint8_t i = 1; i < size; i++)
    {
        uint16_t key = sorted[i];

        int8_t j = i - 1;

        while((j >= 0) && (sorted[j] > key))
        {
            sorted[j + 1] = sorted[j];

            j--;
        }

        sorted[j + 1] = key;
    }

    return sorted[size / 2];
}

/******************************************************************************
 * Moving Average Filter
 ******************************************************************************/

static void PH_FilterAdd(float value)
{
    g_runningSum -= g_filterBuffer[g_filterIndex];

    g_filterBuffer[g_filterIndex] = value;

    g_runningSum += value;

    g_filterIndex++;

    if(g_filterIndex >= PH_FILTER_SIZE)
    {
        g_filterIndex = 0;
    }

    if(g_filterCount < PH_FILTER_SIZE)
    {
        g_filterCount++;
    }
}

/******************************************************************************
 * Get Moving Average
 ******************************************************************************/

static float PH_FilterAverage(void)
{
    if(g_filterCount == 0)
    {
        return NAN;
    }

    return g_runningSum / (float)g_filterCount;
}

/******************************************************************************
 * Validate pH Reading
 ******************************************************************************/

static bool PH_CheckReading(float ph)
{
    if(isnan(ph))
    {
        g_sensorStatus = SENSOR_ERROR;

        return false;
    }

    if(ph < PH_MIN_VALID)
    {
        g_sensorStatus = SENSOR_OUT_OF_RANGE;

        return false;
    }

    if(ph > PH_MAX_VALID)
    {
        g_sensorStatus = SENSOR_OUT_OF_RANGE;

        return false;
    }

    return true;
}

/******************************************************************************
 * Collect ADC Samples
 *
 * Samples are spaced 1 ms apart to improve noise rejection.
 ******************************************************************************/

static uint16_t PH_ReadFilteredADC(void)
{
    uint16_t samples[PH_ADC_SAMPLES];

    for(uint8_t i = 0; i < PH_ADC_SAMPLES; i++)
    {
        samples[i] = PH_ReadADC();

        delay(1);
    }

    return PH_MedianFilter(samples,
                           PH_ADC_SAMPLES);
}
/******************************************************************************
 * Update pH Measurement
 ******************************************************************************/

bool PH_Update(void)
{
    uint16_t filteredADC;

    float voltage;

    float ph;

    /* Read filtered ADC value */

    filteredADC = PH_ReadFilteredADC();

    /* Convert ADC counts to voltage */

    voltage = PH_ADCToVoltage(filteredADC);

    g_sensorVoltage = voltage;

    /* Convert voltage to pH */

    ph = PH_Calculate(voltage);

    /* Validate measurement */

    if(!PH_CheckReading(ph))
    {
        return false;
    }

    /* Add to moving average */

    PH_FilterAdd(ph);

    /* Store filtered value */

    g_phValue = PH_FilterAverage();

    /* Update timestamp */

    g_lastUpdateTime = millis();

    g_sensorStatus = SENSOR_OK;

    return true;
}
/******************************************************************************
 * File        : ph.cpp (Part 4/4)
 * Description : pH Sensor Driver - Calibration + Final Output
 ******************************************************************************/

#include "ph_calibration.h"

/******************************************************************************
 * pH Calculation (Voltage ? pH)
 *
 * This function delegates all calibration logic to the calibration module.
 * Keeps ph.cpp independent from calibration method.
 ******************************************************************************/

float PH_Calculate(float voltage)
{
    return PH_Calibration_ConvertVoltageToPH(voltage);
}

/******************************************************************************
 * Optional: Set Calibration Parameters (Forwarding API)
 *
 * These functions allow external modules (UI / config / factory calibration)
 * to update calibration without touching internal logic.
 ******************************************************************************/

void PH_SetSlope(float slope)
{
    PH_Calibration_SetSlope(slope);
}

void PH_SetOffset(float offset)
{
    PH_Calibration_SetOffset(offset);
}

/******************************************************************************
 * Optional: Get Calibration Parameters
 ******************************************************************************/

float PH_GetSlope(void)
{
    return PH_Calibration_GetSlope();
}

float PH_GetOffset(void)
{
    return PH_Calibration_GetOffset();
}

/******************************************************************************
 * Reset Sensor State (Useful for reinitialization or fault recovery)
 ******************************************************************************/

void PH_Reset(void)
{
    g_phValue = NAN;
    g_sensorVoltage = 0.0f;

    g_sensorStatus = SENSOR_NOT_INITIALIZED;
    g_lastUpdateTime = millis();

    memset(g_filterBuffer, 0, sizeof(g_filterBuffer));

    g_runningSum = 0.0f;
    g_filterIndex = 0;
    g_filterCount = 0;
}

/******************************************************************************
 * End of File
 ******************************************************************************/
