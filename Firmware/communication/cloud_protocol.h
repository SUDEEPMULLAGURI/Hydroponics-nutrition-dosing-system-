#ifndef CLOUD_PROTOCOL_H
#define CLOUD_PROTOCOL_H

/******************************************************************************
 * File        : cloud_protocol.h
 * Description : High Level Communication API
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "sensor_types.h"
#include "pump_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Initialization
 ******************************************************************************/

bool CloudProtocol_Init(void);

bool CloudProtocol_Update(void);

/******************************************************************************
 * Sensor Data
 ******************************************************************************/

bool CloudProtocol_SendSensorData(
        const SensorData_t *data);

bool CloudProtocol_SendSensorStatus(void);

/******************************************************************************
 * Pump
 ******************************************************************************/

bool CloudProtocol_SendPumpStatus(
        PumpId_t pump);

bool CloudProtocol_SendPumpCalibration(void);

/******************************************************************************
 * Configuration
 ******************************************************************************/

bool CloudProtocol_RequestConfiguration(void);

bool CloudProtocol_SendConfiguration(void);

/******************************************************************************
 * Time
 ******************************************************************************/

bool CloudProtocol_RequestTime(void);

/******************************************************************************
 * Alarms
 ******************************************************************************/

bool CloudProtocol_SendAlarm(
        uint16_t alarmId);

/******************************************************************************
 * OTA
 ******************************************************************************/

bool CloudProtocol_RequestOTA(void);

#ifdef __cplusplus
}
#endif

#endif
