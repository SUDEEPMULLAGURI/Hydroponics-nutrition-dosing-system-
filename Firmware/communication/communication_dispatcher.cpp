/******************************************************************************
 * File        : communication_dispatcher.cpp
 ******************************************************************************/

#include "communication_dispatcher.h"

#include <string.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define COMM_MAX_HANDLERS      128U

/******************************************************************************
 * Handler Entry
 ******************************************************************************/

typedef struct
{
    bool used;

    CommunicationCommand_t command;

    CommunicationHandler_t handler;

} DispatcherEntry_t;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static DispatcherEntry_t
g_handlers[COMM_MAX_HANDLERS];
/******************************************************************************
 * Initialize
 ******************************************************************************/

CommunicationStatus_t
CommunicationDispatcher_Init(void)
{
    memset(g_handlers,
           0,
           sizeof(g_handlers));

    return COMM_STATUS_OK;
}
/******************************************************************************
 * Register Handler
 ******************************************************************************/

CommunicationStatus_t
CommunicationDispatcher_Register(
        CommunicationCommand_t command,
        CommunicationHandler_t handler)
{
    if(handler == nullptr)
    {
        return COMM_STATUS_INVALID_PARAMETER;
    }

    for(uint16_t i=0;
        i<COMM_MAX_HANDLERS;
        i++)
    {
        if(!g_handlers[i].used)
        {
            g_handlers[i].used = true;

            g_handlers[i].command =
                command;

            g_handlers[i].handler =
                handler;

            return COMM_STATUS_OK;
        }
    }

    return COMM_STATUS_QUEUE_FULL;
}
/******************************************************************************
 * Dispatch Packet
 ******************************************************************************/

CommunicationStatus_t
CommunicationDispatcher_Dispatch(
        const CommunicationPacket_t *packet)
{
    if(packet == nullptr)
    {
        return COMM_STATUS_INVALID_PACKET;
    }

    for(uint16_t i=0;
        i<COMM_MAX_HANDLERS;
        i++)
    {
        if(!g_handlers[i].used)
            continue;

        if(g_handlers[i].command ==
            packet->header.command)
        {
            g_handlers[i].handler(packet);

            return COMM_STATUS_OK;
        }
    }

    return COMM_STATUS_INVALID_COMMAND;
}
/******************************************************************************
 * Unregister Handler
 ******************************************************************************/

CommunicationStatus_t
CommunicationDispatcher_Unregister(
        CommunicationCommand_t command)
{
    for(uint16_t i = 0;
        i < COMM_MAX_HANDLERS;
        i++)
    {
        if(g_handlers[i].used &&
           g_handlers[i].command == command)
        {
            memset(&g_handlers[i],
                   0,
                   sizeof(DispatcherEntry_t));

            return COMM_STATUS_OK;
        }
    }

    return COMM_STATUS_INVALID_COMMAND;
}
/******************************************************************************
 * Check Registration
 ******************************************************************************/

bool
CommunicationDispatcher_IsRegistered(
        CommunicationCommand_t command)
{
    for(uint16_t i = 0;
        i < COMM_MAX_HANDLERS;
        i++)
    {
        if(g_handlers[i].used &&
           g_handlers[i].command == command)
        {
            return true;
        }
    }

    return false;
}
/******************************************************************************
 * Number of Registered Handlers
 ******************************************************************************/

uint16_t
CommunicationDispatcher_GetCount(void)
{
    uint16_t count = 0;

    for(uint16_t i = 0;
        i < COMM_MAX_HANDLERS;
        i++)
    {
        if(g_handlers[i].used)
        {
            count++;
        }
    }

    return count;
}

