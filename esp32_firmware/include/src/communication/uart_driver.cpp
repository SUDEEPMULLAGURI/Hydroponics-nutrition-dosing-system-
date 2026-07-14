/******************************************************************************
 * File        : uart_driver.cpp
 * Description : ESP32 UART Driver
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "uart_driver.h"
#include "esp32_config.h"

#include <Arduino.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

/* UART used to communicate with MAX32630 */

static HardwareSerial& g_uart = ESP32_UART_PORT;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static bool g_initialized = false;

static UARTStatistics_t g_statistics = {0};

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void UARTDriver_ResetCounters(void);
/******************************************************************************
 * Initialize UART
 ******************************************************************************/

UARTStatus_t UARTDriver_Init(void)
{
    if(g_initialized)
    {
        return UART_STATUS_OK;
    }

    /*
     * UART2
     *
     * TX Pin : Configurable
     * RX Pin : Configurable
     */

    g_uart.begin(
            ESP32_UART_BAUDRATE,
            SERIAL_8N1);

    UARTDriver_ResetCounters();

    g_initialized = true;

    return UART_STATUS_OK;
}
/******************************************************************************
 * Deinitialize UART
 ******************************************************************************/

UARTStatus_t UARTDriver_DeInit(void)
{
    if(!g_initialized)
    {
        return UART_STATUS_OK;
    }

    g_uart.end();

    g_initialized = false;

    return UART_STATUS_OK;
}
/******************************************************************************
 * Driver State
 ******************************************************************************/

bool UARTDriver_IsInitialized(void)
{
    return g_initialized;
}
/******************************************************************************
 * Reset Statistics
 ******************************************************************************/

static void UARTDriver_ResetCounters(void)
{
    memset(&g_statistics,
           0,
           sizeof(g_statistics));
}

void UARTDriver_ResetStatistics(void)
{
    UARTDriver_ResetCounters();
}
/******************************************************************************
 * Get Statistics
 ******************************************************************************/

UARTStatistics_t UARTDriver_GetStatistics(void)
{
    return g_statistics;
}
/******************************************************************************
 * Get Statistics
 ******************************************************************************/

UARTStatistics_t UARTDriver_GetStatistics(void)
{
    return g_statistics;
}
/******************************************************************************
 * Send Data
 ******************************************************************************/

UARTStatus_t
UARTDriver_Send(
        const uint8_t *data,
        uint16_t length)
{
    if(!g_initialized)
    {
        return UART_STATUS_NOT_INITIALIZED;
    }

    if((data == nullptr) || (length == 0))
    {
        return UART_STATUS_INVALID_PARAMETER;
    }

    size_t written = g_uart.write(data, length);

    if(written != length)
    {
        g_statistics.txErrors++;

        return UART_STATUS_ERROR;
    }

    g_uart.flush();

    g_statistics.txBytes += written;

    g_statistics.txPackets++;

    return UART_STATUS_OK;
}
/******************************************************************************
 * Receive Data
 ******************************************************************************/

UARTStatus_t
UARTDriver_Receive(
        uint8_t *buffer,
        uint16_t *length)
{
    if(!g_initialized)
    {
        return UART_STATUS_NOT_INITIALIZED;
    }

    if((buffer == nullptr) || (length == nullptr))
    {
        return UART_STATUS_INVALID_PARAMETER;
    }

    uint16_t count = 0;

    while(g_uart.available())
    {
        buffer[count++] = g_uart.read();

        if(count >= ESP32_UART_RX_BUFFER_SIZE)
        {
            break;
        }
    }

    *length = count;

    if(count > 0)
    {
        g_statistics.rxBytes += count;

        g_statistics.rxPackets++;
    }

    return UART_STATUS_OK;
}
/******************************************************************************
 * Bytes Available
 ******************************************************************************/

uint16_t
UARTDriver_Available(void)
{
    if(!g_initialized)
    {
        return 0;
    }

    return g_uart.available();
}
/******************************************************************************
 * Flush UART
 ******************************************************************************/

UARTStatus_t
UARTDriver_Flush(void)
{
    if(!g_initialized)
    {
        return UART_STATUS_NOT_INITIALIZED;
    }

    g_uart.flush();

    while(g_uart.available())
    {
        g_uart.read();
    }

    return UART_STATUS_OK;
}
/******************************************************************************
 * Connection State
 ******************************************************************************/

bool
UARTDriver_IsConnected(void)
{
    return g_initialized;
}

