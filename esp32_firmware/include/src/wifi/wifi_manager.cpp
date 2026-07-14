/******************************************************************************
 * File        : wifi_manager.cpp
 * Description : WiFi Manager
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include "wifi_manager.h"

#include "preferences_storage.h"
#include "storage_types.h"
#include "esp32_config.h"

#include <WiFi.h>
#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static WiFiState_t
g_state =
WIFI_STATE_OFF;

static WiFiCredentials_t
g_credentials;

static WiFiInfo_t
g_info;

static uint32_t
g_lastReconnectTime = 0;

static bool
g_initialized = false;

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static void WiFiManager_Event(
        WiFiEvent_t event);

static void WiFiManager_UpdateInfo(void);
/******************************************************************************
 * Initialize
 ******************************************************************************/

bool WiFiManager_Init(void)
{
    if(g_initialized)
    {
        return true;
    }

    memset(&g_credentials,
           0,
           sizeof(g_credentials));

    memset(&g_info,
           0,
           sizeof(g_info));

    if(PreferencesStorage_LoadWiFi(
            &g_credentials)
        !=
        STORAGE_STATUS_OK)
    {
        g_state =
            WIFI_STATE_ERROR;

        return false;
    }

    WiFi.mode(WIFI_STA);

    WiFi.onEvent(
            WiFiManager_Event);

    g_state =
        WIFI_STATE_DISCONNECTED;

    g_initialized = true;

    return true;
}
/******************************************************************************
 * Connect
 ******************************************************************************/

bool WiFiManager_Connect(void)
{
    if(!g_initialized)
    {
        return false;
    }

    g_state =
        WIFI_STATE_CONNECTING;

    WiFi.begin(
            g_credentials.ssid,
            g_credentials.password);

    return true;
}
/******************************************************************************
 * Disconnect
 ******************************************************************************/

bool WiFiManager_Disconnect(void)
{
    WiFi.disconnect(true);

    g_state =
        WIFI_STATE_DISCONNECTED;

    return true;
}
/******************************************************************************
 * Reconnect
 ******************************************************************************/

bool WiFiManager_Reconnect(void)
{
    WiFi.disconnect(false);

    delay(100);

    return
        WiFiManager_Connect();
}
/******************************************************************************
 * Update
 ******************************************************************************/

bool WiFiManager_Update(void)
{
    if(!g_initialized)
    {
        return false;
    }

    /*
     * Automatic Reconnect
     */

    if(g_state == WIFI_STATE_DISCONNECTED)
    {
        if((millis() - g_lastReconnectTime) >=
            WIFI_RECONNECT_INTERVAL_MS)
        {
            g_lastReconnectTime = millis();

            WiFiManager_Connect();
        }
    }

    /*
     * Update Network Information
     */

    if(g_state == WIFI_STATE_CONNECTED)
    {
        WiFiManager_UpdateInfo();
    }

    return true;
}
/******************************************************************************
 * WiFi Event Handler
 ******************************************************************************/

static void
WiFiManager_Event(
        WiFiEvent_t event)
{
    switch(event)
    {
        case ARDUINO_EVENT_WIFI_STA_START:

            g_state =
                WIFI_STATE_DISCONNECTED;

            break;

        case ARDUINO_EVENT_WIFI_STA_CONNECTED:

            g_state =
                WIFI_STATE_CONNECTING;

            break;

        case ARDUINO_EVENT_WIFI_STA_GOT_IP:

            g_state =
                WIFI_STATE_CONNECTED;

            WiFiManager_UpdateInfo();

            break;

        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:

            g_state =
                WIFI_STATE_DISCONNECTED;

            break;

        default:

            break;
    }
}
/******************************************************************************
 * Update Network Information
 ******************************************************************************/

static void
WiFiManager_UpdateInfo(void)
{
    strncpy(
        g_info.ssid,
        WiFi.SSID().c_str(),
        sizeof(g_info.ssid) - 1);

    strncpy(
        g_info.ip,
        WiFi.localIP().toString().c_str(),
        sizeof(g_info.ip) - 1);

    strncpy(
        g_info.gateway,
        WiFi.gatewayIP().toString().c_str(),
        sizeof(g_info.gateway) - 1);

    strncpy(
        g_info.subnet,
        WiFi.subnetMask().toString().c_str(),
        sizeof(g_info.subnet) - 1);

    g_info.rssi =
        WiFi.RSSI();
}
/******************************************************************************
 * Connection Status
 ******************************************************************************/

bool
WiFiManager_IsConnected(void)
{
    return
    (
        g_state ==
        WIFI_STATE_CONNECTED
    );
}
/******************************************************************************
 * Current State
 ******************************************************************************/

WiFiState_t
WiFiManager_GetState(void)
{
    return g_state;
}
/******************************************************************************
 * Get Network Information
 ******************************************************************************/

bool
WiFiManager_GetInfo(
        WiFiInfo_t *info)
{
    if(info == nullptr)
    {
        return false;
    }

    memcpy(info,
           &g_info,
           sizeof(WiFiInfo_t));

    return true;
}

