#ifndef FIREBASE_DATABASE_H
#define FIREBASE_DATABASE_H


  File         firebase_database.h
  Description  Firebase Database Service
 

#include stdint.h
#include stdbool.h

#ifdef __cplusplus
extern C
{
#endif

bool FirebaseDatabase_Init(void);

bool FirebaseDatabase_Write(
        const char path,
        const char json);

bool FirebaseDatabase_Read(
        const char path,
        char buffer,
        uint16_t maxLength);

bool FirebaseDatabase_Delete(
        const char path);

bool FirebaseDatabase_Update(
        const char path,
        const char json);

#ifdef __cplusplus
}
#endif

#endif
