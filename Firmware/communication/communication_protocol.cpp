/******************************************************************************
 * File        : communication_protocol.cpp
 * Description : Communication Protocol Layer
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "communication_protocol.h"

#include <string.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static uint16_t g_sequenceNumber = 0;

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static uint16_t CommunicationProtocol_CRC16(
        const uint8_t *data,
        uint16_t length);

static bool CommunicationProtocol_CheckHeader(
        const CommunicationPacketHeader_t *header);

/******************************************************************************
 * Initialize
 ******************************************************************************/

CommunicationStatus_t
CommunicationProtocol_Init(void)
{
    g_sequenceNumber = 0;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Create Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationProtocol_CreatePacket(
        CommunicationPacket_t *packet,
        CommunicationCommand_t command,
        const void *payload,
        uint16_t payloadLength,
        uint8_t flags)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    if(payloadLength > COMM_MAX_PAYLOAD_SIZE)
    {
        return COMM_STATUS_INVALID_LENGTH;
    }

    memset(packet, 0, sizeof(CommunicationPacket_t));

    /* Header */

    packet->header.startOfFrame =
        COMM_PACKET_SOF;

    packet->header.protocolVersion =
        COMM_PROTOCOL_VERSION;

    packet->header.flags =
        flags;

    packet->header.sequenceNumber =
        ++g_sequenceNumber;

    packet->header.command =
        (uint16_t)command;

    packet->header.payloadLength =
        payloadLength;

    /* Payload */

    if((payload != nullptr) &&
       (payloadLength > 0))
    {
        memcpy(packet->payload,
               payload,
               payloadLength);
    }

    /* CRC will be calculated during Encode() */

    packet->crc = 0;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Decode Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationProtocol_Decode(
        const uint8_t *buffer,
        uint16_t length,
        CommunicationPacket_t *packet)
{
    uint16_t index = 0;

    if ((buffer == nullptr) ||
        (packet == nullptr))
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    /* Minimum packet size */

    if (length <
        (sizeof(CommunicationPacketHeader_t)
        + sizeof(uint16_t)))
    {
        return COMM_STATUS_INVALID_LENGTH;
    }

    /*----------------------------------------------------------
        Header
    ----------------------------------------------------------*/

    memcpy(&packet->header,
           buffer,
           sizeof(CommunicationPacketHeader_t));

    index +=
        sizeof(CommunicationPacketHeader_t);

    /* Validate Header */

    if (!CommunicationProtocol_CheckHeader(
            &packet->header))
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    /*----------------------------------------------------------
        Validate Payload Length
    ----------------------------------------------------------*/

    if (packet->header.payloadLength >
        COMM_MAX_PAYLOAD_SIZE)
    {
        return COMM_STATUS_INVALID_LENGTH;
    }

    if (length !=
        sizeof(CommunicationPacketHeader_t)
        +
        packet->header.payloadLength
        +
        sizeof(uint16_t))
    {
        return COMM_STATUS_INVALID_LENGTH;
    }

    /*----------------------------------------------------------
        Payload
    ----------------------------------------------------------*/

    if (packet->header.payloadLength > 0)
    {
        memcpy(packet->payload,
               buffer + index,
               packet->header.payloadLength);

        index +=
            packet->header.payloadLength;
    }

    /*----------------------------------------------------------
        CRC
    ----------------------------------------------------------*/

    memcpy(&packet->crc,
           buffer + index,
           sizeof(uint16_t));

    return COMM_STATUS_OK;
}

