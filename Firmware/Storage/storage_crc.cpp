/******************************************************************************
 * File        : storage_crc.cpp
 * Description : CRC32 Engine
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include "storage_crc.h"

/******************************************************************************
 * CRC32 Polynomial
 ******************************************************************************/

#define CRC32_POLYNOMIAL      (0xEDB88320UL)
#define CRC32_INITIAL_VALUE   (0xFFFFFFFFUL)
#define CRC32_FINAL_XOR       (0xFFFFFFFFUL)

/******************************************************************************
 * Initialize
 ******************************************************************************/

bool StorageCRC_Init(void)
{
    return true;
}

/******************************************************************************
 * Calculate CRC32
 ******************************************************************************/

uint32_t StorageCRC_Calculate(const void *data,
                              uint32_t length)
{
    if ((data == nullptr) || (length == 0))
    {
        return 0;
    }

    uint32_t crc = CRC32_INITIAL_VALUE;

    const uint8_t *bytes =
        (const uint8_t *)data;

    for(uint32_t i = 0; i < length; i++)
    {
        crc ^= bytes[i];

        for(uint8_t bit = 0; bit < 8; bit++)
        {
            if(crc & 1)
            {
                crc =
                    (crc >> 1) ^
                    CRC32_POLYNOMIAL;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc ^ CRC32_FINAL_XOR;
}

/******************************************************************************
 * Verify CRC
 ******************************************************************************/

bool StorageCRC_Verify(const void *data,
                       uint32_t length,
                       uint32_t expected)
{
    uint32_t calculated =
        StorageCRC_Calculate(data, length);

    return (calculated == expected);
}
