/******************************************************************************
 * @file    kernel_types.h
 * @brief   HydroKernel Common Types
 *
 * ----------------------------------------------------------------------------
 * Hydroponics Nutrition Dosing Controller
 * ----------------------------------------------------------------------------
 *
 * This file contains all common kernel data types used throughout the firmware.
 *
 * IMPORTANT
 * ---------
 * This file must NEVER include Arduino headers or MCU-specific headers.
 * It must remain completely platform independent.
 *
 ******************************************************************************/

#ifndef HYDRO_KERNEL_TYPES_H
#define HYDRO_KERNEL_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Kernel Version
 ******************************************************************************/

#define KERNEL_VERSION_MAJOR    1
#define KERNEL_VERSION_MINOR    0
#define KERNEL_VERSION_PATCH    0

/******************************************************************************
 * Kernel Status
 ******************************************************************************/

typedef enum
{
    KERNEL_OK = 0,

    KERNEL_ERROR,

    KERNEL_BUSY,

    KERNEL_TIMEOUT,

    KERNEL_QUEUE_FULL,

    KERNEL_INVALID_PARAMETER,

    KERNEL_NOT_INITIALIZED,

    KERNEL_OUT_OF_MEMORY

} KernelStatus_t;

/******************************************************************************
 * Task Priority
 ******************************************************************************/

typedef enum
{
    KERNEL_PRIORITY_CRITICAL = 0,

    KERNEL_PRIORITY_HIGH,

    KERNEL_PRIORITY_NORMAL,

    KERNEL_PRIORITY_LOW

} KernelPriority_t;

/******************************************************************************
 * Task State
 ******************************************************************************/

typedef enum
{
    KERNEL_TASK_UNUSED = 0,

    KERNEL_TASK_READY,

    KERNEL_TASK_RUNNING,

    KERNEL_TASK_WAITING,

    KERNEL_TASK_SUSPENDED,

    KERNEL_TASK_DISABLED,

    KERNEL_TASK_ERROR

} KernelTaskState_t;

/******************************************************************************
 * Timer Type
 ******************************************************************************/

typedef enum
{
    KERNEL_TIMER_ONE_SHOT = 0,

    KERNEL_TIMER_PERIODIC

} KernelTimerType_t;

/******************************************************************************
 * Event Priority
 ******************************************************************************/

typedef enum
{
    KERNEL_EVENT_CRITICAL = 0,

    KERNEL_EVENT_HIGH,

    KERNEL_EVENT_NORMAL,

    KERNEL_EVENT_LOW

} KernelEventPriority_t;

/******************************************************************************
 * Generic Boolean
 ******************************************************************************/

typedef enum
{
    KERNEL_FALSE = 0,

    KERNEL_TRUE

} KernelBool_t;

/******************************************************************************
 * Task Callback
 ******************************************************************************/

typedef void (*KernelTaskCallback_t)(void);

/******************************************************************************
 * Event Callback
 ******************************************************************************/

typedef void (*KernelEventCallback_t)(void *argument);

/******************************************************************************
 * Kernel Tick
 ******************************************************************************/

typedef uint32_t KernelTick_t;

/******************************************************************************
 * Kernel Time
 ******************************************************************************/

typedef uint64_t KernelTimeUs_t;

#ifdef __cplusplus
}
#endif

#endif /* HYDRO_KERNEL_TYPES_H */
