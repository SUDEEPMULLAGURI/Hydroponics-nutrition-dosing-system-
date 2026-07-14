#ifndef STORAGE_KEYS_H
#define STORAGE_KEYS_H

/******************************************************************************
 * File        : storage_keys.h
 * Description : Preferences Storage Keys
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#define STORAGE_NAMESPACE             "hydroponics"

/******************************************************************************
 * WiFi
 ******************************************************************************/

#define KEY_WIFI_SSID                 "wifi_ssid"
#define KEY_WIFI_PASSWORD             "wifi_pass"

/******************************************************************************
 * Firebase
 ******************************************************************************/

#define KEY_FIREBASE_API              "fb_api"
#define KEY_FIREBASE_PROJECT          "fb_proj"
#define KEY_FIREBASE_DB               "fb_db"
#define KEY_FIREBASE_EMAIL            "fb_email"
#define KEY_FIREBASE_PASSWORD         "fb_pass"

/******************************************************************************
 * Device
 ******************************************************************************/

#define KEY_DEVICE_ID                 "device_id"
#define KEY_FW_VERSION                "fw_ver"
#define KEY_HW_VERSION                "hw_ver"

/******************************************************************************
 * Cloud
 ******************************************************************************/

#define KEY_LAST_SYNC                 "last_sync"
#define KEY_OFFLINE_INDEX             "offline_idx"

/******************************************************************************
 * OTA
 ******************************************************************************/

#define KEY_OTA_VERSION               "ota_ver"
#define KEY_OTA_PENDING               "ota_pending"

#endif
