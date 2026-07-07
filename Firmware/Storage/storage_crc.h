#ifndef STORAGE_CRC_H
#define STORAGE_CRC_H

/******************************************************************************
 * File        : storage_crc.h
 * Description : CRC32 Engine
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
 * @brief Initialize CRC engine.
 *
 * Currently no initialization is required,
 * but the function is provided for future
 * hardware CRC peripherals.
 *
 * @return true Always true.
 */
bool StorageCRC_Init(void);

/******************************************************************************
 * CRC Calculation
 ******************************************************************************/

/**
 * @brief Calculate CRC32.
 *
 * @param data Pointer to data
 * @param length Number of bytes
 *
 * @return CRC32 value
 */
uint32_t StorageCRC_Calculate(const void *data,
                              uint32_t length);

/******************************************************************************
 * CRC Verification
 ******************************************************************************/

/**
 * @brief Verify CRC.
 *
 * @param data Pointer to data
 * @param length Number of bytes
 * @param expected Expected CRC
 *
 * @return true if CRC matches
 */
bool StorageCRC_Verify(const void *data,
                       uint32_t length,
                       uint32_t expected);

#ifdef __cplusplus
}
#endif

#endif