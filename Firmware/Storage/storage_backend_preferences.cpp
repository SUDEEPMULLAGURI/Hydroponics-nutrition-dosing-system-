/******************************************************************************
 * File        : storage_backend_preferences.cpp
 * Description : ESP32 Preferences Storage Backend
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "storage_backend.h"

#include <Arduino.h>
#include <Preferences.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define STORAGE_NAMESPACE      "storage"

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static Preferences g_preferences;

static bool g_initialized = false;

/******************************************************************************
 * Initialize
 ******************************************************************************/

bool StorageBackend_Init(void)
{
    if (g_initialized)
    {
        return true;
    }

    if (!g_preferences.begin(STORAGE_NAMESPACE, false))
    {
        return false;
    }

    g_initialized = true;

    return true;
}

/******************************************************************************
 * Deinitialize
 ******************************************************************************/

void StorageBackend_DeInit(void)
{
    if (!g_initialized)
    {
        return;
    }

    g_preferences.end();

    g_initialized = false;
}

/******************************************************************************
 * Initialization Status
 ******************************************************************************/

bool StorageBackend_IsInitialized(void)
{
    return g_initialized;
}

/******************************************************************************
 * Write Object
 ******************************************************************************/

bool StorageBackend_Write(const char *objectName,
                          const void *data,
                          uint32_t length)
{
    if (!g_initialized)
    {
        return false;
    }

    if ((objectName == nullptr) ||
        (data == nullptr) ||
        (length == 0))
    {
        return false;
    }

    size_t written =
        g_preferences.putBytes(objectName,
                               data,
                               length);

    return (written == length);
}

/******************************************************************************
 * Read Object
 ******************************************************************************/

bool StorageBackend_Read(const char *objectName,
                         void *data,
                         uint32_t length)
{
    if (!g_initialized)
    {
        return false;
    }

    if ((objectName == nullptr) ||
        (data == nullptr) ||
        (length == 0))
    {
        return false;
    }

    size_t read =
        g_preferences.getBytes(objectName,
                               data,
                               length);

    return (read == length);
}

/******************************************************************************
 * Delete Object
 ******************************************************************************/

bool StorageBackend_Delete(const char *objectName)
{
    if (!g_initialized)
    {
        return false;
    }

    if (objectName == nullptr)
    {
        return false;
    }

    return g_preferences.remove(objectName);
}

/******************************************************************************
 * Check Object Exists
 ******************************************************************************/

bool StorageBackend_Exists(const char *objectName)
{
    if (!g_initialized)
    {
        return false;
    }

    if (objectName == nullptr)
    {
        return false;
    }

    return g_preferences.isKey(objectName);
}

/******************************************************************************
 * Get Stored Object Size
 ******************************************************************************/

uint32_t StorageBackend_GetSize(const char *objectName)
{
    if (!g_initialized)
    {
        return 0;
    }

    if (objectName == nullptr)
    {
        return 0;
    }

    return g_preferences.getBytesLength(objectName);
}

/******************************************************************************
 * Format Storage
 ******************************************************************************/

bool StorageBackend_Format(void)
{
    if (!g_initialized)
    {
        return false;
    }

    return g_preferences.clear();
}
