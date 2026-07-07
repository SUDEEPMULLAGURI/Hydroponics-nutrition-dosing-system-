/******************************************************************************
 * File        : storage_driver.cpp
 * Description : ESP32 Storage Driver
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "storage_driver.h"

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
 * Initialize Driver
 ******************************************************************************/

bool StorageDriver_Init(void)
{
    if(g_initialized)
    {
        return true;
    }

    if(!g_preferences.begin(STORAGE_NAMESPACE, false))
    {
        return false;
    }

    g_initialized = true;

    return true;
}

/******************************************************************************
 * Write Object
 ******************************************************************************/

bool StorageDriver_Write(const char *name,
                         const void *data,
                         uint32_t length)
{
    if(!g_initialized)
    {
        return false;
    }

    if(name == nullptr)
    {
        return false;
    }

    if(data == nullptr)
    {
        return false;
    }

    if(length == 0)
    {
        return false;
    }

    size_t written =
        g_preferences.putBytes(name,
                               data,
                               length);

    return (written == length);
}

/******************************************************************************
 * Read Object
 ******************************************************************************/

bool StorageDriver_Read(const char *name,
                        void *data,
                        uint32_t length)
{
    if(!g_initialized)
    {
        return false;
    }

    if(name == nullptr)
    {
        return false;
    }

    if(data == nullptr)
    {
        return false;
    }

    if(length == 0)
    {
        return false;
    }

    size_t read =
        g_preferences.getBytes(name,
                               data,
                               length);

    return (read == length);
}

/******************************************************************************
 * Check Object Exists
 ******************************************************************************/

bool StorageDriver_Exists(const char *name)
{
    if(!g_initialized)
    {
        return false;
    }

    if(name == nullptr)
    {
        return false;
    }

    return g_preferences.isKey(name);
}

/******************************************************************************
 * Delete Object
 ******************************************************************************/

bool StorageDriver_Delete(const char *name)
{
    if(!g_initialized)
    {
        return false;
    }

    if(name == nullptr)
    {
        return false;
    }

    return g_preferences.remove(name);
}

/******************************************************************************
 * Format Storage
 ******************************************************************************/

bool StorageDriver_Format(void)
{
    if(!g_initialized)
    {
        return false;
    }

    return g_preferences.clear();
}

/******************************************************************************
 * Deinitialize Driver
 ******************************************************************************/

void StorageDriver_DeInit(void)
{
    if(!g_initialized)
    {
        return;
    }

    g_preferences.end();

    g_initialized = false;
}
