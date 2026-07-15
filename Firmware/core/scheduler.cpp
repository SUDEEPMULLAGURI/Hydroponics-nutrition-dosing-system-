/******************************************************************************
 * @file    scheduler.cpp
 * @brief   HydroKernel Scheduler
 ******************************************************************************/

#include "scheduler.h"

#include "../../hal/timer/hal_timer.h"

namespace kernel
{

Scheduler::Scheduler()
    :
    taskCount(0),
    cpuUsage(0.0f)
{
}

/******************************************************************************
 * Initialize
 ******************************************************************************/

Status Scheduler::Init()
{
    taskCount = 0;

    cpuUsage = 0.0f;

    for(auto &task : tasks)
    {
        task = {};
    }

    return Status::Ok;
}

/******************************************************************************
 * Reset
 ******************************************************************************/

Status Scheduler::Reset()
{
    return Init();
}

/******************************************************************************
 * Register Task
 ******************************************************************************/

Status Scheduler::RegisterTask(const TaskConfig& config)
{
    if(taskCount >= MAX_TASKS)
        return Status::OutOfMemory;

    tasks[taskCount].config = config;

    tasks[taskCount].runtime.state = TaskState::Ready;

    tasks[taskCount].runtime.lastExecutionTick =
        HAL_TIMER_Millis();

    tasks[taskCount].runtime.nextExecutionTick =
        HAL_TIMER_Millis() + config.periodMs;

    taskCount++;

    return Status::Ok;
}
/******************************************************************************
 * Execute Scheduler
 ******************************************************************************/

void Scheduler::Run()
{
    const uint32_t now = HAL_TIMER_Millis();

    for(uint8_t priority = 0;
        priority <= static_cast<uint8_t>(TaskPriority::Low);
        priority++)
    {
        for(uint8_t i = 0; i < taskCount; i++)
        {
            Task &task = tasks[i];

            if(!task.config.enabled)
                continue;

            if(task.config.priority !=
                static_cast<TaskPriority>(priority))
                continue;

            if(!TaskReady(task, now))
                continue;

            ExecuteTask(task);
        }
    }

    CalculateCpuUsage();
}
void Scheduler::ExecuteTask(Task &task)
{
    const uint32_t start = HAL_TIMER_Micros();

    task.runtime.state = TaskState::Running;

    task.config.callback();

    const uint32_t end = HAL_TIMER_Micros();

    const uint32_t runtime = end - start;

    UpdateStatistics(task, runtime);

    task.runtime.lastExecutionTick =
        HAL_TIMER_Millis();

    task.runtime.nextExecutionTick =
        task.runtime.lastExecutionTick +
        task.config.periodMs;

    task.runtime.state = TaskState::Ready;
}
bool Scheduler::TaskReady(
    const Task& task,
    uint32_t tick) const
{
    return tick >= task.runtime.nextExecutionTick;
}
void Scheduler::UpdateStatistics(
    Task& task,
    uint32_t runtime)
{
    auto& stats = task.statistics;

    stats.executionCount++;

    stats.lastExecutionTimeUs = runtime;

    stats.totalExecutionTimeUs += runtime;

    if(runtime > stats.maxExecutionTimeUs)
        stats.maxExecutionTimeUs = runtime;

    if(runtime < stats.minExecutionTimeUs)
        stats.minExecutionTimeUs = runtime;
}
void Scheduler::CalculateCpuUsage()
{
    /*
     * TODO:
     * Calculate scheduler CPU load.
     *
     * This will be implemented after the Runtime Monitor
     * is added to the kernel.
     */

    cpuUsage = 0.0f;
}

