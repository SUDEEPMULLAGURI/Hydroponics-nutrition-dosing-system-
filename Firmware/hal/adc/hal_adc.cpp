/******************************************************************************
 * @file    hal_adc.cpp
 ******************************************************************************/

#include "hal_adc.h"

#include <Arduino.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

static constexpr float ADC_REFERENCE = 3.3f;

static constexpr uint16_t ADC_MAX = 4095;

/******************************************************************************
 * Channel Lookup Table
 *
 * These values come from config/pins.h
 ******************************************************************************/

#include "../../config/pins.h"

static const uint8_t adcMap[HAL_ADC_CHANNEL_COUNT] =
{
    PIN_ADC0,
    PIN_ADC1,
    PIN_ADC2,
    PIN_ADC3,
    PIN_ADC4,
    PIN_ADC5,
    PIN_ADC6,
    PIN_ADC7
};

/******************************************************************************
 * Initialization
 ******************************************************************************/

HAL_Status_t HAL_ADC_Init(void)
{
    analogReadResolution(12);

    return HAL_OK;
}

void HAL_ADC_Update(void)
{
}

void HAL_ADC_DeInit(void)
{
}

void HAL_ADC_Reset(void)
{
}
/******************************************************************************
 * Read Raw ADC
 ******************************************************************************/

HAL_Status_t HAL_ADC_ReadRaw(
        HAL_ADC_Channel_t channel,
        uint16_t *value)
{
    if(channel >= HAL_ADC_CHANNEL_COUNT)
        return HAL_INVALID_PARAMETER;

    if(value == nullptr)
        return HAL_INVALID_PARAMETER;

    *value = analogRead(adcMap[channel]);

    return HAL_OK;
}

/******************************************************************************
 * Read Voltage
 ******************************************************************************/

HAL_Status_t HAL_ADC_ReadVoltage(
        HAL_ADC_Channel_t channel,
        float *voltage)
{
    if(voltage == nullptr)
        return HAL_INVALID_PARAMETER;

    uint16_t raw;

    if(HAL_ADC_ReadRaw(channel,&raw) != HAL_OK)
        return HAL_ERROR;

    *voltage =
        ((float)raw / ADC_MAX) * ADC_REFERENCE;

    return HAL_OK;
}

/******************************************************************************
 * Utility
 ******************************************************************************/

uint16_t HAL_ADC_MaxValue(void)
{
    return ADC_MAX;
}

float HAL_ADC_ReferenceVoltage(void)
{
    return ADC_REFERENCE;
}

