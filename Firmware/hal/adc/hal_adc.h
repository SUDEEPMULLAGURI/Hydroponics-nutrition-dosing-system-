/******************************************************************************
 * @file    hal_adc.h
 * @brief   ADC Hardware Abstraction Layer
 *
 * Hardware independent Analog-to-Digital Converter interface.
 *
 ******************************************************************************/

#ifndef HAL_ADC_H
#define HAL_ADC_H

#include "../hal_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * ADC Channels
 ******************************************************************************/

typedef enum
{
    HAL_ADC_CHANNEL_0 = 0,
    HAL_ADC_CHANNEL_1,
    HAL_ADC_CHANNEL_2,
    HAL_ADC_CHANNEL_3,
    HAL_ADC_CHANNEL_4,
    HAL_ADC_CHANNEL_5,
    HAL_ADC_CHANNEL_6,
    HAL_ADC_CHANNEL_7,

    HAL_ADC_CHANNEL_COUNT

} HAL_ADC_Channel_t;

/******************************************************************************
 * ADC Configuration
 ******************************************************************************/

typedef struct
{
    uint8_t resolution;

    float referenceVoltage;

} HAL_ADC_Config_t;

/******************************************************************************
 * API
 ******************************************************************************/

HAL_Status_t HAL_ADC_Init(void);

void HAL_ADC_Update(void);

void HAL_ADC_DeInit(void);

void HAL_ADC_Reset(void);

HAL_Status_t HAL_ADC_ReadRaw(
        HAL_ADC_Channel_t channel,
        uint16_t *value);

HAL_Status_t HAL_ADC_ReadVoltage(
        HAL_ADC_Channel_t channel,
        float *voltage);

uint16_t HAL_ADC_MaxValue(void);

float HAL_ADC_ReferenceVoltage(void);

#ifdef __cplusplus
}
#endif

#endif
