#ifndef SYSTEM_H
#define SYSTEM_H

/******************************************************************************
 * File        : system.h
 * Description : System Manager
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Firmware Information
 ******************************************************************************/

#define SYSTEM_FIRMWARE_NAME        "Smart Hydroponics Controller"

#define SYSTEM_FIRMWARE_VERSION     "1.0.0"

#define SYSTEM_BUILD_DATE           __DATE__

#define SYSTEM_BUILD_TIME           __TIME__

/******************************************************************************
 * System Status
 ******************************************************************************/

typedef enum
{
    SYSTEM_OK = 0,

    SYSTEM_ERROR,

    SYSTEM_NOT_INITIALIZED,

    SYSTEM_INITIALIZING,

    SYSTEM_RUNNING,

    SYSTEM_FAULT

} SystemStatus_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/* Initialize entire system */

bool System_Init(void);

/* Periodic update */

void System_Update(void);

/* Reset */

void System_Reset(void);

/* System Ready */

bool System_IsReady(void);

/* System Fault */

bool System_IsFault(void);

/* Get uptime */

uint32_t System_GetUptime(void);

/* Firmware Information */

const char* System_GetFirmwareName(void);

const char* System_GetFirmwareVersion(void);

const char* System_GetBuildDate(void);

const char* System_GetBuildTime(void);

#ifdef __cplusplus
}
#endif

#endif
