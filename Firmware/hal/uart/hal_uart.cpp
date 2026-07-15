/******************************************************************************
 * @file    hal_uart.cpp
 ******************************************************************************/

#include "hal_uart.h"

#include <Arduino.h>

/******************************************************************************
 * Default Configurations
 ******************************************************************************/

static HAL_UART_Config_t debugConfig =
{
    115200,
    8,
    1,
    0
};

static HAL_UART_Config_t espConfig =
{
    115200,
    8,
    1,
    0
};

/******************************************************************************
 * Initialization
 ******************************************************************************/

HAL_Status_t HAL_UART_Init(void)
{
    Serial.begin(debugConfig.baudRate);

#if defined(HAVE_HWSERIAL1)
    Serial1.begin(espConfig.baudRate);
#endif

    return HAL_OK;
}

void HAL_UART_Update(void)
{
}

void HAL_UART_DeInit(void)
{
    Serial.end();

#if defined(HAVE_HWSERIAL1)
    Serial1.end();
#endif
}

void HAL_UART_Reset(void)
{
}

/******************************************************************************
 * Open
 ******************************************************************************/

HAL_Status_t HAL_UART_Open(
        HAL_UART_Channel_t channel,
        const HAL_UART_Config_t *config)
{
    if(config == nullptr)
        return HAL_INVALID_PARAMETER;

    switch(channel)
    {
        case HAL_UART_DEBUG:

            Serial.begin(config->baudRate);

            return HAL_OK;

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:

            Serial1.begin(config->baudRate);

            return HAL_OK;

#endif

        default:

            return HAL_INVALID_PARAMETER;
    }
}

/******************************************************************************
 * Close
 ******************************************************************************/

HAL_Status_t HAL_UART_Close(
        HAL_UART_Channel_t channel)
{
    switch(channel)
    {
        case HAL_UART_DEBUG:

            Serial.end();

            return HAL_OK;

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:

            Serial1.end();

            return HAL_OK;

#endif

        default:

            return HAL_INVALID_PARAMETER;
    }
}
/******************************************************************************
 * Write
 ******************************************************************************/

HAL_Status_t HAL_UART_Write(
        HAL_UART_Channel_t channel,
        const uint8_t *data,
        uint16_t length)
{
    if(data == nullptr)
        return HAL_INVALID_PARAMETER;

    switch(channel)
    {
        case HAL_UART_DEBUG:

            Serial.write(data,length);

            return HAL_OK;

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:

            Serial1.write(data,length);

            return HAL_OK;

#endif

        default:

            return HAL_INVALID_PARAMETER;
    }
}

/******************************************************************************
 * Read
 ******************************************************************************/

HAL_Status_t HAL_UART_Read(
        HAL_UART_Channel_t channel,
        uint8_t *buffer,
        uint16_t length,
        uint16_t *received)
{
    if(buffer == nullptr || received == nullptr)
        return HAL_INVALID_PARAMETER;

    *received = 0;

    Stream *port = nullptr;

    switch(channel)
    {
        case HAL_UART_DEBUG:
            port = &Serial;
            break;

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:
            port = &Serial1;
            break;

#endif

        default:
            return HAL_INVALID_PARAMETER;
    }

    while(port->available() && (*received < length))
    {
        buffer[*received] = port->read();
        (*received)++;
    }

    return HAL_OK;
}

/******************************************************************************
 * Available
 ******************************************************************************/

uint16_t HAL_UART_Available(
        HAL_UART_Channel_t channel)
{
    switch(channel)
    {
        case HAL_UART_DEBUG:
            return Serial.available();

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:
            return Serial1.available();

#endif

        default:
            return 0;
    }
}

/******************************************************************************
 * Flush
 ******************************************************************************/

void HAL_UART_Flush(
        HAL_UART_Channel_t channel)
{
    switch(channel)
    {
        case HAL_UART_DEBUG:

            Serial.flush();

            break;

#if defined(HAVE_HWSERIAL1)

        case HAL_UART_ESP32:

            Serial1.flush();

            break;

#endif

        default:
            break;
    }
}
