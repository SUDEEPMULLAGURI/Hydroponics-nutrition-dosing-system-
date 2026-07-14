#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

/******************************************************************************
 * File        : storage_types.h
 * Description : Storage Data Types
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
 * Storage Status
 ******************************************************************************/

typedef enum
{
    STORAGE_STATUS_OK = 0,

    STORAGE_STATUS_ERROR,

    STORAGE_STATUS_NOT_FOUND,

    STORAGE_STATUS_INVALID_PARAMETER,

    STORAGE_STATUS_NOT_INITIALIZED

} StorageStatus_t;

/******************************************************************************
 * WiFi Credentials
 ******************************************************************************/

typedef struct
{
    char ssid[32];

    char password[64];

} WiFiCredentials_t;

/******************************************************************************
 * Firebase Configuration
 ******************************************************************************/

typedef struct
{
    char apiKey[128];

    char projectId[64];

    char databaseUrl[128];

    char userEmail[64];

    char userPassword[64];

} FirebaseConfig_t;

/******************************************************************************
 * Device Information
 ******************************************************************************/

typedef struct
{
    char deviceId[32];

    char firmwareVersion[16];

    char hardwareRevision[16];

} DeviceInfo_t;

#ifdef __cplusplus
}
#endif

#endif
