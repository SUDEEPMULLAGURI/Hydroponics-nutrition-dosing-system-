/******************************************************************************
 * File        : system_fsm.cpp
 * Description : System Finite State Machine
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "system_fsm.h"

#include "pump.h"
#include "pump_calibration.h"

#include "temperature.h"
#include "ph.h"
#include "ec.h"

#include "storage_manager.h"
#include "communication_manager.h"
#include "dosing_manager.h"
#include "alarm_manager.h"

#include <string.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define SYSTEM_EVENT_QUEUE_SIZE      16

/******************************************************************************
 * Event Queue
 ******************************************************************************/

typedef struct
{
    SystemEvent_t queue[SYSTEM_EVENT_QUEUE_SIZE];

    uint8_t head;

    uint8_t tail;

    uint8_t count;

} EventQueue_t;

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static EventQueue_t g_eventQueue;

static SystemState_t g_currentState;

static SystemState_t g_previousState;

static SystemEvent_t g_lastEvent;

static bool g_initialized;

static bool g_faultActive;
/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static bool EventQueue_Push(
                SystemEvent_t event);

static bool EventQueue_Pop(
                SystemEvent_t *event);

static void SystemFSM_ChangeState(
                SystemState_t newState);

static void State_Entry(
                SystemState_t state);

static void State_Update(
                SystemState_t state);

static void State_Exit(
                SystemState_t state);
/******************************************************************************
 * Initialize
 ******************************************************************************/

SystemStatus_t SystemFSM_Init(void)
{
    memset(&g_eventQueue,
           0,
           sizeof(g_eventQueue));

    g_currentState =
        SYSTEM_STATE_POWER_ON;

    g_previousState =
        SYSTEM_STATE_POWER_ON;

    g_lastEvent =
        SYSTEM_EVENT_NONE;

    g_initialized = true;

    g_faultActive = false;

    EventQueue_Push(
        SYSTEM_EVENT_POWER_ON);

    return SYSTEM_STATUS_OK;
}
/******************************************************************************
 * Push Event
 ******************************************************************************/

static bool EventQueue_Push(
        SystemEvent_t event)
{
    if(g_eventQueue.count >=
       SYSTEM_EVENT_QUEUE_SIZE)
    {
        return false;
    }

    g_eventQueue.queue[
        g_eventQueue.tail] = event;

    g_eventQueue.tail++;

    if(g_eventQueue.tail >=
       SYSTEM_EVENT_QUEUE_SIZE)
    {
        g_eventQueue.tail = 0;
    }

    g_eventQueue.count++;

    return true;
}
/******************************************************************************
 * Pop Event
 ******************************************************************************/

static bool EventQueue_Pop(
        SystemEvent_t *event)
{
    if(g_eventQueue.count == 0)
    {
        return false;
    }

    *event =
        g_eventQueue.queue[
            g_eventQueue.head];

    g_eventQueue.head++;

    if(g_eventQueue.head >=
       SYSTEM_EVENT_QUEUE_SIZE)
    {
        g_eventQueue.head = 0;
    }

    g_eventQueue.count--;

    return true;
}
/******************************************************************************
 * Change State
 ******************************************************************************/

static void SystemFSM_ChangeState(SystemState_t newState)
{
    if(newState >= SYSTEM_STATE_COUNT)
    {
        return;
    }

    if(newState == g_currentState)
    {
        return;
    }

    /* Execute current state's exit function */

    State_Exit(g_currentState);

    /* Save previous state */

    g_previousState = g_currentState;

    /* Change state */

    g_currentState = newState;

    /* Execute new state's entry function */

    State_Entry(g_currentState);
}
/******************************************************************************
 * Update FSM
 ******************************************************************************/

SystemStatus_t SystemFSM_Update(void)
{
    if(!g_initialized)
    {
        return SYSTEM_STATUS_NOT_INITIALIZED;
    }

    SystemEvent_t event;

    if(EventQueue_Pop(&event))
    {
        g_lastEvent = event;

        switch(g_currentState)
        {
            case SYSTEM_STATE_POWER_ON:

                if(event == SYSTEM_EVENT_POWER_ON)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_INITIALIZE);
                }

                break;

            case SYSTEM_STATE_INITIALIZE:

                if(event ==
                   SYSTEM_EVENT_INITIALIZATION_COMPLETE)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_SELF_TEST);
                }

                else if(event ==
                        SYSTEM_EVENT_INITIALIZATION_FAILED)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_FAULT);
                }

                break;

            case SYSTEM_STATE_SELF_TEST:

                if(event ==
                    SYSTEM_EVENT_SELF_TEST_PASS)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_LOAD_CONFIGURATION);
                }

                else if(event ==
                        SYSTEM_EVENT_SELF_TEST_FAIL)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_FAULT);
                }

                break;
            case SYSTEM_STATE_LOAD_CONFIGURATION:

                if(event ==
                    SYSTEM_EVENT_CONFIGURATION_LOADED)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_READY);
                }

                else if(event ==
                        SYSTEM_EVENT_CONFIGURATION_ERROR)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_FAULT);
                }

                break;

            case SYSTEM_STATE_READY:

                SystemFSM_ChangeState(
                    SYSTEM_STATE_MONITOR);

                break;

            case SYSTEM_STATE_MONITOR:

                if(event ==
                    SYSTEM_EVENT_START_DOSING)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_DOSING);
                }

                else if(event ==
                        SYSTEM_EVENT_START_CALIBRATION)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_CALIBRATION);
                }

                else if(event ==
                        SYSTEM_EVENT_FAULT)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_FAULT);
                }

                break;
            case SYSTEM_STATE_DOSING:

                if(event ==
                    SYSTEM_EVENT_DOSING_COMPLETE)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_MONITOR);
                }

                else if(event ==
                        SYSTEM_EVENT_DOSING_TIMEOUT)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_FAULT);
                }

                break;
            case SYSTEM_STATE_CALIBRATION:

                if(event ==
                    SYSTEM_EVENT_CALIBRATION_COMPLETE)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_MONITOR);
                }

                else if(event ==
                        SYSTEM_EVENT_CALIBRATION_ABORT)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_MONITOR);
                }

                break;
            case SYSTEM_STATE_FAULT:

                if(event ==
                    SYSTEM_EVENT_RECOVERY)
                {
                    SystemFSM_ChangeState(
                        SYSTEM_STATE_INITIALIZE);
                }

                break;

            default:

                break;
        }
    }

    /* Execute current state's periodic update */

    State_Update(g_currentState);

    return SYSTEM_STATUS_OK;
}
/******************************************************************************
 * State Entry
 ******************************************************************************/

static void State_Entry(SystemState_t state)
{
    switch(state)
    {
        /**********************************************************************
         * POWER ON
         **********************************************************************/

        case SYSTEM_STATE_POWER_ON:
        {
            break;
        }

        /**********************************************************************
         * INITIALIZE
         **********************************************************************/

        case SYSTEM_STATE_INITIALIZE:
        {
            break;
        }

        /**********************************************************************
         * SELF TEST
         **********************************************************************/

        case SYSTEM_STATE_SELF_TEST:
        {
            break;
        }

        /**********************************************************************
         * LOAD CONFIGURATION
         **********************************************************************/

        case SYSTEM_STATE_LOAD_CONFIGURATION:
        {
            break;
        }

        /**********************************************************************
         * READY
         **********************************************************************/

        case SYSTEM_STATE_READY:
        {
            break;
        }

        /**********************************************************************
         * MONITOR
         **********************************************************************/

        case SYSTEM_STATE_MONITOR:
        {
            break;
        }

        /**********************************************************************
         * DOSING
         **********************************************************************/

        case SYSTEM_STATE_DOSING:
        {
            DosingManager_Start();

            break;
        }

        /**********************************************************************
         * CALIBRATION
         **********************************************************************/

        case SYSTEM_STATE_CALIBRATION:
        {
            break;
        }

        /**********************************************************************
         * FAULT
         **********************************************************************/

        case SYSTEM_STATE_FAULT:
        {
            g_faultActive = true;

            Pump_StopAll();

            AlarmManager_Raise(ALARM_SYSTEM_FAULT);

            CommunicationManager_SendFault();

            break;
        }

        default:
            break;
    }
}
/******************************************************************************
 * State Update
 ******************************************************************************/

static void State_Update(SystemState_t state)
{
    switch(state)
    {
        /**********************************************************************
         * INITIALIZE
         **********************************************************************/

        case SYSTEM_STATE_INITIALIZE:
        {
            bool ok = true;

            ok &= Pump_Init();

            ok &= Temperature_Init();

            ok &= PH_Init();

            ok &= EC_Init();

            ok &= Storage_Init();

            ok &= CommunicationManager_Init();

            ok &= AlarmManager_Init();

            ok &= DosingManager_Init();

            if(ok)
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_INITIALIZATION_COMPLETE);
            }
            else
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_INITIALIZATION_FAILED);
            }

            break;
        }
                case SYSTEM_STATE_SELF_TEST:
        {
            bool passed = true;

            passed &= Temperature_IsValid();

            passed &= PH_IsValid();

            passed &= EC_IsValid();

            if(passed)
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_SELF_TEST_PASS);
            }
            else
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_SELF_TEST_FAIL);
            }

            break;
        }
                case SYSTEM_STATE_LOAD_CONFIGURATION:
        {
            bool loaded = true;

            loaded &= PumpCalibration_Load();

            loaded &= DosingManager_LoadConfiguration();

            loaded &= AlarmManager_LoadConfiguration();

            if(loaded)
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_CONFIGURATION_LOADED);
            }
            else
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_CONFIGURATION_ERROR);
            }

            break;
        }
                case SYSTEM_STATE_READY:
        {
            SystemFSM_PostEvent(
                SYSTEM_EVENT_MONITOR);

            break;
        }
        
                case SYSTEM_STATE_MONITOR:
        {
            Temperature_Update();

            PH_Update();

            EC_Update();

            AlarmManager_Update();

            CommunicationManager_Update();

            if(DosingManager_NeedsDosing())
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_START_DOSING);
            }

            break;
        }
                case SYSTEM_STATE_DOSING:
        {
            DosingManager_Update();

            if(DosingManager_IsComplete())
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_DOSING_COMPLETE);
            }

            break;
        }
                case SYSTEM_STATE_CALIBRATION:
        {
            PumpCalibration_Update();

            if(PumpCalibration_IsComplete())
            {
                SystemFSM_PostEvent(
                    SYSTEM_EVENT_CALIBRATION_COMPLETE);
            }

            break;
        }
        case SYSTEM_STATE_FAULT:
        {
            AlarmManager_Update();

            CommunicationManager_Update();

            break;
        }

        default:
            break;
    }
}
/******************************************************************************
 * State Exit
 ******************************************************************************/

static void State_Exit(SystemState_t state)
{
    switch(state)
    {
        /**********************************************************************
         * POWER ON
         **********************************************************************/

        case SYSTEM_STATE_POWER_ON:
        {
            break;
        }

        /**********************************************************************
         * INITIALIZE
         **********************************************************************/

        case SYSTEM_STATE_INITIALIZE:
        {
            break;
        }

        /**********************************************************************
         * SELF TEST
         **********************************************************************/

        case SYSTEM_STATE_SELF_TEST:
        {
            break;
        }

        /**********************************************************************
         * LOAD CONFIGURATION
         **********************************************************************/

        case SYSTEM_STATE_LOAD_CONFIGURATION:
        {
            break;
        }

        /**********************************************************************
         * READY
         **********************************************************************/

        case SYSTEM_STATE_READY:
        {
            break;
        }

        /**********************************************************************
         * MONITOR
         **********************************************************************/

        case SYSTEM_STATE_MONITOR:
        {
            break;
        }

        /**********************************************************************
         * DOSING
         **********************************************************************/

        case SYSTEM_STATE_DOSING:
        {
            DosingManager_Stop();

            break;
        }

        /**********************************************************************
         * CALIBRATION
         **********************************************************************/

        case SYSTEM_STATE_CALIBRATION:
        {
            PumpCalibration_Stop();

            break;
        }

        /**********************************************************************
         * FAULT
         **********************************************************************/

        case SYSTEM_STATE_FAULT:
        {
            g_faultActive = false;

            AlarmManager_Clear(ALARM_SYSTEM_FAULT);

            break;
        }

        default:
        {
            break;
        }
    }
}
/******************************************************************************
 * Post Event
 ******************************************************************************/

SystemStatus_t SystemFSM_PostEvent(
                    SystemEvent_t event)
{
    if(!g_initialized)
    {
        return SYSTEM_STATUS_NOT_INITIALIZED;
    }

    if(!EventQueue_Push(event))
    {
        return SYSTEM_STATUS_BUSY;
    }

    return SYSTEM_STATUS_OK;
}
/******************************************************************************
 * Get Current State
 ******************************************************************************/

SystemState_t SystemFSM_GetState(void)
{
    return g_currentState;
}
/******************************************************************************
 * Get Previous State
 ******************************************************************************/

SystemState_t SystemFSM_GetPreviousState(void)
{
    return g_previousState;
}
/******************************************************************************
 * Get Last Event
 ******************************************************************************/

SystemEvent_t SystemFSM_GetLastEvent(void)
{
    return g_lastEvent;
}
/******************************************************************************
 * System Ready
 ******************************************************************************/

bool SystemFSM_IsReady(void)
{
    return (g_currentState ==
            SYSTEM_STATE_MONITOR);
}
/******************************************************************************
 * Fault Status
 ******************************************************************************/

bool SystemFSM_IsFaulted(void)
{
    return g_faultActive;
}
/******************************************************************************
 * Force State
 ******************************************************************************/

SystemStatus_t SystemFSM_SetState(
                    SystemState_t state)
{
    if(state >= SYSTEM_STATE_COUNT)
    {
        return SYSTEM_STATUS_INVALID_STATE;
    }

    SystemFSM_ChangeState(state);

    return SYSTEM_STATUS_OK;
}
/******************************************************************************
 * Reset FSM
 ******************************************************************************/

SystemStatus_t SystemFSM_Reset(void)
{
    memset(&g_eventQueue,
           0,
           sizeof(g_eventQueue));

    g_currentState = SYSTEM_STATE_POWER_ON;

    g_previousState = SYSTEM_STATE_POWER_ON;

    g_lastEvent = SYSTEM_EVENT_NONE;

    g_faultActive = false;

    EventQueue_Push(
        SYSTEM_EVENT_POWER_ON);

    return SYSTEM_STATUS_OK;
}
        
