#ifndef COMMUNICATION_TYPES_H
#define COMMUNICATION_TYPES_H

/******************************************************************************
 * File        : communication_types.h
 * Description : Communication Common Types
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
 * Configuration
 ******************************************************************************/

#define COMM_MAX_PAYLOAD_SIZE          256U
#define COMM_PACKET_BUFFER_SIZE        512U

/******************************************************************************
 * Communication Status
 ******************************************************************************/

typedef enum
{
    COMM_STATUS_OK = 0,

    COMM_STATUS_BUSY,

    COMM_STATUS_TIMEOUT,

    COMM_STATUS_INVALID_PACKET,

    COMM_STATUS_INVALID_CRC,

    COMM_STATUS_INVALID_LENGTH,

    COMM_STATUS_INVALID_COMMAND,

    COMM_STATUS_NOT_INITIALIZED,

    COMM_STATUS_TRANSPORT_ERROR,

    COMM_STATUS_QUEUE_FULL,

    COMM_STATUS_QUEUE_EMPTY,

    COMM_STATUS_UNKNOWN_ERROR

} CommunicationStatus_t;

/******************************************************************************
 * Communication State
 ******************************************************************************/

typedef enum
{
    COMM_STATE_OFFLINE = 0,

    COMM_STATE_CONNECTING,

    COMM_STATE_HANDSHAKE,

    COMM_STATE_ONLINE,

    COMM_STATE_ERROR

} CommunicationState_t;

/******************************************************************************
 * Packet Priority
 ******************************************************************************/

typedef enum
{
    COMM_PRIORITY_LOW = 0,

    COMM_PRIORITY_NORMAL,

    COMM_PRIORITY_HIGH,

    COMM_PRIORITY_CRITICAL

} CommunicationPriority_t;

#ifdef __cplusplus
}
#endif

#endif
