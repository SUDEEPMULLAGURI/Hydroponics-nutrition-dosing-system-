#ifndef DOSING_QUEUE_H
#define DOSING_QUEUE_H

/******************************************************************************
 * File        : dosing_queue.h
 * Description : Dosing Request Queue
 * Project     : Hydroponic Nutrient Dosing Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "dosing_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Queue API
 ******************************************************************************/

/**
 * @brief Initialize queue.
 */
void DosingQueue_Init(void);

/**
 * @brief Add request to queue.
 *
 * @param request Pointer to request.
 *
 * @return true if successful.
 */
bool DosingQueue_Push(const DoseRequest_t *request);

/**
 * @brief Remove oldest request.
 *
 * @param request Output request.
 *
 * @return true if successful.
 */
bool DosingQueue_Pop(DoseRequest_t *request);

/**
 * @brief Peek next request without removing it.
 *
 * @param request Output request.
 *
 * @return true if queue not empty.
 */
bool DosingQueue_Peek(DoseRequest_t *request);

/**
 * @brief Remove every queued request.
 */
void DosingQueue_Clear(void);

/******************************************************************************
 * Queue Status
 ******************************************************************************/

bool DosingQueue_IsEmpty(void);

bool DosingQueue_IsFull(void);

uint8_t DosingQueue_Count(void);

#ifdef __cplusplus
}
#endif

#endif