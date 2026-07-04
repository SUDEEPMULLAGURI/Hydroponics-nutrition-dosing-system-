#ifndef STORAGE_OBJECT_TABLE_H
#define STORAGE_OBJECT_TABLE_H

/******************************************************************************
 * File        : storage_object_table.h
 * Description : Storage Object Definitions
 * Project     : Hydroponic Nutrient Dosing Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>

#include "storage_keys.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Storage Object Descriptor
 ******************************************************************************/

typedef struct
{
    StorageKey_t key;

    const char *namespaceName;

    const char *objectName;

    uint32_t maxSize;

} StorageObjectInfo_t;

/******************************************************************************
 * Public Table
 ******************************************************************************/

extern const StorageObjectInfo_t
g_storageObjectTable[STORAGE_KEY_COUNT];

/******************************************************************************
 * Public API
 ******************************************************************************/

const StorageObjectInfo_t*
Storage_GetObjectInfo(StorageKey_t key);

#ifdef __cplusplus
}
#endif

#endif