/******************************************************************************
 * @file    scheduler.h
 * @brief   HydroKernel Cooperative Scheduler
 *
 * Internal Scheduler
 *
 * This file is private to the HydroKernel.
 ******************************************************************************/

#ifndef HYDRO_KERNEL_SCHEDULER_H
#define HYDRO_KERNEL_SCHEDULER_H

#include "scheduler_types.h"

namespace kernel
{

class Scheduler
{
public:

    Scheduler();

    Status Init();

    Status Reset();

    Status RegisterTask(
        const TaskConfig& config);

    Status RemoveTask(uint8_t taskId);

    Status EnableTask(uint8_t taskId);

    Status DisableTask(uint8_t taskId);

    void Run();

    uint8_t TaskCount() const;

    float CpuUsage() const;

    const TaskStatistics& Statistics(
        uint8_t taskId) const;

private:

    void ExecuteTask(Task& task);

    void UpdateStatistics(
        Task& task,
        uint32_t executionTime);

    void CalculateCpuUsage();

    bool TaskReady(
        const Task& task,
        uint32_t tick) const;

private:

    Task tasks[MAX_TASKS];

    uint8_t taskCount;

    float cpuUsage;
};

}

#endif
