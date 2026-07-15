/******************************************************************************
 * @file    hal_gpio.h
 * @brief   GPIO Hardware Abstraction Layer
 *
 * This module provides a platform independent interface for digital inputs
 * and outputs.
 *
 ******************************************************************************/

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "../hal_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Logical GPIO IDs
 ******************************************************************************/

typedef enum
{
    HAL_GPIO_PUMP_A = 0,
    HAL_GPIO_PUMP_B,
    HAL_GPIO_PUMP_C,
    HAL_GPIO_PUMP_D,

    HAL_GPIO_MIXER,

    HAL_GPIO_STATUS_LED,

    HAL_GPIO_BUZZER,

    HAL_GPIO_FLOAT_SWITCH,

    HAL_GPIO_DOOR_SWITCH,

    HAL_GPIO_COUNT

} HAL_GPIO_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

HAL_Status_t HAL_GPIO_Init(void);

void HAL_GPIO_Update(void);

void HAL_GPIO_DeInit(void);

void HAL_GPIO_Reset(void);

HAL_Status_t HAL_GPIO_Write(
    HAL_GPIO_t gpio,
    HAL_GPIO_State_t state);

HAL_GPIO_State_t HAL_GPIO_Read(
    HAL_GPIO_t gpio);

HAL_Status_t HAL_GPIO_Toggle(
    HAL_GPIO_t gpio);

HAL_Status_t HAL_GPIO_SetMode(
    HAL_GPIO_t gpio,
    HAL_GPIO_Mode_t mode);

#ifdef __cplusplus
}
#endif

#endif
