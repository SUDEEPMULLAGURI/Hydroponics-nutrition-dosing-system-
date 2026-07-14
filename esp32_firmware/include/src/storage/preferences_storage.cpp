/******************************************************************************
 * File        : preferences_storage.cpp
 * Description : ESP32 Preferences Storage Service
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "preferences_storage.h"
#include "storage_keys.h"

#include <Preferences.h>
#include <string.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static Preferences g_preferences;

static bool g_initialized = false;

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static bool PreferencesStorage_CheckInit(void);
/******************************************************************************
 * Initialize Storage
 ******************************************************************************/

StorageStatus_t PreferencesStorage_Init(void)
{
    if(g_initialized)
    {
        return STORAGE_STATUS_OK;
    }

    if(!g_preferences.begin(STORAGE_NAMESPACE, false))
    {
        return STORAGE_STATUS_ERROR;
    }

    g_initialized = true;

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Deinitialize Storage
 ******************************************************************************/

StorageStatus_t PreferencesStorage_DeInit(void)
{
    if(!g_initialized)
    {
        return STORAGE_STATUS_OK;
    }

    g_preferences.end();

    g_initialized = false;

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Initialization Status
 ******************************************************************************/

bool PreferencesStorage_IsInitialized(void)
{
    return g_initialized;
}
/******************************************************************************
 * Internal Check
 ******************************************************************************/

static bool PreferencesStorage_CheckInit(void)
{
    return g_initialized;
}
/******************************************************************************
 * Save WiFi Credentials
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_SaveWiFi(
        const WiFiCredentials_t *credentials)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(credentials == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    g_preferences.putString(
            KEY_WIFI_SSID,
            credentials->ssid);

    g_preferences.putString(
            KEY_WIFI_PASSWORD,
            credentials->password);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load WiFi Credentials
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadWiFi(
        WiFiCredentials_t *credentials)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(credentials == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    memset(credentials,
           0,
           sizeof(WiFiCredentials_t));

    String value;

    value =
        g_preferences.getString(
            KEY_WIFI_SSID,
            "");

    value.toCharArray(
            credentials->ssid,
            sizeof(credentials->ssid));

    value =
        g_preferences.getString(
            KEY_WIFI_PASSWORD,
            "");

    value.toCharArray(
            credentials->password,
            sizeof(credentials->password));

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load WiFi Credentials
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadWiFi(
        WiFiCredentials_t *credentials)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(credentials == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    memset(credentials,
           0,
           sizeof(WiFiCredentials_t));

    String value;

    value =
        g_preferences.getString(
            KEY_WIFI_SSID,
            "");

    value.toCharArray(
            credentials->ssid,
            sizeof(credentials->ssid));

    value =
        g_preferences.getString(
            KEY_WIFI_PASSWORD,
            "");

    value.toCharArray(
            credentials->password,
            sizeof(credentials->password));

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load Firebase Configuration
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadFirebase(
        FirebaseConfig_t *config)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(config == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    memset(config,
           0,
           sizeof(FirebaseConfig_t));

    String value;

    value = g_preferences.getString(KEY_FIREBASE_API, "");
    value.toCharArray(config->apiKey,
                      sizeof(config->apiKey));

    value = g_preferences.getString(KEY_FIREBASE_PROJECT, "");
    value.toCharArray(config->projectId,
                      sizeof(config->projectId));

    value = g_preferences.getString(KEY_FIREBASE_DB, "");
    value.toCharArray(config->databaseUrl,
                      sizeof(config->databaseUrl));

    value = g_preferences.getString(KEY_FIREBASE_EMAIL, "");
    value.toCharArray(config->userEmail,
                      sizeof(config->userEmail));

    value = g_preferences.getString(KEY_FIREBASE_PASSWORD, "");
    value.toCharArray(config->userPassword,
                      sizeof(config->userPassword));

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Save Device Information
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_SaveDeviceInfo(
        const DeviceInfo_t *device)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(device == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    g_preferences.putString(
            KEY_DEVICE_ID,
            device->deviceId);

    g_preferences.putString(
            KEY_FW_VERSION,
            device->firmwareVersion);

    g_preferences.putString(
            KEY_HW_VERSION,
            device->hardwareRevision);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load Device Information
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadDeviceInfo(
        DeviceInfo_t *device)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(device == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    memset(device,
           0,
           sizeof(DeviceInfo_t));

    String value;

    value = g_preferences.getString(KEY_DEVICE_ID, "");
    value.toCharArray(device->deviceId,
                      sizeof(device->deviceId));

    value = g_preferences.getString(KEY_FW_VERSION, "");
    value.toCharArray(device->firmwareVersion,
                      sizeof(device->firmwareVersion));

    value = g_preferences.getString(KEY_HW_VERSION, "");
    value.toCharArray(device->hardwareRevision,
                      sizeof(device->hardwareRevision));

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Save Last Synchronization Timestamp
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_SaveLastSync(
        uint32_t timestamp)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    g_preferences.putUInt(
            KEY_LAST_SYNC,
            timestamp);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load Last Synchronization Timestamp
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadLastSync(
        uint32_t *timestamp)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(timestamp == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    *timestamp =
        g_preferences.getUInt(
            KEY_LAST_SYNC,
            0);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Save Firmware Version
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_SaveFirmwareVersion(
        const char *version)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if(version == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    g_preferences.putString(
            KEY_OTA_VERSION,
            version);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Load Firmware Version
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_LoadFirmwareVersion(
        char *version,
        uint16_t maxLength)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    if((version == nullptr) ||
       (maxLength == 0))
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    memset(version,
           0,
           maxLength);

    String value =
        g_preferences.getString(
            KEY_OTA_VERSION,
            "");

    value.toCharArray(
            version,
            maxLength);

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Clear Storage
 ******************************************************************************/

StorageStatus_t
PreferencesStorage_Clear(void)
{
    if(!PreferencesStorage_CheckInit())
    {
        return STORAGE_STATUS_NOT_INITIALIZED;
    }

    g_preferences.clear();

    return STORAGE_STATUS_OK;
}

