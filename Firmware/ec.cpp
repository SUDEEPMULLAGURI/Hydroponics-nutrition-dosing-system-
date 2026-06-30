#include "ec.h"
#include "temperature.h"
#include "pins.h"

#include <Arduino.h>
/******************************************************************************
    Configuration
******************************************************************************/

#define EC_ADC_SAMPLES            20

#define EC_FILTER_SIZE            10

#define EC_TIMEOUT_MS             5000

#define ADC_RESOLUTION            4095.0f

#define ADC_REFERENCE_VOLTAGE     3.3f

#define EC_TEMP_COEFFICIENT       0.019f
/******************************************************************************
    Private Variables
******************************************************************************/

static float ecValue = 0.0f;

static float ecVoltage = 0.0f;

static SensorStatus_t sensorStatus = SENSOR_NOT_INITIALIZED;

static uint32_t lastUpdateTime = 0;

static float ecBuffer[EC_FILTER_SIZE];

static float runningSum = 0;

static uint8_t sampleIndex = 0;

static uint8_t sampleCount = 0;

static uint16_t EC_ReadADC(void);

/******************************************************************************
    Private functions 
******************************************************************************/
static uint16_t EC_MedianFilter(uint16_t buffer[], uint8_t size);

static float EC_ADCToVoltage(uint16_t adc);

static float EC_CompensateTemperature(float voltage,
                                      float temperature);

static float EC_VoltageToEC(float voltage);

static void EC_FilterAdd(float value);

static float EC_FilterAverage(void);

/******************************************************************************
    Private functions 
******************************************************************************/
bool EC_Init(void)
{
    analogReadResolution(12);

    runningSum = 0;

    sampleIndex = 0;

    sampleCount = 0;

    for(int i=0;i<EC_FILTER_SIZE;i++)
    {
        ecBuffer[i]=0;
    }

    sensorStatus = SENSOR_OK;

    return true;
}

/******************************************************************************
    Private functions 
******************************************************************************/
static uint16_t EC_ReadADC(void)
{
    return analogRead(EC_SENSOR_PIN);
}

/******************************************************************************
    Private functions 
******************************************************************************/
static float EC_ADCToVoltage(uint16_t adc)
{
    return (adc * ADC_REFERENCE_VOLTAGE)
            / ADC_RESOLUTION;
}
/******************************************************************************
    Private functions 
******************************************************************************/
static float EC_CompensateTemperature(float voltage,
                                      float temperature)
{
    float coefficient;

    coefficient = 1.0f +
                  EC_TEMP_COEFFICIENT *
                  (temperature - 25.0f);

    return voltage / coefficient;
}
/******************************************************************************
    Private functions 
******************************************************************************/
static float EC_VoltageToEC(float voltage)
{
    return
    (
        133.42f * voltage * voltage * voltage

        -

        255.86f * voltage * voltage

        +

        857.39f * voltage

    ) * 0.5f;
}
/******************************************************************************
    Private functions 
******************************************************************************/
static void EC_FilterAdd(float value)
{
    runningSum -= ecBuffer[sampleIndex];

    ecBuffer[sampleIndex] = value;

    runningSum += value;

    sampleIndex++;

    if(sampleIndex >= EC_FILTER_SIZE)
    {
        sampleIndex = 0;
    }

    if(sampleCount < EC_FILTER_SIZE)
    {
        sampleCount++;
    }
}

/******************************************************************************
    Private functions 
******************************************************************************/
static float EC_FilterAverage(void)
{
    if(sampleCount==0)
        return 0;

    return runningSum/sampleCount;
}
/******************************************************************************
    Private functions 
******************************************************************************/
static uint16_t EC_MedianFilter(uint16_t data[],
                                uint8_t size)
{
    uint16_t sorted[EC_ADC_SAMPLES];

    memcpy(sorted,data,sizeof(sorted));

    for(int i=1;i<size;i++)
    {
        uint16_t key=sorted[i];

        int j=i-1;

        while(j>=0 && sorted[j]>key)
        {
            sorted[j+1]=sorted[j];

            j--;
        }

        sorted[j+1]=key;
    }

    return sorted[size/2];
}
/******************************************************************************
    PUblic functions 
******************************************************************************/
bool EC_Update(void)
{
    uint16_t adcSamples[EC_ADC_SAMPLES];

    float temperature;

    temperature = Temperature_GetValue();

    for(int i=0;i<EC_ADC_SAMPLES;i++)
    {
        adcSamples[i]=EC_ReadADC();
        
         delay(1);
    }

    uint16_t filteredADC;

    filteredADC =
        EC_MedianFilter(adcSamples,
                        EC_ADC_SAMPLES);

    ecVoltage =
        EC_ADCToVoltage(filteredADC);

    float correctedVoltage;

    correctedVoltage =
        EC_CompensateTemperature(
            ecVoltage,
            temperature
        );

    float ec;

    ec =
        EC_VoltageToEC(correctedVoltage);

    EC_FilterAdd(ec);

    ecValue =
        EC_FilterAverage();

    lastUpdateTime =
        millis();

    sensorStatus =
        SENSOR_OK;

    return true;
}
/*********************************To return ec value*********************************************/
float EC_GetValue(void)
{
    return ecValue;
}
/**********************************To return voltage value********************************************/
float EC_GetVoltage(void)
{
    return ecVoltage;
}
/***********************************To return sensor status*******************************************/
SensorStatus_t EC_GetStatus(void)
{
    return sensorStatus;
}
/*************************************To validate incoming sensor values*****************************************/
bool EC_IsValid(void)
{
    if(sensorStatus!=SENSOR_OK)
        return false;

    if((millis()-lastUpdateTime)>
        EC_TIMEOUT_MS)
    {
        sensorStatus=SENSOR_TIMEOUT;

        return false;
    }

    return true;
}
/******************************************************************************/



