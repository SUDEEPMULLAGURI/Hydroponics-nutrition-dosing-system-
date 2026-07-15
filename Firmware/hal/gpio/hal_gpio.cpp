/******************************************************************************
 * @file    hal_gpio.cpp
 * @brief   GPIO HAL Implementation
 ******************************************************************************/

#include "hal_gpio.h"
#include "../../config/pins.h"

#include <Arduino.h>

/******************************************************************************
 * Private Pin Lookup Table
 ******************************************************************************/

static const uint8_t gpioMap[HAL_GPIO_COUNT] =
{
    PIN_PUMP_A,
    PIN_PUMP_B,
    PIN_PUMP_C,
    PIN_PUMP_D,

    PIN_MIXER,

    PIN_STATUS_LED,

    PIN_BUZZER,

    PIN_FLOAT_SWITCH,

    PIN_DOOR_SWITCH
};

/******************************************************************************
 * Initialization
 ******************************************************************************/

HAL_Status_t HAL_GPIO_Init(void)
{
    pinMode(PIN_PUMP_A, OUTPUT);
    pinMode(PIN_PUMP_B, OUTPUT);
    pinMode(PIN_PUMP_C, OUTPUT);
    pinMode(PIN_PUMP_D, OUTPUT);

    pinMode(PIN_MIXER, OUTPUT);

    pinMode(PIN_STATUS_LED, OUTPUT);

    pinMode(PIN_BUZZER, OUTPUT);

    pinMode(PIN_FLOAT_SWITCH, INPUT_PULLUP);

    pinMode(PIN_DOOR_SWITCH, INPUT_PULLUP);

    digitalWrite(PIN_PUMP_A, LOW);
    digitalWrite(PIN_PUMP_B, LOW);
    digitalWrite(PIN_PUMP_C, LOW);
    digitalWrite(PIN_PUMP_D, LOW);

    digitalWrite(PIN_MIXER, LOW);

    digitalWrite(PIN_BUZZER, LOW);

    return HAL_OK;
}

void HAL_GPIO_Update(void)
{
}

void HAL_GPIO_DeInit(void)
{
}

void HAL_GPIO_Reset(void)
{
}

/******************************************************************************
 * GPIO Write
 ******************************************************************************/

HAL_Status_t HAL_GPIO_Write(
    HAL_GPIO_t gpio,
    HAL_GPIO_State_t state)
{
    if(gpio >= HAL_GPIO_COUNT)
        return HAL_INVALID_PARAMETER;

    digitalWrite(gpioMap[gpio],
                 state == HAL_GPIO_HIGH ? HIGH : LOW);

    return HAL_OK;
}

/******************************************************************************
 * GPIO Read
 ******************************************************************************/

HAL_GPIO_State_t HAL_GPIO_Read(
    HAL_GPIO_t gpio)
{
    if(gpio >= HAL_GPIO_COUNT)
        return HAL_GPIO_LOW;

    return digitalRead(gpioMap[gpio]) ?
            HAL_GPIO_HIGH :
            HAL_GPIO_LOW;
}

/******************************************************************************
 * GPIO Toggle
 ******************************************************************************/

HAL_Status_t HAL_GPIO_Toggle(
    HAL_GPIO_t gpio)
{
    if(gpio >= HAL_GPIO_COUNT)
        return HAL_INVALID_PARAMETER;

    digitalWrite(gpioMap[gpio],
                 !digitalRead(gpioMap[gpio]));

    return HAL_OK;
}

/******************************************************************************
 * GPIO Mode
 ******************************************************************************/

HAL_Status_t HAL_GPIO_SetMode(
    HAL_GPIO_t gpio,
    HAL_GPIO_Mode_t mode)
{
    if(gpio >= HAL_GPIO_COUNT)
        return HAL_INVALID_PARAMETER;

    switch(mode)
    {
        case HAL_GPIO_INPUT:
            pinMode(gpioMap[gpio], INPUT);
            break;

        case HAL_GPIO_OUTPUT:
            pinMode(gpioMap[gpio], OUTPUT);
            break;

        case HAL_GPIO_INPUT_PULLUP:
            pinMode(gpioMap[gpio], INPUT_PULLUP);
            break;

        case HAL_GPIO_ANALOG:
            pinMode(gpioMap[gpio], INPUT);
            break;

        default:
            return HAL_INVALID_PARAMETER;
    }

    return HAL_OK;
}
