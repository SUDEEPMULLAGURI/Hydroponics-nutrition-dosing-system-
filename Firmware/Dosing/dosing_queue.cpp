/******************************************************************************
 * File        : dosing_queue.cpp
 * Description : Dosing Queue
 * Project     : Hydroponic Nutrient Dosing Controller
 ******************************************************************************/

#include "dosing_queue.h"

#include <string.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static DoseRequest_t queue[DOSING_MAX_QUEUE_SIZE];

static uint8_t head = 0;

static uint8_t tail = 0;

static uint8_t count = 0;

/******************************************************************************
 * Initialize
 ******************************************************************************/

void DosingQueue_Init(void)
{
    memset(queue, 0, sizeof(queue));

    head = 0;
    tail = 0;
    count = 0;
}

/******************************************************************************
 * Push
 ******************************************************************************/

bool DosingQueue_Push(const DoseRequest_t *request)
{
    if(request == nullptr)
        return false;

    if(count >= DOSING_MAX_QUEUE_SIZE)
        return false;

    queue[tail] = *request;

    tail++;

    if(tail >= DOSING_MAX_QUEUE_SIZE)
    {
        tail = 0;
    }

    count++;

    return true;
}

/******************************************************************************
 * Pop
 ******************************************************************************/

bool DosingQueue_Pop(DoseRequest_t *request)
{
    if(request == nullptr)
        return false;

    if(count == 0)
        return false;

    *request = queue[head];

    head++;

    if(head >= DOSING_MAX_QUEUE_SIZE)
    {
        head = 0;
    }

    count--;

    return true;
}

/******************************************************************************
 * Peek
 ******************************************************************************/

bool DosingQueue_Peek(DoseRequest_t *request)
{
    if(request == nullptr)
        return false;

    if(count == 0)
        return false;

    *request = queue[head];

    return true;
}

/******************************************************************************
 * Clear
 ******************************************************************************/

void DosingQueue_Clear(void)
{
    head = 0;
    tail = 0;
    count = 0;
}

/******************************************************************************
 * Queue Status
 ******************************************************************************/

bool DosingQueue_IsEmpty(void)
{
    return (count == 0);
}

bool DosingQueue_IsFull(void)
{
    return (count >= DOSING_MAX_QUEUE_SIZE);
}

uint8_t DosingQueue_Count(void)
{
    return count;
}
