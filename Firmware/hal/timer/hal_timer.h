/******************************************************************************
 * @file    hal_timer.h
 * @brief   Hardware Timer Abstraction Layer
 *
 * Provides platform independent timing services.
 *
 ******************************************************************************/

#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "../hal_types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Timer Object
 ******************************************************************************/

typedef struct
{
    uint32_t startTime;
    uint32_t period;
    HAL_Bool_t running;

} HAL_Timer_t;

/******************************************************************************
 * Initialization
 ******************************************************************************/

HAL_Status_t HAL_TIMER_Init(void);

void HAL_TIMER_Update(void);

void HAL_TIMER_DeInit(void);

void HAL_TIMER_Reset(void);

/******************************************************************************
 * System Time
 ******************************************************************************/

uint32_t HAL_TIMER_Millis(void);

uint64_t HAL_TIMER_Micros(void);

void HAL_TIMER_Delay(uint32_t ms);

/******************************************************************************
 * Software Timers
 ******************************************************************************/

void HAL_TIMER_Start(
    HAL_Timer_t *timer,
    uint32_t period);

void HAL_TIMER_Stop(
    HAL_Timer_t *timer);

void HAL_TIMER_Restart(
    HAL_Timer_t *timer);

HAL_Bool_t HAL_TIMER_Expired(
    HAL_Timer_t *timer);

uint32_t HAL_TIMER_Elapsed(
    HAL_Timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif
