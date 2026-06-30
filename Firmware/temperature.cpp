/******************************************************************************
 * File        : temperature.cpp
 * Description : DS18B20 Temperature Sensor Driver
 * Project     : Hydroponic Nutrient Dosing Controller
 ******************************************************************************/

#include "temperature.h"
#include "pins.h"

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*----------------------------------------------------------
    Configuration
----------------------------------------------------------*/

#define TEMP_FILTER_SIZE        10
#define TEMP_MIN_VALUE          0.0f
#define TEMP_MAX_VALUE          60.0f
#define TEMP_TIMEOUT_MS         3000

/*----------------------------------------------------------
    Private Variables
----------------------------------------------------------*/

static OneWire oneWire(TEMP_SENSOR_PIN);
static DallasTemperature ds18b20(&oneWire);

static float temperature = 0.0f;

static SensorStatus_t sensorStatus = SENSOR_NOT_INITIALIZED;

static uint32_t lastUpdateTime = 0;

/* Moving Average */

static float sampleBuffer[TEMP_FILTER_SIZE];

static float runningSum = 0.0f;

static uint8_t sampleIndex = 0;

static uint8_t sampleCount = 0;

/*----------------------------------------------------------
    Private Function Prototypes
----------------------------------------------------------*/

static void Filter_AddSample(float sample);

static float Filter_GetAverage(void);

/*----------------------------------------------------------
    Initialize Sensor
----------------------------------------------------------*/

bool Temperature_Init(void)
{
    ds18b20.begin();

    ds18b20.setResolution(12);

    ds18b20.setWaitForConversion(true);

    for(uint8_t i = 0; i < TEMP_FILTER_SIZE; i++)
    {
        sampleBuffer[i] = 0.0f;
    }

    runningSum = 0.0f;
    sampleIndex = 0;
    sampleCount = 0;

    sensorStatus = SENSOR_OK;

    return true;
}

/*----------------------------------------------------------
    Read Temperature
----------------------------------------------------------*/

bool Temperature_Update(void)
{
    ds18b20.requestTemperatures();

    float value = ds18b20.getTempCByIndex(0);

    if(value == DEVICE_DISCONNECTED_C)
    {
        sensorStatus = SENSOR_DISCONNECTED;
        return false;
    }

    if(value < TEMP_MIN_VALUE || value > TEMP_MAX_VALUE)
    {
        sensorStatus = SENSOR_OUT_OF_RANGE;
        return false;
    }

    Filter_AddSample(value);

    temperature = Filter_GetAverage();

    lastUpdateTime = millis();

    sensorStatus = SENSOR_OK;

    return true;
}

/*----------------------------------------------------------
    Moving Average Filter
----------------------------------------------------------*/

static void Filter_AddSample(float sample)
{
    runningSum -= sampleBuffer[sampleIndex];

    sampleBuffer[sampleIndex] = sample;

    runningSum += sample;

    sampleIndex++;

    if(sampleIndex >= TEMP_FILTER_SIZE)
    {
        sampleIndex = 0;
    }

    if(sampleCount < TEMP_FILTER_SIZE)
    {
        sampleCount++;
    }
}

static float Filter_GetAverage(void)
{
    if(sampleCount == 0)
    {
        return 0.0f;
    }

    return runningSum / sampleCount;
}

/*----------------------------------------------------------
    Public Functions
----------------------------------------------------------*/

float Temperature_GetValue(void)
{
    return temperature;
}

SensorStatus_t Temperature_GetStatus(void)
{
    return sensorStatus;
}

bool Temperature_IsValid(void)
{
    if(sensorStatus != SENSOR_OK)
    {
        return false;
    }

    if((millis() - lastUpdateTime) > TEMP_TIMEOUT_MS)
    {
        sensorStatus = SENSOR_TIMEOUT;
        return false;
    }

    return true;
}
