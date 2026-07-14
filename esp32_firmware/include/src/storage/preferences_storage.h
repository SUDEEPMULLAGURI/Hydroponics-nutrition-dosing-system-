#ifndef PREFERENCES_STORAGE_H
#define PREFERENCES_STORAGE_H

/******************************************************************************
 * File        : preferences_storage.h
 * Description : ESP32 Preferences Storage Service
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "storage_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Initialization
 ******************************************************************************/

StorageStatus_t PreferencesStorage_Init(void);

StorageStatus_t PreferencesStorage_DeInit(void);

bool PreferencesStorage_IsInitialized(void);

/******************************************************************************
 * WiFi
 ******************************************************************************/

StorageStatus_t PreferencesStorage_SaveWiFi(
        const WiFiCredentials_t *credentials);

StorageStatus_t PreferencesStorage_LoadWiFi(
        WiFiCredentials_t *credentials);

/******************************************************************************
 * Firebase
 ******************************************************************************/

StorageStatus_t PreferencesStorage_SaveFirebase(
        const FirebaseConfig_t *config);

StorageStatus_t PreferencesStorage_LoadFirebase(
        FirebaseConfig_t *config);

/******************************************************************************
 * Device Information
 ******************************************************************************/

StorageStatus_t PreferencesStorage_SaveDeviceInfo(
        const DeviceInfo_t *device);

StorageStatus_t PreferencesStorage_LoadDeviceInfo(
        DeviceInfo_t *device);

/******************************************************************************
 * Cloud
 ******************************************************************************/

StorageStatus_t PreferencesStorage_SaveLastSync(
        uint32_t timestamp);

StorageStatus_t PreferencesStorage_LoadLastSync(
        uint32_t *timestamp);

/******************************************************************************
 * OTA
 ******************************************************************************/

StorageStatus_t PreferencesStorage_SaveFirmwareVersion(
        const char *version);

StorageStatus_t PreferencesStorage_LoadFirmwareVersion(
        char *version,
        uint16_t maxLength);

/******************************************************************************
 * Factory Reset
 ******************************************************************************/

StorageStatus_t PreferencesStorage_Clear(void);

#ifdef __cplusplus
}
#endif

#endif
