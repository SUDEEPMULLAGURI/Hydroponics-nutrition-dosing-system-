#ifndef OFFLINE_QUEUE_H
#define OFFLINE_QUEUE_H

/******************************************************************************
 * File        : offline_queue.h
 * Description : Offline Cloud Queue
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define OFFLINE_QUEUE_MAX_ITEMS        128U

#define OFFLINE_QUEUE_MAX_DATA_SIZE    256U

/******************************************************************************
 * Queue Item
 ******************************************************************************/

typedef struct
{
    uint32_t timestamp;

    char path[64];

    uint8_t payload[OFFLINE_QUEUE_MAX_DATA_SIZE];

    uint16_t payloadLength;

} OfflineQueueItem_t;

/******************************************************************************
 * Statistics
 ******************************************************************************/

typedef struct
{
    uint32_t stored;

    uint32_t uploaded;

    uint32_t dropped;

    uint16_t currentSize;

} OfflineQueueStatistics_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

bool OfflineQueue_Init(void);

bool OfflineQueue_Update(void);

bool OfflineQueue_Push(
        const char *path,
        const void *payload,
        uint16_t length);

bool OfflineQueue_Pop(
        OfflineQueueItem_t *item);

bool OfflineQueue_Peek(
        OfflineQueueItem_t *item);

bool OfflineQueue_Clear(void);

bool OfflineQueue_IsEmpty(void);

bool OfflineQueue_IsFull(void);

uint16_t OfflineQueue_Size(void);

OfflineQueueStatistics_t
OfflineQueue_GetStatistics(void);

#ifdef __cplusplus
}
#endif

#endif
