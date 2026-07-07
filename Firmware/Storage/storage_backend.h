#ifndef STORAGE_BACKEND_H
#define STORAGE_BACKEND_H

/******************************************************************************
 * File        : storage_backend.h
 * Description : Generic Storage Backend Interface
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Initialization
 ******************************************************************************/

/**
 * Initialize backend.
 */
bool StorageBackend_Init(void);

/**
 * Shutdown backend.
 */
void StorageBackend_DeInit(void);

/**
 * Check initialization state.
 */
bool StorageBackend_IsInitialized(void);

/******************************************************************************
 * Object Operations
 ******************************************************************************/

/**
 * Write object.
 */
bool StorageBackend_Write(const char *objectName,
                          const void *data,
                          uint32_t length);

/**
 * Read object.
 */
bool StorageBackend_Read(const char *objectName,
                         void *data,
                         uint32_t length);

/**
 * Delete object.
 */
bool StorageBackend_Delete(const char *objectName);

/**
 * Check if object exists.
 */
bool StorageBackend_Exists(const char *objectName);

/**
 * Get stored object size.
 */
uint32_t StorageBackend_GetSize(const char *objectName);

/**
 * Erase all objects.
 */
bool StorageBackend_Format(void);

#ifdef __cplusplus
}
#endif

#endif
