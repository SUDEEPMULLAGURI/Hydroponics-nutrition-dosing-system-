#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/******************************************************************************
 * File        : uart_driver.h
 * Description : ESP32 UART Driver
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * UART Status
 ******************************************************************************/

typedef enum
{
    UART_STATUS_OK = 0,

    UART_STATUS_BUSY,

    UART_STATUS_TIMEOUT,

    UART_STATUS_NOT_INITIALIZED,

    UART_STATUS_INVALID_PARAMETER,

    UART_STATUS_BUFFER_FULL,

    UART_STATUS_BUFFER_EMPTY,

    UART_STATUS_ERROR

} UARTStatus_t;

/******************************************************************************
 * UART Statistics
 ******************************************************************************/

typedef struct
{
    uint32_t txBytes;

    uint32_t rxBytes;

    uint32_t txPackets;

    uint32_t rxPackets;

    uint32_t txErrors;

    uint32_t rxErrors;

    uint32_t crcErrors;

} UARTStatistics_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/* Initialization */

UARTStatus_t UARTDriver_Init(void);

UARTStatus_t UARTDriver_DeInit(void);

bool UARTDriver_IsInitialized(void);

/* Data Transfer */

UARTStatus_t UARTDriver_Send(
        const uint8_t *data,
        uint16_t length);

UARTStatus_t UARTDriver_Receive(
        uint8_t *buffer,
        uint16_t *length);

/* Buffer Management */

uint16_t UARTDriver_Available(void);

UARTStatus_t UARTDriver_Flush(void);

/* Statistics */

void UARTDriver_ResetStatistics(void);

UARTStatistics_t UARTDriver_GetStatistics(void);

/* Health */

bool UARTDriver_IsConnected(void);

#ifdef __cplusplus
}
#endif

#endif
