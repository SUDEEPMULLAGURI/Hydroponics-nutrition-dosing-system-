/******************************************************************************
 * File        : storage_object_table.cpp
 ******************************************************************************/

#include "storage_object_table.h"

const StorageObjectInfo_t
g_storageObjectTable[STORAGE_KEY_COUNT] =
{
    /* STORAGE_KEY_SYSTEM */

    {
        STORAGE_KEY_SYSTEM,
        "system",
        "config",
        512,
        true,
        true,
        false
    },

    /* STORAGE_KEY_SETTINGS */

    {
        STORAGE_KEY_SETTINGS,
        "system",
        "settings",
        1024,
        true,
        true,
        false
    },

    /* STORAGE_KEY_STATISTICS */

    {
        STORAGE_KEY_STATISTICS,
        "system",
        "stats",
        1024,
        false,
        false,
        false
    },

    /* STORAGE_KEY_WIFI */

    {
        STORAGE_KEY_WIFI,
        "network",
        "wifi",
        512,
        true,
        true,
        true
    },

    /* STORAGE_KEY_FIREBASE */

    {
        STORAGE_KEY_FIREBASE,
        "network",
        "firebase",
        1024,
        true,
        true,
        true
    },

    /* STORAGE_KEY_MQTT */

    {
        STORAGE_KEY_MQTT,
        "network",
        "mqtt",
        512,
        true,
        true,
        true
    },

    /* STORAGE_KEY_PUMP_CALIBRATION */

    {
        STORAGE_KEY_PUMP_CALIBRATION,
        "calibration",
        "pump",
        2048,
        true,
        true,
        false
    },

    /* STORAGE_KEY_PH_CALIBRATION */

    {
        STORAGE_KEY_PH_CALIBRATION,
        "calibration",
        "ph",
        512,
        true,
        true,
        false
    },

    /* STORAGE_KEY_EC_CALIBRATION */

    {
        STORAGE_KEY_EC_CALIBRATION,
        "calibration",
        "ec",
        512,
        true,
        true,
        false
    },

    /* STORAGE_KEY_TEMP_CALIBRATION */

    {
        STORAGE_KEY_TEMP_CALIBRATION,
        "calibration",
        "temp",
        256,
        true,
        true,
        false
    },

    /* STORAGE_KEY_WATER_LEVEL_CALIBRATION */

    {
        STORAGE_KEY_WATER_LEVEL_CALIBRATION,
        "calibration",
        "level",
        256,
        true,
        true,
        false
    },

    /* STORAGE_KEY_RECIPES */

    {
        STORAGE_KEY_RECIPES,
        "recipes",
        "profiles",
        8192,
        true,
        true,
        false
    },

    /* STORAGE_KEY_SCHEDULES */

    {
        STORAGE_KEY_SCHEDULES,
        "recipes",
        "schedule",
        4096,
        true,
        true,
        false
    },

    /* STORAGE_KEY_CROP_PROFILES */

    {
        STORAGE_KEY_CROP_PROFILES,
        "recipes",
        "crop",
        4096,
        true,
        true,
        false
    },

    /* STORAGE_KEY_EVENT_LOG */

    {
        STORAGE_KEY_EVENT_LOG,
        "logs",
        "events",
        32768,
        false,
        false,
        false
    },

    /* STORAGE_KEY_ALARM_LOG */

    {
        STORAGE_KEY_ALARM_LOG,
        "logs",
        "alarms",
        16384,
        false,
        false,
        false
    },

    /* STORAGE_KEY_USERS */

    {
        STORAGE_KEY_USERS,
        "security",
        "users",
        2048,
        true,
        true,
        true
    },

    /* STORAGE_KEY_DEVICE_INFO */

    {
        STORAGE_KEY_DEVICE_INFO,
        "system",
        "device",
        512,
        true,
        true,
        false
    }
};

/******************************************************************************
 * Get Object Information
 ******************************************************************************/

const StorageObjectInfo_t*
Storage_GetObjectInfo(StorageKey_t key)
{
    if(key >= STORAGE_KEY_COUNT)
    {
        return nullptr;
    }

    return &g_storageObjectTable[key];
}
