/******************************************************************************
 * File        : communication_manager.cpp
 * Description : Communication Manager
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "communication_manager.h"

#include "communication_protocol.h"
#include "communication_transport.h"

#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define COMM_HEARTBEAT_INTERVAL_MS     1000U
#define COMM_TIMEOUT_MS                5000U

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static CommunicationState_t
g_state =
COMM_STATE_OFFLINE;

static uint32_t
g_lastHeartbeat = 0;

static uint32_t
g_lastReceiveTime = 0;

static uint32_t
g_txPackets = 0;

static uint32_t
g_rxPackets = 0;

static uint32_t
g_crcErrors = 0;

static CommunicationPacket_t
g_packet;

static uint8_t
g_rxBuffer[COMM_MAX_PACKET_SIZE];

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void CommunicationManager_SendHeartbeat(void);

static void CommunicationManager_ProcessPacket(
        const CommunicationPacket_t *packet);

static void CommunicationManager_CheckTimeout(void);
/******************************************************************************
 * Update Communication Manager
 ******************************************************************************/

CommunicationStatus_t
CommunicationManager_Update(void)
{
    uint16_t length = 0;

    CommunicationStatus_t status;

    /*----------------------------------------------------------
        Check Transport
    ----------------------------------------------------------*/

    if (!CommunicationTransport_IsReady())
    {
        g_state = COMM_STATE_OFFLINE;

        return COMM_STATUS_TRANSPORT_ERROR;
    }

    /*----------------------------------------------------------
        Receive Packet
    ----------------------------------------------------------*/

    if (CommunicationTransport_Available() > 0)
    {
        status =
            CommunicationTransport_Receive(
                g_rxBuffer,
                &length);

        if (status == COMM_STATUS_OK)
        {
            status =
                CommunicationProtocol_Decode(
                    g_rxBuffer,
                    length,
                    &g_packet);

            if (status == COMM_STATUS_OK)
            {
                status =
                    CommunicationProtocol_Verify(
                        &g_packet);

                if (status == COMM_STATUS_OK)
                {
                    g_rxPackets++;

                    g_lastReceiveTime =
                        millis();

                    CommunicationManager_ProcessPacket(
                        &g_packet);
                }
                else
                {
                    g_crcErrors++;
                }
            }
        }
    }

    /*----------------------------------------------------------
        Heartbeat
    ----------------------------------------------------------*/

    if ((millis() - g_lastHeartbeat) >=
        COMM_HEARTBEAT_INTERVAL_MS)
    {
        CommunicationManager_SendHeartbeat();

        g_lastHeartbeat =
            millis();
    }

    /*----------------------------------------------------------
        Timeout Detection
    ----------------------------------------------------------*/

    CommunicationManager_CheckTimeout();

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Send Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationManager_Send(
        CommunicationCommand_t command,
        const void *payload,
        uint16_t length)
{
    CommunicationStatus_t status;

    uint8_t txBuffer[COMM_MAX_PACKET_SIZE];

    uint16_t txLength = 0;

    /* Build Packet */

    status =
        CommunicationProtocol_CreatePacket(
                &g_packet,
                command,
                payload,
                length,
                COMM_FLAG_ACK_REQUIRED);

    if(status != COMM_STATUS_OK)
    {
        return status;
    }

    /* Encode Packet */

    status =
        CommunicationProtocol_Encode(
                &g_packet,
                txBuffer,
                &txLength);

    if(status != COMM_STATUS_OK)
    {
        return status;
    }

    /* Send */

    status =
        CommunicationTransport_Send(
                txBuffer,
                txLength);

    if(status != COMM_STATUS_OK)
    {
        return status;
    }

    g_txPackets++;

    return COMM_STATUS_OK;
}

