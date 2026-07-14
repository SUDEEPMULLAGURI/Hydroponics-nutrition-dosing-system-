/******************************************************************************
 * File        : communication_queue.cpp
 ******************************************************************************/

#include "communication_queue.h"

#include <string.h>

/******************************************************************************
 * Queue Object
 ******************************************************************************/

typedef struct
{
    CommunicationPacket_t packet;

    CommunicationPriority_t priority;

} QueueItem_t;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static QueueItem_t
g_txQueue[COMM_TX_QUEUE_SIZE];

static QueueItem_t
g_rxQueue[COMM_RX_QUEUE_SIZE];

static uint16_t
g_txHead = 0;

static uint16_t
g_txTail = 0;

static uint16_t
g_txCount = 0;

static uint16_t
g_rxHead = 0;

static uint16_t
g_rxTail = 0;

static uint16_t
g_rxCount = 0;
/******************************************************************************
 * Push TX Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationQueue_PushTx(
        const CommunicationPacket_t *packet,
        CommunicationPriority_t priority)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    if(g_txCount >= COMM_TX_QUEUE_SIZE)
    {
        return COMM_STATUS_QUEUE_FULL;
    }

    memcpy(&g_txQueue[g_txTail].packet,
           packet,
           sizeof(CommunicationPacket_t));

    g_txQueue[g_txTail].priority =
        priority;

    g_txTail++;

    if(g_txTail >= COMM_TX_QUEUE_SIZE)
    {
        g_txTail = 0;
    }

    g_txCount++;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Push RX Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationQueue_PushRx(
        const CommunicationPacket_t *packet)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    if(g_rxCount >= COMM_RX_QUEUE_SIZE)
    {
        return COMM_STATUS_QUEUE_FULL;
    }

    memcpy(&g_rxQueue[g_rxTail].packet,
           packet,
           sizeof(CommunicationPacket_t));

    g_rxTail++;

    if(g_rxTail >= COMM_RX_QUEUE_SIZE)
    {
        g_rxTail = 0;
    }

    g_rxCount++;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Pop TX Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationQueue_PopTx(
        CommunicationPacket_t *packet)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    if(g_txCount == 0)
    {
        return COMM_STATUS_QUEUE_EMPTY;
    }

    uint16_t best =
        g_txHead;

    uint16_t index =
        g_txHead;

    for(uint16_t i = 0; i < g_txCount; i++)
    {
        if(g_txQueue[index].priority >
           g_txQueue[best].priority)
        {
            best = index;
        }

        index++;

        if(index >= COMM_TX_QUEUE_SIZE)
        {
            index = 0;
        }
    }

    memcpy(packet,
           &g_txQueue[best].packet,
           sizeof(CommunicationPacket_t));

    g_txQueue[best] =
        g_txQueue[g_txHead];

    g_txHead++;

    if(g_txHead >= COMM_TX_QUEUE_SIZE)
    {
        g_txHead = 0;
    }

    g_txCount--;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Pop RX Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationQueue_PopRx(
        CommunicationPacket_t *packet)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    if(g_rxCount == 0)
    {
        return COMM_STATUS_QUEUE_EMPTY;
    }

    memcpy(packet,
           &g_rxQueue[g_rxHead].packet,
           sizeof(CommunicationPacket_t));

    g_rxHead++;

    if(g_rxHead >= COMM_RX_QUEUE_SIZE)
    {
        g_rxHead = 0;
    }

    g_rxCount--;

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Status
 ******************************************************************************/

bool
CommunicationQueue_IsTxEmpty(void)
{
    return (g_txCount == 0);
}

bool
CommunicationQueue_IsRxEmpty(void)
{
    return (g_rxCount == 0);
}

uint16_t
CommunicationQueue_GetTxCount(void)
{
    return g_txCount;
}

uint16_t
CommunicationQueue_GetRxCount(void)
{
    return g_rxCount;
}
/******************************************************************************
 * Status
 ******************************************************************************/

bool
CommunicationQueue_IsTxEmpty(void)
{
    return (g_txCount == 0);
}

bool
CommunicationQueue_IsRxEmpty(void)
{
    return (g_rxCount == 0);
}

uint16_t
CommunicationQueue_GetTxCount(void)
{
    return g_txCount;
}

uint16_t
CommunicationQueue_GetRxCount(void)
{
    return g_rxCount;
}


