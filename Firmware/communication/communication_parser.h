#ifndef COMMUNICATION_PARSER_H
#define COMMUNICATION_PARSER_H

/******************************************************************************
 * File        : communication_parser.h
 * Description : UART Packet Parser
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

CommunicationStatus_t
CommunicationParser_Init(void);

CommunicationStatus_t
CommunicationParser_ProcessByte(
        uint8_t byte);

bool
CommunicationParser_IsPacketReady(void);

CommunicationStatus_t
CommunicationParser_GetPacket(
        CommunicationPacket_t *packet);

void
CommunicationParser_Reset(void);

#ifdef __cplusplus
}
#endif

#endif
