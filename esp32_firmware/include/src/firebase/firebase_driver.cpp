/******************************************************************************
 * File        : firebase_driver.cpp
 * Description : Firebase Driver
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "firebase_driver.h"

#include "preferences_storage.h"
#include "storage_types.h"

#include <WiFi.h>

/*
 * Firebase Client Library
 * (Mobizt FirebaseClient)
 */

#include <FirebaseClient.h>

#include <Arduino.h>
#include <string.h>
/******************************************************************************
 * Private Variables
 ******************************************************************************/

static FirebaseConfig_t
g_config;

static bool
g_initialized = false;

static bool
g_connected = false;

/*
 * Firebase Client Objects
 */

static DefaultNetwork network;

static UserAuth auth;

static FirebaseApp app;

static AsyncClientClass client(network);

static RealtimeDatabase database;
/******************************************************************************
 * Initialize
 ******************************************************************************/

bool FirebaseDriver_Init(void)
{
    if(g_initialized)
    {
        return true;
    }

    memset(&g_config,
           0,
           sizeof(g_config));

    if(PreferencesStorage_LoadFirebase(
            &g_config)
        !=
        STORAGE_STATUS_OK)
    {
        return false;
    }

    auth.setEmail(
            g_config.userEmail);

    auth.setPassword(
            g_config.userPassword);

    app.setApiKey(
            g_config.apiKey);

    database.url(
            g_config.databaseUrl);

    g_initialized = true;

    return true;
}
/******************************************************************************
 * Connect
 ******************************************************************************/

bool FirebaseDriver_Connect(void)
{
    if(!g_initialized)
    {
        return false;
    }

    initializeApp(
            client,
            app,
            getAuth(auth));

    database.loop();

    g_connected = true;

    return true;
}
/******************************************************************************
 * Disconnect
 ******************************************************************************/

bool FirebaseDriver_Disconnect(void)
{
    g_connected = false;

    return true;
}
/******************************************************************************
 * Connection Status
 ******************************************************************************/

bool FirebaseDriver_IsConnected(void)
{
    if(!g_initialized)
    {
        return false;
    }

    if(!WiFi.isConnected())
    {
        return false;
    }

    return g_connected;
}

