/******************************************************************************
 * File        : hal_types.h
 * Author      : Hydroponics Controller Project
 * Description :
 * Common HAL data types used throughout the firmware.
 *
 * This file contains platform-independent enumerations, typedefs and status
 * codes shared by all HAL modules.
 *
 * NOTE:
 * No Arduino or MCU specific headers shall be included here.
 ******************************************************************************/

#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * HAL Status
 ******************************************************************************/

typedef enum
{
    HAL_OK = 0,

    HAL_ERROR,

    HAL_BUSY,

    HAL_TIMEOUT,

    HAL_INVALID_PARAMETER,

    HAL_NOT_INITIALIZED

} HAL_Status_t;

/******************************************************************************
 * GPIO Direction
 ******************************************************************************/

typedef enum
{
    HAL_GPIO_INPUT = 0,

    HAL_GPIO_OUTPUT,

    HAL_GPIO_INPUT_PULLUP,

    HAL_GPIO_INPUT_PULLDOWN,

    HAL_GPIO_ANALOG

} HAL_GPIO_Mode_t;

/******************************************************************************
 * GPIO State
 ******************************************************************************/

typedef enum
{
    HAL_GPIO_LOW = 0,

    HAL_GPIO_HIGH

} HAL_GPIO_State_t;

/******************************************************************************
 * Logic State
 ******************************************************************************/

typedef enum
{
    HAL_DISABLE = 0,

    HAL_ENABLE

} HAL_State_t;

/******************************************************************************
 * Generic Result
 ******************************************************************************/

typedef enum
{
    HAL_FALSE = 0,

    HAL_TRUE

} HAL_Bool_t;

#ifdef __cplusplus
}
#endif

#endif
