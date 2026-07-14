#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

/******************************************************************************
 * File        : firebase_manager.h
 * Description : Firebase Cloud Manager
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Firebase State
 ******************************************************************************/

typedef enum
{
    FIREBASE_STATE_OFFLINE = 0,

    FIREBASE_STATE_CONNECTING,

    FIREBASE_STATE_AUTHENTICATING,

    FIREBASE_STATE_CONNECTED,

    FIREBASE_STATE_ERROR

} FirebaseState_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

bool FirebaseManager_Init(void);

bool FirebaseManager_Update(void);

bool FirebaseManager_Connect(void);

bool FirebaseManager_Disconnect(void);

bool FirebaseManager_IsConnected(void);

FirebaseState_t FirebaseManager_GetState(void);

#ifdef __cplusplus
}
#endif

#endif
