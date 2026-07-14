#ifndef COMMUNICATION_QUEUE_H
#define COMMUNICATION_QUEUE_H

/******************************************************************************
 * File        : communication_queue.h
 * Description : Communication Packet Queue
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
 * Configuration
 ******************************************************************************/

#define COMM_TX_QUEUE_SIZE        16U
#define COMM_RX_QUEUE_SIZE        16U

/******************************************************************************
 * Public API
 ******************************************************************************/

CommunicationStatus_t
CommunicationQueue_Init(void);

CommunicationStatus_t
CommunicationQueue_PushTx(
        const CommunicationPacket_t *packet,
        CommunicationPriority_t priority);

CommunicationStatus_t
CommunicationQueue_PopTx(
        CommunicationPacket_t *packet);

CommunicationStatus_t
CommunicationQueue_PushRx(
        const CommunicationPacket_t *packet);

CommunicationStatus_t
CommunicationQueue_PopRx(
        CommunicationPacket_t *packet);

bool
CommunicationQueue_IsTxEmpty(void);

bool
CommunicationQueue_IsRxEmpty(void);

uint16_t
CommunicationQueue_GetTxCount(void);

uint16_t
CommunicationQueue_GetRxCount(void);

#ifdef __cplusplus
}
#endif

#endif
