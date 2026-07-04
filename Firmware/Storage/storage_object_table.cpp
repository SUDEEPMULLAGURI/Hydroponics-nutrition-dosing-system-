/******************************************************************************
 * File        : storage_object_table.cpp
 ******************************************************************************/

#include "storage_object_table.h"

const StorageObjectInfo_t
g_storageObjectTable[STORAGE_KEY_COUNT] =
{
    {
        STORAGE_KEY_SYSTEM,
        "system",
        "config",
        256
    },

    {
        STORAGE_KEY_WIFI,
        "network",
        "wifi",
        256
    },

    {
        STORAGE_KEY_PUMP_CALIBRATION,
        "calibration",
        "pump",
        1024
    },

    {
        STORAGE_KEY_PH_CALIBRATION,
        "calibration",
        "ph",
        512
    },

    {
        STORAGE_KEY_EC_CALIBRATION,
        "calibration",
        "ec",
        512
    },

    {
        STORAGE_KEY_RECIPES,
        "recipe",
        "recipes",
        4096
    },

    {
        STORAGE_KEY_SETTINGS,
        "system",
        "settings",
        1024
    },

    {
        STORAGE_KEY_STATISTICS,
        "statistics",
        "runtime",
        1024
    },

    {
        STORAGE_KEY_LOGS,
        "logs",
        "events",
        8192
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
