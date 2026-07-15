/******************************************************************************
 * @file    hal_uart.h
 * @brief   UART Hardware Abstraction Layer
 ******************************************************************************/

#ifndef HAL_UART_H
#define HAL_UART_H

#include "../hal_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * UART Channels
 ******************************************************************************/

typedef enum
{
    HAL_UART_DEBUG = 0,

    HAL_UART_ESP32,

    HAL_UART_RS485,

    HAL_UART_COUNT

} HAL_UART_Channel_t;

/******************************************************************************
 * UART Configuration
 ******************************************************************************/

typedef struct
{
    uint32_t baudRate;

    uint8_t dataBits;

    uint8_t stopBits;

    uint8_t parity;

} HAL_UART_Config_t;

/******************************************************************************
 * API
 ******************************************************************************/

HAL_Status_t HAL_UART_Init(void);

void HAL_UART_Update(void);

void HAL_UART_DeInit(void);

void HAL_UART_Reset(void);

HAL_Status_t HAL_UART_Open(
        HAL_UART_Channel_t channel,
        const HAL_UART_Config_t *config);

HAL_Status_t HAL_UART_Close(
        HAL_UART_Channel_t channel);

HAL_Status_t HAL_UART_Write(
        HAL_UART_Channel_t channel,
        const uint8_t *data,
        uint16_t length);

HAL_Status_t HAL_UART_Read(
        HAL_UART_Channel_t channel,
        uint8_t *buffer,
        uint16_t length,
        uint16_t *received);

uint16_t HAL_UART_Available(
        HAL_UART_Channel_t channel);

void HAL_UART_Flush(
        HAL_UART_Channel_t channel);

#ifdef __cplusplus
}
#endif

#endif
