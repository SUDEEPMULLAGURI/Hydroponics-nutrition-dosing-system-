#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

/******************************************************************************
 * File        : wifi_manager.h
 * Description : WiFi Manager
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * WiFi State
 ******************************************************************************/

typedef enum
{
    WIFI_STATE_OFF = 0,

    WIFI_STATE_DISCONNECTED,

    WIFI_STATE_CONNECTING,

    WIFI_STATE_CONNECTED,

    WIFI_STATE_RECONNECTING,

    WIFI_STATE_ERROR

} WiFiState_t;

/******************************************************************************
 * WiFi Information
 ******************************************************************************/

typedef struct
{
    char ssid[32];

    char ip[16];

    char gateway[16];

    char subnet[16];

    int32_t rssi;

} WiFiInfo_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

bool WiFiManager_Init(void);

bool WiFiManager_Update(void);

bool WiFiManager_Connect(void);

bool WiFiManager_Disconnect(void);

bool WiFiManager_Reconnect(void);

bool WiFiManager_IsConnected(void);

WiFiState_t WiFiManager_GetState(void);

bool WiFiManager_GetInfo(
        WiFiInfo_t *info);

#ifdef __cplusplus
}
#endif

#endif
