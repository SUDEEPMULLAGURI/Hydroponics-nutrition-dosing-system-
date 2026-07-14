#ifndef FIREBASE_DRIVER_H
#define FIREBASE_DRIVER_H

/******************************************************************************
 * File        : firebase_driver.h
 * Description : Firebase Driver
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Public API
 ******************************************************************************/

bool FirebaseDriver_Init(void);

bool FirebaseDriver_Connect(void);

bool FirebaseDriver_Disconnect(void);

bool FirebaseDriver_IsConnected(void);

bool FirebaseDriver_Publish(
        const char *path,
        const char *json);

bool FirebaseDriver_Read(
        const char *path,
        char *buffer,
        uint16_t maxLength);

bool FirebaseDriver_Delete(
        const char *path);

bool FirebaseDriver_Update(
        const char *path,
        const char *json);

#ifdef __cplusplus
}
#endif

#endif
