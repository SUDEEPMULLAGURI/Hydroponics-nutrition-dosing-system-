/******************************************************************************
 * File        : communication_transport_uart.cpp
 * Description : UART Transport Layer
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "communication_transport_uart.h"

#include <Arduino.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define COMM_UART             Serial1

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static bool g_initialized = false;

static uint32_t g_txBytes = 0;

static uint32_t g_rxBytes = 0;

static uint32_t g_txErrors = 0;

static uint32_t g_rxErrors = 0;

/******************************************************************************
 * Initialize UART
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransportUART_Init(void)
{
    if(g_initialized)
    {
        return COMM_STATUS_OK;
    }

    COMM_UART.begin(COMM_UART_BAUDRATE);

    g_initialized = true;

    return COMM_STATUS_OK;
}

/******************************************************************************
 * Deinitialize
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransportUART_DeInit(void)
{
    if(!g_initialized)
    {
        return COMM_STATUS_OK;
    }

    COMM_UART.end();

    g_initialized = false;

    return COMM_STATUS_OK;
}

/******************************************************************************
 * Generic Transport Init
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransport_Init(void)
{
    return CommunicationTransportUART_Init();
}

/******************************************************************************
 * Generic Transport DeInit
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransport_DeInit(void)
{
    return CommunicationTransportUART_DeInit();
}

/******************************************************************************
 * Send Bytes
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransport_Send(
        const uint8_t *data,
        uint16_t length)
{
    if(!g_initialized)
    {
        return COMM_STATUS_NOT_INITIALIZED;
    }

    if((data == nullptr) || (length == 0))
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    size_t written =
        COMM_UART.write(data, length);

    if(written != length)
    {
        g_txErrors++;

        return COMM_STATUS_TRANSPORT_ERROR;
    }

    g_txBytes += written;

    return COMM_STATUS_OK;
}

/******************************************************************************
 * Receive Bytes
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransport_Receive(
        uint8_t *data,
        uint16_t *length)
{
    if(!g_initialized)
    {
        return COMM_STATUS_NOT_INITIALIZED;
    }

    if((data == nullptr) || (length == nullptr))
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    uint16_t count = 0;

    while(COMM_UART.available())
    {
        data[count++] = COMM_UART.read();

        if(count >= COMM_PACKET_BUFFER_SIZE)
        {
            break;
        }
    }

    *length = count;

    g_rxBytes += count;

    return COMM_STATUS_OK;
}

/******************************************************************************
 * Available Bytes
 ******************************************************************************/

uint16_t
CommunicationTransport_Available(void)
{
    if(!g_initialized)
    {
        return 0;
    }

    return COMM_UART.available();
}

/******************************************************************************
 * Flush
 ******************************************************************************/

CommunicationStatus_t
CommunicationTransport_Flush(void)
{
    if(!g_initialized)
    {
        return COMM_STATUS_NOT_INITIALIZED;
    }

    COMM_UART.flush();

    while(COMM_UART.available())
    {
        COMM_UART.read();
    }

    return COMM_STATUS_OK;
}

/******************************************************************************
 * Ready
 ******************************************************************************/

bool
CommunicationTransport_IsReady(void)
{
    return g_initialized;
}
