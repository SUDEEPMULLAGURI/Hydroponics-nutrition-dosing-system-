/******************************************************************************
 * File        : storage_service.cpp
 * Description : Storage Service
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "storage_service.h"

#include "storage_backend.h"
#include "storage_crc.h"
#include "storage_object_table.h"

#include <Arduino.h>
#include <string.h>

/******************************************************************************
 * Configuration
 ******************************************************************************/

#define STORAGE_MAX_OBJECT_SIZE        8192U

/******************************************************************************
 * Private Variables
 ******************************************************************************/

static StorageStatus_t g_lastStatus =
    STORAGE_STATUS_NOT_INITIALIZED;

/*
 * Working buffer
 *
 * Layout:
 *
 * +----------------------+
 * | StorageHeader_t      |
 * +----------------------+
 * | User Data            |
 * +----------------------+
 */

static uint8_t
g_storageBuffer[
sizeof(StorageHeader_t)
+
STORAGE_MAX_OBJECT_SIZE];

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

static bool Storage_CheckKey(StorageKey_t key);

static bool Storage_CheckLength(
        const StorageObjectInfo_t *object,
        uint32_t length);

static void Storage_CreateHeader(
        StorageHeader_t *header,
        uint32_t dataLength,
        uint32_t crc);

static StorageStatus_t
Storage_ValidateHeader(
        const StorageHeader_t *header,
        uint32_t expectedLength);

/******************************************************************************
 * Check Storage Key
 ******************************************************************************/

static bool Storage_CheckKey(StorageKey_t key)
{
    return (key < STORAGE_KEY_COUNT);
}

/******************************************************************************
 * Check Object Size
 ******************************************************************************/

static bool Storage_CheckLength(
        const StorageObjectInfo_t *object,
        uint32_t length)
{
    if (object == nullptr)
    {
        return false;
    }

    if (length == 0)
    {
        return false;
    }

    if (length > object->maximumSize)
    {
        return false;
    }

    if (length > STORAGE_MAX_OBJECT_SIZE)
    {
        return false;
    }

    return true;
}

/******************************************************************************
 * Create Header
 ******************************************************************************/

static void Storage_CreateHeader(
        StorageHeader_t *header,
        uint32_t dataLength,
        uint32_t crc)
{
    header->magic = STORAGE_MAGIC;

    header->version = STORAGE_VERSION;

    header->headerSize =
        sizeof(StorageHeader_t);

    header->dataLength = dataLength;

    header->crc = crc;

    header->timestamp = millis();
}

/******************************************************************************
 * Validate Header
 ******************************************************************************/

static StorageStatus_t
Storage_ValidateHeader(
        const StorageHeader_t *header,
        uint32_t expectedLength)
{
    if (header == nullptr)
    {
        return STORAGE_STATUS_INVALID_PARAMETER;
    }

    if (header->magic != STORAGE_MAGIC)
    {
        return STORAGE_STATUS_INVALID_MAGIC;
    }

    if (header->version != STORAGE_VERSION)
    {
        return STORAGE_STATUS_INVALID_VERSION;
    }

    if (header->headerSize != sizeof(StorageHeader_t))
    {
        return STORAGE_STATUS_INVALID_HEADER;
    }

    if (header->dataLength != expectedLength)
    {
        return STORAGE_STATUS_INVALID_LENGTH;
    }

    return STORAGE_STATUS_OK;
}
/******************************************************************************
 * Save Object
 ******************************************************************************/

StorageStatus_t Storage_Save(StorageKey_t key,
                             const void *data,
                             uint32_t length)
{
    const StorageObjectInfo_t *object;

    StorageHeader_t header;

    uint32_t crc;

    uint32_t totalLength;

    /* Parameter checking */

    if (!StorageBackend_IsInitialized())
    {
        g_lastStatus = STORAGE_STATUS_NOT_INITIALIZED;
        return g_lastStatus;
    }

    if (!Storage_CheckKey(key))
    {
        g_lastStatus = STORAGE_STATUS_INVALID_PARAMETER;
        return g_lastStatus;
    }

    if (data == nullptr)
    {
        g_lastStatus = STORAGE_STATUS_INVALID_PARAMETER;
        return g_lastStatus;
    }

    object = Storage_GetObjectInfo(key);

    if (object == nullptr)
    {
        g_lastStatus = STORAGE_STATUS_NOT_FOUND;
        return g_lastStatus;
    }

    if (!Storage_CheckLength(object, length))
    {
        g_lastStatus = STORAGE_STATUS_INVALID_LENGTH;
        return g_lastStatus;
    }

    /* Calculate CRC */

    if (object->enableCRC)
    {
        crc = StorageCRC_Calculate(data, length);
    }
    else
    {
        crc = 0;
    }

    /* Build header */

    Storage_CreateHeader(
            &header,
            length,
            crc);

    /* Build storage object */

    memcpy(g_storageBuffer,
           &header,
           sizeof(StorageHeader_t));

    memcpy(g_storageBuffer +
           sizeof(StorageHeader_t),
           data,
           length);

    totalLength =
            sizeof(StorageHeader_t)
            + length;

    /* Write to backend */

    if (!StorageBackend_Write(
            object->objectName,
            g_storageBuffer,
            totalLength))
    {
        g_lastStatus =
            STORAGE_STATUS_WRITE_ERROR;

        return g_lastStatus;
    }

    g_lastStatus =
        STORAGE_STATUS_OK;

    return g_lastStatus;
}
/******************************************************************************
 * Load Object
 ******************************************************************************/

StorageStatus_t Storage_Load(StorageKey_t key,
                             void *data,
                             uint32_t expectedLength)
{
    const StorageObjectInfo_t *object;

    StorageHeader_t *header;

    uint8_t *payload;

    uint32_t storedLength;

    uint32_t totalLength;

    /*----------------------------------------------------------
        Parameter Checking
    ----------------------------------------------------------*/

    if (!StorageBackend_IsInitialized())
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_INITIALIZED;

        return g_lastStatus;
    }

    if (!Storage_CheckKey(key))
    {
        g_lastStatus =
            STORAGE_STATUS_INVALID_PARAMETER;

        return g_lastStatus;
    }

    if (data == nullptr)
    {
        g_lastStatus =
            STORAGE_STATUS_INVALID_PARAMETER;

        return g_lastStatus;
    }

    object =
        Storage_GetObjectInfo(key);

    if (object == nullptr)
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_FOUND;

        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Check Object Exists
    ----------------------------------------------------------*/

    if (!StorageBackend_Exists(object->objectName))
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_FOUND;

        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Determine Stored Size
    ----------------------------------------------------------*/

    storedLength =
        StorageBackend_GetSize(
            object->objectName);

    if (storedLength == 0)
    {
        g_lastStatus =
            STORAGE_STATUS_READ_ERROR;

        return g_lastStatus;
    }

    if (storedLength >
        sizeof(g_storageBuffer))
    {
        g_lastStatus =
            STORAGE_STATUS_INVALID_LENGTH;

        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Read Entire Object
    ----------------------------------------------------------*/

    if (!StorageBackend_Read(
            object->objectName,
            g_storageBuffer,
            storedLength))
    {
        g_lastStatus =
            STORAGE_STATUS_READ_ERROR;

        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Parse Header
    ----------------------------------------------------------*/

    header =
        (StorageHeader_t *)g_storageBuffer;

    payload =
        g_storageBuffer +
        sizeof(StorageHeader_t);

    /*----------------------------------------------------------
        Validate Header
    ----------------------------------------------------------*/

    g_lastStatus =
        Storage_ValidateHeader(
            header,
            expectedLength);

    if (g_lastStatus != STORAGE_STATUS_OK)
    {
        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Verify Total Size
    ----------------------------------------------------------*/

    totalLength =
        sizeof(StorageHeader_t)
        +
        header->dataLength;

    if (storedLength != totalLength)
    {
        g_lastStatus =
            STORAGE_STATUS_INVALID_LENGTH;

        return g_lastStatus;
    }

    /*----------------------------------------------------------
        Verify CRC
    ----------------------------------------------------------*/

    if (object->enableCRC)
    {
        if (!StorageCRC_Verify(
                payload,
                header->dataLength,
                header->crc))
        {
            g_lastStatus =
                STORAGE_STATUS_CRC_ERROR;

            return g_lastStatus;
        }
    }

    /*----------------------------------------------------------
        Copy User Data
    ----------------------------------------------------------*/

    memcpy(data,
           payload,
           header->dataLength);

    g_lastStatus =
        STORAGE_STATUS_OK;

    return g_lastStatus;
}
/******************************************************************************
 * Delete Object
 ******************************************************************************/

StorageStatus_t Storage_Delete(StorageKey_t key)
{
    const StorageObjectInfo_t *object;

    if (!StorageBackend_IsInitialized())
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_INITIALIZED;

        return g_lastStatus;
    }

    if (!Storage_CheckKey(key))
    {
        g_lastStatus =
            STORAGE_STATUS_INVALID_PARAMETER;

        return g_lastStatus;
    }

    object = Storage_GetObjectInfo(key);

    if (object == nullptr)
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_FOUND;

        return g_lastStatus;
    }

    if (!StorageBackend_Exists(object->objectName))
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_FOUND;

        return g_lastStatus;
    }

    if (!StorageBackend_Delete(object->objectName))
    {
        g_lastStatus =
            STORAGE_STATUS_DRIVER_ERROR;

        return g_lastStatus;
    }

    g_lastStatus =
        STORAGE_STATUS_OK;

    return g_lastStatus;
}

/******************************************************************************
 * Check Object Exists
 ******************************************************************************/

bool Storage_Exists(StorageKey_t key)
{
    const StorageObjectInfo_t *object;

    if (!StorageBackend_IsInitialized())
    {
        return false;
    }

    if (!Storage_CheckKey(key))
    {
        return false;
    }

    object = Storage_GetObjectInfo(key);

    if (object == nullptr)
    {
        return false;
    }

    return StorageBackend_Exists(
                object->objectName);
}

/******************************************************************************
 * Format Storage
 ******************************************************************************/

StorageStatus_t Storage_Format(void)
{
    if (!StorageBackend_IsInitialized())
    {
        g_lastStatus =
            STORAGE_STATUS_NOT_INITIALIZED;

        return g_lastStatus;
    }

    if (!StorageBackend_Format())
    {
        g_lastStatus =
            STORAGE_STATUS_DRIVER_ERROR;

        return g_lastStatus;
    }

    g_lastStatus =
        STORAGE_STATUS_OK;

    return g_lastStatus;
}

/******************************************************************************
 * Get Last Status
 ******************************************************************************/

StorageStatus_t Storage_GetLastStatus(void)
{
    return g_lastStatus;
}

