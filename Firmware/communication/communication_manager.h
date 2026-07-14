#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

/******************************************************************************
 * File        : communication_manager.h
 * Description : Communication Manager
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
CommunicationManager_Init(void);

CommunicationStatus_t
CommunicationManager_Update(void);

CommunicationStatus_t
CommunicationManager_Send(
        CommunicationCommand_t command,
        const void *payload,
        uint16_t length);

bool
CommunicationManager_IsConnected(void);

CommunicationState_t
CommunicationManager_GetState(void);

uint32_t
CommunicationManager_GetTxPackets(void);

uint32_t
CommunicationManager_GetRxPackets(void);

uint32_t
CommunicationManager_GetCrcErrors(void);

#ifdef __cplusplus
}
#endif

#endif
