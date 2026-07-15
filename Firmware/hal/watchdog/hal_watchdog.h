/******************************************************************************
 * @file        hal_watchdog.h
 * @brief       Hardware Abstraction Layer for Watchdog Timer.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 *
 ******************************************************************************/

#ifndef HAL_WATCHDOG_H
#define HAL_WATCHDOG_H

#include <stdint.h>

#include "../hal_types.h"

namespace HAL::Watchdog
{

/*=============================================================================
 * Reset Reason
 *===========================================================================*/

enum class ResetReason : uint8_t
{
    Unknown,
    PowerOn,
    ExternalReset,
    SoftwareReset,
    WatchdogReset,
    BrownOut
};

/*=============================================================================
 * Runtime State
 *===========================================================================*/

enum class State : uint8_t
{
    Stopped,
    Running
};

/*=============================================================================
 * Configuration
 *===========================================================================*/

struct Config
{
    uint32_t timeoutMs;
};

/*=============================================================================
 * Runtime Information
 *===========================================================================*/

struct Runtime
{
    HAL::InitState initState;

    State state;

    Config config;

    ResetReason lastResetReason;
};

/*=============================================================================
 * Public API
 *===========================================================================*/

HAL::Result Init(
    const Config& config);

HAL::Result Start();

HAL::Result Feed();

HAL::Result Stop();

State GetState();

ResetReason GetLastResetReason();

const Runtime& GetRuntime();

}

#endif
