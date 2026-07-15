/******************************************************************************
 * @file    hal.cpp
 * @brief   HAL Master Implementation
 ******************************************************************************/

#include "hal.h"

#include "gpio/hal_gpio.h"
#include "adc/hal_adc.h"
#include "pwm/hal_pwm.h"
#include "uart/hal_uart.h"
#include "timer/hal_timer.h"
#include "flash/hal_flash.h"
#include "watchdog/hal_watchdog.h"

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static HAL_Bool_t g_halInitialized = HAL_FALSE;

/******************************************************************************
 * Public Functions
 ******************************************************************************/

HAL_Status_t HAL_Init(void)
{
    if(g_halInitialized == HAL_TRUE)
        return HAL_OK;

    if(HAL_GPIO_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_ADC_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_PWM_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_UART_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_TIMER_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_FLASH_Init() != HAL_OK)
        return HAL_ERROR;

    if(HAL_WATCHDOG_Init() != HAL_OK)
        return HAL_ERROR;

    g_halInitialized = HAL_TRUE;

    return HAL_OK;
}

void HAL_Update(void)
{
    if(g_halInitialized == HAL_FALSE)
        return;

    HAL_TIMER_Update();

    HAL_UART_Update();

    HAL_WATCHDOG_Update();
}

HAL_Bool_t HAL_IsInitialized(void)
{
    return g_halInitialized;
}

uint8_t HAL_GetMajorVersion(void)
{
    return HAL_VERSION_MAJOR;
}

uint8_t HAL_GetMinorVersion(void)
{
    return HAL_VERSION_MINOR;
}

uint8_t HAL_GetPatchVersion(void)
{
    return HAL_VERSION_PATCH;
}
