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
