/******************************************************************************
 * @file    scheduler_types.h
 * @brief   HydroKernel Scheduler Types
 *
 * Internal data structures used by the Scheduler.
 *
 ******************************************************************************/

#ifndef HYDRO_SCHEDULER_TYPES_H
#define HYDRO_SCHEDULER_TYPES_H

#include "../kernel_types.h"

namespace kernel
{
/******************************************************************************
 * Task Identifiers
 ******************************************************************************/

enum class TaskId : uint8_t
{
    SensorManager = 0,

    PumpManager,

    CommunicationManager,

    StorageManager,

    AlarmManager,

    SafetyManager,

    DiagnosticsManager,

    DosingManager,

    Fsm,

    Logger,

    Idle,

    Count
};

/******************************************************************************
 * Task Function
 ******************************************************************************/

using TaskCallback = void(*)();

/******************************************************************************
 * Task Priority
 ******************************************************************************/

enum class TaskPriority : uint8_t
{
    Critical = 0,
    High,
    Normal,
    Low
};

/******************************************************************************
 * Task State
 ******************************************************************************/

enum class TaskState : uint8_t
{
    Ready = 0,
    Running,
    Waiting,
    Suspended,
    Disabled,
    Error
};

/******************************************************************************
 * Runtime Statistics
 ******************************************************************************/

struct TaskStatistics
{
    uint32_t executionCount = 0;

    uint32_t maxExecutionTimeUs = 0;

    uint32_t minExecutionTimeUs = UINT32_MAX;

    uint32_t totalExecutionTimeUs = 0;

    uint32_t deadlineMisses = 0;

    uint32_t lastExecutionTimeUs = 0;
};

/******************************************************************************
 * Task Configuration
 ******************************************************************************/

struct TaskConfig
{
    TaskCallback callback = nullptr;

    uint32_t periodMs = 0;

    TaskPriority priority = TaskPriority::Normal;

    bool enabled = true;
};

/******************************************************************************
 * Runtime Information
 ******************************************************************************/

struct TaskRuntime
{
    uint32_t lastExecutionTick = 0;

    uint32_t nextExecutionTick = 0;

    TaskState state = TaskState::Ready;
};

/******************************************************************************
 * Complete Task Object
 ******************************************************************************/

struct Task
{
    TaskConfig config;

    TaskRuntime runtime;

    TaskStatistics statistics;
};

}

#endif
