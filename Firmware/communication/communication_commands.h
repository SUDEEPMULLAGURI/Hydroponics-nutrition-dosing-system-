#ifndef COMMUNICATION_COMMANDS_H
#define COMMUNICATION_COMMANDS_H

/******************************************************************************
 * File        : communication_commands.h
 * Description : Communication Protocol Commands
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Communication Commands
 ******************************************************************************/

typedef enum
{
    /**********************************************************************
     * System Commands (0x0000 - 0x00FF)
     **********************************************************************/

    COMM_CMD_NONE                     = 0x0000,

    COMM_CMD_HEARTBEAT                = 0x0001,
    COMM_CMD_HEARTBEAT_ACK            = 0x0002,

    COMM_CMD_HANDSHAKE                = 0x0003,
    COMM_CMD_HANDSHAKE_ACK            = 0x0004,

    COMM_CMD_GET_VERSION              = 0x0005,
    COMM_CMD_VERSION_RESPONSE         = 0x0006,

    COMM_CMD_GET_DEVICE_INFO          = 0x0007,
    COMM_CMD_DEVICE_INFO_RESPONSE     = 0x0008,

    COMM_CMD_RESET                    = 0x0009,
    COMM_CMD_FACTORY_RESET            = 0x000A,

    /**********************************************************************
     * Sensor Commands (0x0100 - 0x01FF)
     **********************************************************************/

    COMM_CMD_SENSOR_DATA              = 0x0100,

    COMM_CMD_PH_DATA                  = 0x0101,
    COMM_CMD_EC_DATA                  = 0x0102,
    COMM_CMD_TEMP_DATA                = 0x0103,
    COMM_CMD_WATER_LEVEL_DATA         = 0x0104,

    COMM_CMD_SENSOR_STATUS            = 0x0105,

    /**********************************************************************
     * Pump Commands (0x0200 - 0x02FF)
     **********************************************************************/

    COMM_CMD_PUMP_START               = 0x0200,
    COMM_CMD_PUMP_STOP                = 0x0201,

    COMM_CMD_PUMP_STATUS              = 0x0202,

    COMM_CMD_PUMP_CALIBRATION         = 0x0203,

    /**********************************************************************
     * Configuration Commands (0x0300 - 0x03FF)
     **********************************************************************/

    COMM_CMD_GET_CONFIGURATION        = 0x0300,
    COMM_CMD_SET_CONFIGURATION        = 0x0301,

    COMM_CMD_SAVE_CONFIGURATION       = 0x0302,
    COMM_CMD_LOAD_CONFIGURATION       = 0x0303,

    /**********************************************************************
     * Storage Commands (0x0400 - 0x04FF)
     **********************************************************************/

    COMM_CMD_STORAGE_READ             = 0x0400,
    COMM_CMD_STORAGE_WRITE            = 0x0401,
    COMM_CMD_STORAGE_DELETE           = 0x0402,
    COMM_CMD_STORAGE_FORMAT           = 0x0403,

    /**********************************************************************
     * WiFi Commands (0x0500 - 0x05FF)
     **********************************************************************/

    COMM_CMD_WIFI_CONNECT             = 0x0500,
    COMM_CMD_WIFI_DISCONNECT          = 0x0501,

    COMM_CMD_WIFI_STATUS              = 0x0502,

    COMM_CMD_WIFI_CREDENTIALS         = 0x0503,

    COMM_CMD_WIFI_SCAN                = 0x0504,

    /**********************************************************************
     * Cloud Commands (0x0600 - 0x06FF)
     **********************************************************************/

    COMM_CMD_CLOUD_CONNECT            = 0x0600,

    COMM_CMD_CLOUD_DISCONNECT         = 0x0601,

    COMM_CMD_CLOUD_STATUS             = 0x0602,

    COMM_CMD_UPLOAD_SENSOR_DATA       = 0x0603,

    COMM_CMD_UPLOAD_CONFIGURATION     = 0x0604,

    COMM_CMD_DOWNLOAD_CONFIGURATION   = 0x0605,

    /**********************************************************************
     * Time Commands (0x0700 - 0x07FF)
     **********************************************************************/

    COMM_CMD_TIME_SYNC                = 0x0700,

    COMM_CMD_TIME_RESPONSE            = 0x0701,

    /**********************************************************************
     * OTA Commands (0x0800 - 0x08FF)
     **********************************************************************/

    COMM_CMD_OTA_BEGIN                = 0x0800,

    COMM_CMD_OTA_DATA                 = 0x0801,

    COMM_CMD_OTA_END                  = 0x0802,

    COMM_CMD_OTA_STATUS               = 0x0803,

    /**********************************************************************
     * Logging Commands (0x0900 - 0x09FF)
     **********************************************************************/

    COMM_CMD_LOG_MESSAGE              = 0x0900,

    COMM_CMD_LOG_REQUEST              = 0x0901,

    /**********************************************************************
     * Error Commands (0x0A00 - 0x0AFF)
     **********************************************************************/

    COMM_CMD_ERROR                    = 0x0A00,

    COMM_CMD_ACK                      = 0x0A01,

    COMM_CMD_NACK                     = 0x0A02

} CommunicationCommand_t;

#ifdef __cplusplus
}
#endif

#endif
