#ifndef COMMUNICATION_TRANSPORT_H
#define COMMUNICATION_TRANSPORT_H

/******************************************************************************
 * File        : communication_transport.h
 * Description : Communication Transport Interface
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "communication_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Transport Type
 ******************************************************************************/

typedef enum
{
    COMM_TRANSPORT_UART = 0,

    COMM_TRANSPORT_SPI,

    COMM_TRANSPORT_CAN,

    COMM_TRANSPORT_USB,

    COMM_TRANSPORT_ETHERNET

} CommunicationTransport_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/**
 * Initialize transport.
 */
CommunicationStatus_t
CommunicationTransport_Init(void);

/**
 * Deinitialize transport.
 */
CommunicationStatus_t
CommunicationTransport_DeInit(void);

/**
 * Send raw bytes.
 */
CommunicationStatus_t
CommunicationTransport_Send(
        const uint8_t *data,
        uint16_t length);

/**
 * Receive raw bytes.
 */
CommunicationStatus_t
CommunicationTransport_Receive(
        uint8_t *data,
        uint16_t *length);

/**
 * Number of bytes waiting.
 */
uint16_t
CommunicationTransport_Available(void);

/**
 * Flush RX/TX buffers.
 */
CommunicationStatus_t
CommunicationTransport_Flush(void);

/**
 * Check transport ready.
 */
bool
CommunicationTransport_IsReady(void);

#ifdef __cplusplus
}
#endif

#endif
