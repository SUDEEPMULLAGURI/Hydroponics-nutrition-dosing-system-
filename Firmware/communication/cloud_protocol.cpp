/******************************************************************************
 * File        : cloud_protocol.cpp
 ******************************************************************************/

#include "cloud_protocol.h"

#include "communication_manager.h"
#include "communication_commands.h"

#include <string.h>

/******************************************************************************
 * Initialize
 ******************************************************************************/

bool CloudProtocol_Init(void)
{
    return true;
}

/******************************************************************************
 * Update
 ******************************************************************************/

bool CloudProtocol_Update(void)
{
    return true;
}
/******************************************************************************
 * Send Sensor Data
 ******************************************************************************/

bool
CloudProtocol_SendSensorData(
        const SensorData_t *data)
{
    if(data == nullptr)
    {
        return false;
    }

    return
    (
    CommunicationManager_Send(
            COMM_CMD_SENSOR_DATA,
            data,
            sizeof(SensorData_t))
    ==
    COMM_STATUS_OK
    );
}
/******************************************************************************
 * Send Pump Status
 ******************************************************************************/

bool
CloudProtocol_SendPumpStatus(
        PumpId_t pump)
{
    return
    (
    CommunicationManager_Send(
            COMM_CMD_PUMP_STATUS,
            &pump,
            sizeof(PumpId_t))
    ==
    COMM_STATUS_OK
    );
}
/******************************************************************************
 * Request Time
 ******************************************************************************/

bool
CloudProtocol_RequestTime(void)
{
    return
    (
    CommunicationManager_Send(
            COMM_CMD_TIME_SYNC,
            nullptr,
            0)
    ==
    COMM_STATUS_OK
    );
}
/******************************************************************************
 * Send Sensor Status
 ******************************************************************************/

bool CloudProtocol_SendSensorStatus(void)
{
    return
    (
        CommunicationManager_Send(
            COMM_CMD_SENSOR_STATUS,
            nullptr,
            0)
        ==
        COMM_STATUS_OK
    );
}
/******************************************************************************
 * Send Pump Calibration
 ******************************************************************************/

bool CloudProtocol_SendPumpCalibration(void)
{
    return
    (
        CommunicationManager_Send(
            COMM_CMD_PUMP_CALIBRATION,
            nullptr,
            0)
        ==
        COMM_STATUS_OK
    );
}
/******************************************************************************
 * Request Configuration
 ******************************************************************************/

bool CloudProtocol_RequestConfiguration(void)
{
    return
    (
        CommunicationManager_Send(
            COMM_CMD_GET_CONFIGURATION,
            nullptr,
            0)
        ==
        COMM_STATUS_OK
    );
}
/******************************************************************************
 * Send Configuration
 ******************************************************************************/

bool CloudProtocol_SendConfiguration(void)
{
    return
    (
        CommunicationManager_Send(
            COMM_CMD_SET_CONFIGURATION,
            nullptr,
            0)
        ==
        COMM_STATUS_OK
    );
}
/******************************************************************************
 * Send Alarm
 ******************************************************************************/

bool CloudProtocol_SendAlarm(
        uint16_t alarmId)
{
    return
    (
        CommunicationManager_Send(
            COMM_CMD_ERROR,
            &alarmId,
            sizeof(alarmId))
        ==
        COMM_STATUS_OK
    );
}

