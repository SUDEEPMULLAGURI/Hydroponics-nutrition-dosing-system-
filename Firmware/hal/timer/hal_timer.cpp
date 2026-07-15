/******************************************************************************
 * @file    hal_timer.cpp
 ******************************************************************************/

#include "hal_timer.h"

#include <Arduino.h>

/******************************************************************************
 * Initialization
 ******************************************************************************/

HAL_Status_t HAL_TIMER_Init(void)
{
    return HAL_OK;
}

void HAL_TIMER_Update(void)
{
}

void HAL_TIMER_DeInit(void)
{
}

void HAL_TIMER_Reset(void)
{
}

/******************************************************************************
 * System Time
 ******************************************************************************/

uint32_t HAL_TIMER_Millis(void)
{
    return millis();
}

uint64_t HAL_TIMER_Micros(void)
{
    return micros();
}

void HAL_TIMER_Delay(uint32_t ms)
{
    delay(ms);
}

/******************************************************************************
 * Software Timer Functions
 ******************************************************************************/

void HAL_TIMER_Start(
    HAL_Timer_t *timer,
    uint32_t period)
{
    if(timer == nullptr)
        return;

    timer->startTime = millis();
    timer->period = period;
    timer->running = HAL_TRUE;
}

void HAL_TIMER_Stop(
    HAL_Timer_t *timer)
{
    if(timer == nullptr)
        return;

    timer->running = HAL_FALSE;
}

void HAL_TIMER_Restart(
    HAL_Timer_t *timer)
{
    if(timer == nullptr)
        return;

    timer->startTime = millis();
    timer->running = HAL_TRUE;
}

HAL_Bool_t HAL_TIMER_Expired(
    HAL_Timer_t *timer)
{
    if(timer == nullptr)
        return HAL_FALSE;

    if(timer->running == HAL_FALSE)
        return HAL_FALSE;

    if((millis() - timer->startTime) >= timer->period)
    {
        timer->running = HAL_FALSE;
        return HAL_TRUE;
    }

    return HAL_FALSE;
}

uint32_t HAL_TIMER_Elapsed(
    HAL_Timer_t *timer)
{
    if(timer == nullptr)
        return 0;

    return millis() - timer->startTime;
}
