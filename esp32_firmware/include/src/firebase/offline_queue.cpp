/******************************************************************************
 * File        : offline_queue.cpp
 * Description : Offline Queue Implementation
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "offline_queue.h"

#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static OfflineQueueItem_t g_queue[OFFLINE_QUEUE_MAX_ITEMS];

static uint16_t g_head = 0;

static uint16_t g_tail = 0;

static uint16_t g_count = 0;

static bool g_initialized = false;

static OfflineQueueStatistics_t g_statistics;

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void OfflineQueue_Reset(void);
/******************************************************************************
 * Reset Queue
 ******************************************************************************/

static void OfflineQueue_Reset(void)
{
    memset(g_queue,
           0,
           sizeof(g_queue));

    memset(&g_statistics,
           0,
           sizeof(g_statistics));

    g_head = 0;

    g_tail = 0;

    g_count = 0;
}
/******************************************************************************
 * Initialize Queue
 ******************************************************************************/

bool OfflineQueue_Init(void)
{
    if(g_initialized)
    {
        return true;
    }

    OfflineQueue_Reset();

    g_initialized = true;

    return true;
}
/******************************************************************************
 * Update Queue
 ******************************************************************************/

bool OfflineQueue_Update(void)
{
    if(!g_initialized)
    {
        return false;
    }

    return true;
}
/******************************************************************************
 * Push Item
 ******************************************************************************/

bool OfflineQueue_Push(
        const char *path,
        const void *payload,
        uint16_t length)
{
    if(!g_initialized)
    {
        return false;
    }

    if((path == nullptr) ||
       (payload == nullptr))
    {
        return false;
    }

    if(length > OFFLINE_QUEUE_MAX_DATA_SIZE)
    {
        return false;
    }

    if(g_count >= OFFLINE_QUEUE_MAX_ITEMS)
    {
        g_statistics.dropped++;

        return false;
    }

    OfflineQueueItem_t *item =
            &g_queue[g_tail];

    memset(item,
           0,
           sizeof(OfflineQueueItem_t));

    item->timestamp = millis();

    strncpy(item->path,
            path,
            sizeof(item->path) - 1);

    memcpy(item->payload,
           payload,
           length);

    item->payloadLength = length;

    g_tail++;

    if(g_tail >= OFFLINE_QUEUE_MAX_ITEMS)
    {
        g_tail = 0;
    }

    g_count++;

    g_statistics.stored++;

    g_statistics.currentSize = g_count;

    return true;
}
/******************************************************************************
 * Pop Item
 ******************************************************************************/

bool OfflineQueue_Pop(
        OfflineQueueItem_t *item)
{
    if(!g_initialized)
    {
        return false;
    }

    if(item == nullptr)
    {
        return false;
    }

    if(g_count == 0)
    {
        return false;
    }

    memcpy(item,
           &g_queue[g_head],
           sizeof(OfflineQueueItem_t));

    memset(&g_queue[g_head],
           0,
           sizeof(OfflineQueueItem_t));

    g_head++;

    if(g_head >= OFFLINE_QUEUE_MAX_ITEMS)
    {
        g_head = 0;
    }

    g_count--;

    g_statistics.uploaded++;

    g_statistics.currentSize = g_count;

    return true;
}
/******************************************************************************
 * Peek Item
 ******************************************************************************/

bool OfflineQueue_Peek(
        OfflineQueueItem_t *item)
{
    if(!g_initialized)
    {
        return false;
    }

    if(item == nullptr)
    {
        return false;
    }

    if(g_count == 0)
    {
        return false;
    }

    memcpy(item,
           &g_queue[g_head],
           sizeof(OfflineQueueItem_t));

    return true;
}
/******************************************************************************
 * Clear Queue
 ******************************************************************************/

bool OfflineQueue_Clear(void)
{
    if(!g_initialized)
    {
        return false;
    }

    OfflineQueue_Reset();

    return true;
}
/******************************************************************************
 * Is Empty
 ******************************************************************************/

bool OfflineQueue_IsEmpty(void)
{
    return (g_count == 0);
}
/******************************************************************************
 * Is Full
 ******************************************************************************/

bool OfflineQueue_IsFull(void)
{
    return (g_count >= OFFLINE_QUEUE_MAX_ITEMS);
}
/******************************************************************************
 * Queue Size
 ******************************************************************************/

uint16_t OfflineQueue_Size(void)
{
    return g_count;
}
/******************************************************************************
 * Statistics
 ******************************************************************************/

OfflineQueueStatistics_t
OfflineQueue_GetStatistics(void)
{
    g_statistics.currentSize = g_count;

    return g_statistics;
}

