/******************************************************************************
 * @file        hal_watchdog.cpp
 * @brief       Hardware Abstraction Layer for Watchdog Timer.
 ******************************************************************************/

#include "hal_watchdog.h"

#include <Arduino.h>

namespace HAL::Watchdog
{

static Runtime s_runtime;

HAL::Result Init(
    const Config& config)
{
    s_runtime.initState =
        HAL::InitState::Initialized;

    s_runtime.state =
        State::Stopped;

    s_runtime.config =
        config;

    s_runtime.lastResetReason =
        ResetReason::PowerOn;

    return HAL::Result::Ok;
}

HAL::Result Start()
{
    if(s_runtime.initState !=
       HAL::InitState::Initialized)
    {
        return HAL::Result::NotInitialized;
    }

    /*
     * Arduino Core:
     * No generic watchdog API.
     *
     * MAX32630 SDK implementation
     * will enable the hardware watchdog.
     */

    s_runtime.state =
        State::Running;

    return HAL::Result::Ok;
}

HAL::Result Feed()
{
    if(s_runtime.state !=
       State::Running)
    {
        return HAL::Result::Error;
    }

    /*
     * TODO
     * Refresh hardware watchdog
     */

    return HAL::Result::Ok;
}

HAL::Result Stop()
{
    /*
     * Some MCUs cannot disable the watchdog
     * after it has started.
     *
     * Current Arduino implementation
     * simply changes the runtime state.
     */

    s_runtime.state =
        State::Stopped;

    return HAL::Result::Ok;
}

State GetState()
{
    return s_runtime.state;
}

ResetReason GetLastResetReason()
{
    return s_runtime.lastResetReason;
}

const Runtime& GetRuntime()
{
    return s_runtime;
}

}
