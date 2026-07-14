#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

/******************************************************************************
 * File        : communication_manager.h
 * Description : ESP32 Communication Manager
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "communication_packet.h"
#include "communication_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Communication State
 ******************************************************************************/

typedef enum
{
    COMM_MANAGER_OFFLINE = 0,

    COMM_MANAGER_WAIT_HANDSHAKE,

    COMM_MANAGER_CONNECTED,

    COMM_MANAGER_ERROR

} CommunicationManagerState_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

bool CommunicationManager_Init(void);

bool CommunicationManager_Update(void);

bool CommunicationManager_Send(
        CommunicationCommand_t command,
        const void *payload,
        uint16_t payloadLength);

bool CommunicationManager_SendAck(
        uint16_t sequence);

bool CommunicationManager_SendNack(
        uint16_t sequence);

bool CommunicationManager_IsConnected(void);

CommunicationManagerState_t
CommunicationManager_GetState(void);

#ifdef __cplusplus
}
#endif

#endif
