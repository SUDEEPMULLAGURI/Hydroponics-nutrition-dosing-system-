#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

/******************************************************************************
 * File        : communication_protocol.h
 * Description : Communication Protocol Layer
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "communication_packet.h"
#include "communication_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Public API
 ******************************************************************************/

/**
 * Initialize protocol layer.
 */
CommunicationStatus_t CommunicationProtocol_Init(void);

/**
 * Build a packet.
 */
CommunicationStatus_t CommunicationProtocol_CreatePacket(
        CommunicationPacket_t *packet,
        CommunicationCommand_t command,
        const void *payload,
        uint16_t payloadLength,
        uint8_t flags);

/**
 * Serialize packet into byte buffer.
 */
CommunicationStatus_t CommunicationProtocol_Encode(
        const CommunicationPacket_t *packet,
        uint8_t *buffer,
        uint16_t *length);

/**
 * Deserialize byte buffer into packet.
 */
CommunicationStatus_t CommunicationProtocol_Decode(
        const uint8_t *buffer,
        uint16_t length,
        CommunicationPacket_t *packet);

/**
 * Send packet.
 */
CommunicationStatus_t CommunicationProtocol_Send(
        const CommunicationPacket_t *packet);

/**
 * Receive packet.
 */
CommunicationStatus_t CommunicationProtocol_Receive(
        CommunicationPacket_t *packet);

#ifdef __cplusplus
}
#endif

#endif
