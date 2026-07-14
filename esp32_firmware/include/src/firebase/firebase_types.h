#ifndef FIREBASE_TYPES_H
#define FIREBASE_TYPES_H

/******************************************************************************
 * File        : firebase_types.h
 * Description : Firebase Data Types
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Authentication
 ******************************************************************************/

typedef struct
{
    char apiKey[128];

    char databaseUrl[128];

    char userEmail[64];

    char userPassword[64];

} FirebaseCredentials_t;

/******************************************************************************
 * Device
 ******************************************************************************/

typedef struct
{
    char deviceId[32];

    char firmwareVersion[16];

    char hardwareVersion[16];

} FirebaseDeviceInfo_t;

/******************************************************************************
 * Connection Statistics
 ******************************************************************************/

typedef struct
{
    bool connected;

    uint32_t reconnectCount;

    uint32_t uploadCount;

    uint32_t downloadCount;

    uint32_t uploadErrors;

    uint32_t downloadErrors;

} FirebaseStatistics_t;

#ifdef __cplusplus
}
#endif

#endif
