#ifndef COMMUNICATION_DISPATCHER_H
#define COMMUNICATION_DISPATCHER_H

/******************************************************************************
 * File        : communication_dispatcher.h
 * Description : Communication Packet Dispatcher
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
 * Handler Function Type
 ******************************************************************************/

typedef void
(*CommunicationHandler_t)(
        const CommunicationPacket_t *packet);

/******************************************************************************
 * Public API
 ******************************************************************************/

CommunicationStatus_t
CommunicationDispatcher_Init(void);

CommunicationStatus_t
CommunicationDispatcher_Register(
        CommunicationCommand_t command,
        CommunicationHandler_t handler);

CommunicationStatus_t
CommunicationDispatcher_Dispatch(
        const CommunicationPacket_t *packet);

#ifdef __cplusplus
}
#endif

#endif
