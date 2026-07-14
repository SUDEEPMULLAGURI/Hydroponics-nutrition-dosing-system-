#ifndef FIREBASE_AUTH_H
#define FIREBASE_AUTH_H

/******************************************************************************
 * File        : firebase_auth.h
 * Description : Firebase Authentication Service
 ******************************************************************************/

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

bool FirebaseAuth_Init(void);

bool FirebaseAuth_Login(void);

bool FirebaseAuth_RefreshToken(void);

bool FirebaseAuth_IsAuthenticated(void);

void FirebaseAuth_Update(void);

#ifdef __cplusplus
}
#endif

#endif
