#ifndef COMMUNICATION_PACKET_H
#define COMMUNICATION_PACKET_H

/******************************************************************************
 * File        : communication_packet.h
 * Description : Communication Packet Definitions
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "communication_types.h"
#include "communication_commands.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Protocol Constants
 ******************************************************************************/

#define COMM_PROTOCOL_VERSION      1U

#define COMM_PACKET_SOF            0xAA55U

#define COMM_MAX_PACKET_SIZE       \
    (sizeof(CommunicationPacketHeader_t) + \
     COMM_MAX_PAYLOAD_SIZE + \
     sizeof(uint16_t))

/******************************************************************************
 * Packet Header
 ******************************************************************************/

typedef struct
{
    uint16_t startOfFrame;

    uint8_t protocolVersion;

    uint8_t flags;

    uint16_t sequenceNumber;

    uint16_t command;

    uint16_t payloadLength;

} CommunicationPacketHeader_t;

/******************************************************************************
 * Complete Packet
 ******************************************************************************/

typedef struct
{
    CommunicationPacketHeader_t header;

    uint8_t payload[COMM_MAX_PAYLOAD_SIZE];

    uint16_t crc;

} CommunicationPacket_t;

/******************************************************************************
 * Packet Flags
 ******************************************************************************/

typedef enum
{
    COMM_FLAG_NONE            = 0x00,

    COMM_FLAG_ACK_REQUIRED    = (1 << 0),

    COMM_FLAG_IS_RESPONSE     = (1 << 1),

    COMM_FLAG_ERROR           = (1 << 2),

    COMM_FLAG_ENCRYPTED       = (1 << 3),

    COMM_FLAG_RESERVED4       = (1 << 4),

    COMM_FLAG_RESERVED5       = (1 << 5),

    COMM_FLAG_RESERVED6       = (1 << 6),

    COMM_FLAG_RESERVED7       = (1 << 7)

} CommunicationPacketFlags_t;

#ifdef __cplusplus
}
#endif

#endif
