/******************************************************************************
 * File        : communication_manager.cpp
 * Description : ESP32 Communication Manager
 ******************************************************************************/

#include "communication_manager.h"

#include "uart_driver.h"
#include "communication_protocol.h"
#include "communication_dispatcher.h"

#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define COMM_HEARTBEAT_INTERVAL_MS     1000U

#define COMM_TIMEOUT_MS                5000U
/******************************************************************************
 * TX Queue
 ******************************************************************************/

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#define COMM_TX_QUEUE_LENGTH      16

typedef struct
{
    CommunicationCommand_t command;

    uint8_t payload[COMM_MAX_PAYLOAD_SIZE];

    uint16_t payloadLength;

} CommunicationTxItem_t;

static QueueHandle_t g_txQueue = nullptr;
/******************************************************************************
 * Private Variables
 ******************************************************************************/

static CommunicationManagerState_t
g_state =
COMM_MANAGER_OFFLINE;

static uint32_t
g_lastHeartbeat = 0;

static uint32_t
g_lastPacketTime = 0;

static CommunicationPacket_t
g_packet;
/******************************************************************************
 * Initialize
 ******************************************************************************/

bool CommunicationManager_Init(void)
{
    if(UARTDriver_Init() != UART_STATUS_OK)
    {
        return false;
    }

    if(CommunicationProtocol_Init() != COMM_STATUS_OK)
    {
        return false;
    }

    CommunicationDispatcher_Init();

    memset(&g_packet,
           0,
           sizeof(g_packet));

    g_lastHeartbeat =
        millis();

    g_lastPacketTime =
        millis();

    g_state =
        COMM_MANAGER_WAIT_HANDSHAKE;
    g_txQueue =
    xQueueCreate(
            COMM_TX_QUEUE_LENGTH,
            sizeof(CommunicationTxItem_t));

    if(g_txQueue == nullptr)
    {
    return false;
    }

    return true;
}
/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void CommunicationManager_ProcessPacket(
        const CommunicationPacket_t *packet);

static void CommunicationManager_SendHeartbeat(void);

static void CommunicationManager_CheckTimeout(void);
/******************************************************************************
 * Update Communication Manager
 ******************************************************************************/

bool CommunicationManager_Update(void)
{
    CommunicationStatus_t status;

    uint8_t rxBuffer[COMM_MAX_PACKET_SIZE];

    uint16_t length = 0;
CommunicationTxItem_t txItem;

if(xQueueReceive(
        g_txQueue,
        &txItem,
        0) == pdTRUE)
{
    uint8_t buffer[COMM_MAX_PACKET_SIZE];

    uint16_t length = 0;

    CommunicationPacket_t packet;

    if(CommunicationProtocol_CreatePacket(
            &packet,
            txItem.command,
            txItem.payload,
            txItem.payloadLength,
            COMM_FLAG_ACK_REQUIRED)
        ==
        COMM_STATUS_OK)
    {
        if(CommunicationProtocol_Encode(
                &packet,
                buffer,
                &length)
            ==
            COMM_STATUS_OK)
        {
            UARTDriver_Send(
                    buffer,
                    length);
        }
    }
}
    /*----------------------------------------------------------
        Receive UART Data
    ----------------------------------------------------------*/

    if(UARTDriver_Available() > 0)
    {
        if(UARTDriver_Receive(rxBuffer,
                              &length) == UART_STATUS_OK)
        {
            status =
                CommunicationProtocol_Decode(
                        rxBuffer,
                        length,
                        &g_packet);

            if(status == COMM_STATUS_OK)
            {
                status =
                    CommunicationProtocol_Verify(
                            &g_packet);

                if(status == COMM_STATUS_OK)
                {
                    g_lastPacketTime =
                        millis();

                    CommunicationManager_ProcessPacket(
                            &g_packet);
                }
            }
        }
    }

    /*----------------------------------------------------------
        Send Heartbeat
    ----------------------------------------------------------*/

    if((millis() - g_lastHeartbeat) >=
        COMM_HEARTBEAT_INTERVAL_MS)
    {
        CommunicationManager_SendHeartbeat();

        g_lastHeartbeat = millis();
    }

    /*----------------------------------------------------------
        Connection Timeout
    ----------------------------------------------------------*/

    CommunicationManager_CheckTimeout();

    return true;
}
/******************************************************************************
 * Process Received Packet
 ******************************************************************************/

static void
CommunicationManager_ProcessPacket(
        const CommunicationPacket_t *packet)
{
    if(packet == nullptr)
    {
        return;
    }

    switch(packet->header.command)
    {
        /******************************************************
         * Handshake
         ******************************************************/

        case COMM_CMD_HANDSHAKE:

            g_state =
                COMM_MANAGER_CONNECTED;

            CommunicationManager_SendAck(
                    packet->header.sequenceNumber);

            break;

        /******************************************************
         * Heartbeat
         ******************************************************/

        case COMM_CMD_HEARTBEAT:

            CommunicationManager_SendAck(
                    packet->header.sequenceNumber);

            break;

        /******************************************************
         * Everything Else
         ******************************************************/

        default:

            CommunicationDispatcher_Dispatch(packet);

            CommunicationManager_SendAck(
                    packet->header.sequenceNumber);

            break;
    }
}
/******************************************************************************
 * Heartbeat
 ******************************************************************************/

static void
CommunicationManager_SendHeartbeat(void)
{
    CommunicationManager_Send(
            COMM_CMD_HEARTBEAT,
            nullptr,
            0);
}
/******************************************************************************
 * Timeout Detection
 ******************************************************************************/

static void
CommunicationManager_CheckTimeout(void)
{
    if((millis() - g_lastPacketTime) >=
        COMM_TIMEOUT_MS)
    {
        g_state =
            COMM_MANAGER_WAIT_HANDSHAKE;
    }
}
/******************************************************************************
 * Queue Packet
 ******************************************************************************/

bool CommunicationManager_Send(
        CommunicationCommand_t command,
        const void *payload,
        uint16_t payloadLength)
{
    if(g_txQueue == nullptr)
    {
        return false;
    }

    CommunicationTxItem_t item;

    memset(&item,
           0,
           sizeof(item));

    item.command = command;

    item.payloadLength = payloadLength;

    if((payload != nullptr) &&
       (payloadLength > 0))
    {
        memcpy(item.payload,
               payload,
               payloadLength);
    }

    if(xQueueSend(
            g_txQueue,
            &item,
            0) != pdTRUE)
    {
        return false;
    }

    return true;
}
/******************************************************************************
 * ACK
 ******************************************************************************/

bool CommunicationManager_SendAck(
        uint16_t sequence)
{
    return
    CommunicationManager_Send(
            COMM_CMD_ACK,
            &sequence,
            sizeof(sequence));
}
/******************************************************************************
 * NACK
 ******************************************************************************/

bool CommunicationManager_SendNack(
        uint16_t sequence)
{
    return
    CommunicationManager_Send(
            COMM_CMD_NACK,
            &sequence,
            sizeof(sequence));
}
/******************************************************************************
 * Connection
 ******************************************************************************/

bool CommunicationManager_IsConnected(void)
{
    return
        (g_state ==
         COMM_MANAGER_CONNECTED);
}

CommunicationManagerState_t
CommunicationManager_GetState(void)
{
    return g_state;
}


