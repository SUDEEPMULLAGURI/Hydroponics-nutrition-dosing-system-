/******************************************************************************
 * File        : system.cpp
 * Description : System Manager
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "system.h"

#include "system_fsm.h"

#include "pins.h"

#include "pump.h"
#include "pump_config.h"

#include "temperature.h"
#include "ph.h"
#include "ec.h"

#include "storage_manager.h"

#include "communication_manager.h"

#include "pump_calibration.h"

#include "dosing_manager.h"

#include "alarm_manager.h"

#include <Arduino.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static bool g_initialized = false;

/******************************************************************************
 * Initialize System
 ******************************************************************************/

bool System_Init(void)
{
    if(g_initialized)
    {
        return true;
    }

    /**********************************************************************
     * Hardware
     **********************************************************************/

    Serial.begin(115200);

    Pins_Init();

    /**********************************************************************
     * Services
     **********************************************************************/

    if(!Storage_Init())
    {
        return false;
    }

    if(!CommunicationManager_Init())
    {
        return false;
    }

    if(!AlarmManager_Init())
    {
        return false;
    }

    if(!PumpCalibration_Init())
    {
        return false;
    }

    if(!DosingManager_Init())
    {
        return false;
    }

    /**********************************************************************
     * Drivers
     **********************************************************************/

    if(!Pump_Init())
    {
        return false;
    }

    if(!Temperature_Init())
    {
        return false;
    }

    if(!PH_Init())
    {
        return false;
    }

    if(!EC_Init())
    {
        return false;
    }

    /**********************************************************************
     * System FSM
     **********************************************************************/

    if(SystemFSM_Init() != SYSTEM_STATUS_OK)
    {
        return false;
    }

    g_initialized = true;

    return true;
}
/******************************************************************************
 * System Update
 ******************************************************************************/

void System_Update(void)
{
    if(!g_initialized)
    {
        return;
    }

    SystemFSM_Update();
}
/******************************************************************************
 * Reset
 ******************************************************************************/

void System_Reset(void)
{
    SystemFSM_Reset();
}
/******************************************************************************
 * Ready
 ******************************************************************************/

bool System_IsReady(void)
{
    return SystemFSM_IsReady();
}
/******************************************************************************
 * Fault
 ******************************************************************************/

bool System_IsFault(void)
{
    return SystemFSM_IsFaulted();
}
/******************************************************************************
 * Uptime
 ******************************************************************************/

uint32_t System_GetUptime(void)
{
    return millis();
}
/******************************************************************************
 * Firmware Name
 ******************************************************************************/

const char* System_GetFirmwareName(void)
{
    return SYSTEM_FIRMWARE_NAME;
}
/******************************************************************************
 * Firmware Version
 ******************************************************************************/

const char* System_GetFirmwareVersion(void)
{
    return SYSTEM_FIRMWARE_VERSION;
}
/******************************************************************************
 * Build Date
 ******************************************************************************/

const char* System_GetBuildDate(void)
{
    return SYSTEM_BUILD_DATE;
}
/******************************************************************************
 * Build Time
 ******************************************************************************/

const char* System_GetBuildTime(void)
{
    return SYSTEM_BUILD_TIME;
}

