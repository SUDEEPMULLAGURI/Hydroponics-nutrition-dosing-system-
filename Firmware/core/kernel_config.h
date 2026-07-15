/******************************************************************************
 * @file    kernel_config.h
 * @brief   HydroKernel Configuration
 *
 * Project:
 *      Commercial Hydroponics Controller
 *
 * Description:
 *      Global compile-time configuration for the HydroKernel.
 *
 ******************************************************************************/

#ifndef HYDRO_KERNEL_CONFIG_H
#define HYDRO_KERNEL_CONFIG_H

#include <stdint.h>

namespace kernel
{

/******************************************************************************
 * Version
 ******************************************************************************/

constexpr uint8_t VERSION_MAJOR = 1;
constexpr uint8_t VERSION_MINOR = 0;
constexpr uint8_t VERSION_PATCH = 0;

/******************************************************************************
 * Scheduler Configuration
 ******************************************************************************/

constexpr uint8_t MAX_TASKS = 32;

constexpr uint8_t MAX_EVENTS = 64;

constexpr uint8_t MAX_TIMERS = 32;

/******************************************************************************
 * Tick Rate
 ******************************************************************************/

constexpr uint32_t TICK_RATE_HZ = 1000;

/******************************************************************************
 * Runtime Statistics
 ******************************************************************************/

constexpr bool ENABLE_RUNTIME_STATS = true;

constexpr bool ENABLE_CPU_USAGE = true;

constexpr bool ENABLE_TASK_MONITOR = true;

/******************************************************************************
 * Watchdog
 ******************************************************************************/

constexpr bool ENABLE_WATCHDOG = true;

/******************************************************************************
 * Event Queue
 ******************************************************************************/

constexpr bool ENABLE_EVENT_QUEUE = true;

/******************************************************************************
 * Logger
 ******************************************************************************/

constexpr bool ENABLE_LOGGER = true;

/******************************************************************************
 * Idle Hook
 ******************************************************************************/

constexpr bool ENABLE_IDLE_HOOK = true;

/******************************************************************************
 * Debug
 ******************************************************************************/

constexpr bool DEBUG_MODE = true;

}

#endif
