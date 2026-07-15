/******************************************************************************
 * @file        hal_flash.h
 * @brief       Hardware Abstraction Layer for Flash Memory.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 *
 ******************************************************************************/

#ifndef HAL_FLASH_H
#define HAL_FLASH_H

#include <stdint.h>

#include "../hal_types.h"

namespace HAL::Flash
{

/*=============================================================================
 * Flash Region
 *===========================================================================*/

enum class Region : uint8_t
{
    Internal,
    External
};

/*=============================================================================
 * Runtime State
 *===========================================================================*/

enum class State : uint8_t
{
    Idle,
    Busy
};

/*=============================================================================
 * Flash Information
 *===========================================================================*/

struct Info
{
    uint32_t totalSizeBytes;

    uint32_t pageSizeBytes;

    uint32_t sectorSizeBytes;
};

/*=============================================================================
 * Runtime Information
 *===========================================================================*/

struct Runtime
{
    HAL::InitState initState;

    State state;

    Info info;
};

/*=============================================================================
 * Public API
 *===========================================================================*/

HAL::Result Init(
    Region region);

HAL::Result Read(
    Region region,
    uint32_t address,
    void* buffer,
    uint32_t length);

HAL::Result Write(
    Region region,
    uint32_t address,
    const void* buffer,
    uint32_t length);

HAL::Result EraseSector(
    Region region,
    uint32_t address);

HAL::Result EraseChip(
    Region region);

const Runtime& GetRuntime(
    Region region);

}

#endif
