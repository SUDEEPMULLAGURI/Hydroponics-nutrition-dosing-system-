/******************************************************************************
 * File        : communication_parser.cpp
 * Description : UART Packet Parser
 ******************************************************************************/

#include "communication_parser.h"

#include "communication_protocol.h"

#include <string.h>

/******************************************************************************
 * Parser States
 ******************************************************************************/

typedef enum
{
    PARSER_WAIT_SOF1 = 0,

    PARSER_WAIT_SOF2,

    PARSER_HEADER,

    PARSER_PAYLOAD,

    PARSER_CRC

} ParserState_t;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static ParserState_t
g_state =
PARSER_WAIT_SOF1;

static uint8_t
g_buffer[COMM_MAX_PACKET_SIZE];

static uint16_t
g_index = 0;

static uint16_t
g_expectedLength = 0;

static bool
g_packetReady = false;

static CommunicationPacket_t
g_packet;
/******************************************************************************
 * Process Incoming Byte
 ******************************************************************************/

CommunicationStatus_t
CommunicationParser_ProcessByte(uint8_t byte)
{
    switch(g_state)
    {
        /**********************************************************************
         * Wait First SOF Byte (0xAA)
         **********************************************************************/

        case PARSER_WAIT_SOF1:

            if(byte == 0xAA)
            {
                g_buffer[0] = byte;
                g_index = 1;

                g_state = PARSER_WAIT_SOF2;
            }

            break;

        /**********************************************************************
         * Wait Second SOF Byte (0x55)
         **********************************************************************/

        case PARSER_WAIT_SOF2:

            if(byte == 0x55)
            {
                g_buffer[g_index++] = byte;

                g_state = PARSER_HEADER;
            }
            else
            {
                CommunicationParser_Reset();
            }

            break;

        /**********************************************************************
         * Read Header
         **********************************************************************/

        case PARSER_HEADER:

            g_buffer[g_index++] = byte;

            if(g_index >= sizeof(CommunicationPacketHeader_t))
            {
                CommunicationPacketHeader_t *header =
                    (CommunicationPacketHeader_t *)g_buffer;

                if(header->payloadLength >
                   COMM_MAX_PAYLOAD_SIZE)
                {
                    CommunicationParser_Reset();

                    return COMM_STATUS_INVALID_LENGTH;
                }

                g_expectedLength =
                    sizeof(CommunicationPacketHeader_t)
                    +
                    header->payloadLength
                    +
                    sizeof(uint16_t);

                if(header->payloadLength == 0)
                {
                    g_state = PARSER_CRC;
                }
                else
                {
                    g_state = PARSER_PAYLOAD;
                }
            }

            break;

        /**********************************************************************
         * Read Payload
         **********************************************************************/

        case PARSER_PAYLOAD:

            g_buffer[g_index++] = byte;

            if(g_index >=
               (g_expectedLength - sizeof(uint16_t)))
            {
                g_state = PARSER_CRC;
            }

            break;

        /**********************************************************************
         * Read CRC
         **********************************************************************/

        case PARSER_CRC:

            g_buffer[g_index++] = byte;

            if(g_index >= g_expectedLength)
            {
                CommunicationStatus_t status;

                status =
                    CommunicationProtocol_Decode(
                        g_buffer,
                        g_expectedLength,
                        &g_packet);

                if(status == COMM_STATUS_OK)
                {
                    status =
                        CommunicationProtocol_Verify(
                            &g_packet);

                    if(status == COMM_STATUS_OK)
                    {
                        g_packetReady = true;
                    }
                }

                CommunicationParser_Reset();

                return status;
            }

            break;

        default:

            CommunicationParser_Reset();

            break;
    }

    return COMM_STATUS_OK;
}

