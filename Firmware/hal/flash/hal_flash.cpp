/******************************************************************************
 * @file        hal_flash.cpp
 * @brief       Hardware Abstraction Layer for Flash Memory.
 ******************************************************************************/

#include "hal_flash.h"

#include <Arduino.h>
#include <cstring>

namespace HAL::Flash
{

constexpr std::size_t RegionCount =
    2;

static Runtime s_runtime[RegionCount];

static bool IsValidRegion(
    Region region)
{
    return static_cast<uint8_t>(region) <
           RegionCount;
}

HAL::Result Init(
    Region region)
{
    if(!IsValidRegion(region))
    {
        return HAL::Result::InvalidParameter;
    }

    uint8_t index =
        static_cast<uint8_t>(region);

    s_runtime[index].initState =
        HAL::InitState::Initialized;

    s_runtime[index].state =
        State::Idle;

    /*
     * Example values.
     * Update when actual Flash device is selected.
     */

    s_runtime[index].info.totalSizeBytes =
        1024 * 1024;

    s_runtime[index].info.pageSizeBytes =
        256;

    s_runtime[index].info.sectorSizeBytes =
        4096;

    return HAL::Result::Ok;
}

HAL::Result Read(
    Region region,
    uint32_t address,
    void* buffer,
    uint32_t length)
{
    (void)region;
    (void)address;
    (void)buffer;
    (void)length;

    /*
     * TODO:
     * Replace with MAX32630 Flash Driver
     */

    return HAL::Result::Unsupported;
}

HAL::Result Write(
    Region region,
    uint32_t address,
    const void* buffer,
    uint32_t length)
{
    (void)region;
    (void)address;
    (void)buffer;
    (void)length;

    /*
     * TODO:
     * Replace with MAX32630 Flash Driver
     */

    return HAL::Result::Unsupported;
}

HAL::Result EraseSector(
    Region region,
    uint32_t address)
{
    (void)region;
    (void)address;

    /*
     * TODO:
     */

    return HAL::Result::Unsupported;
}

HAL::Result EraseChip(
    Region region)
{
    (void)region;

    /*
     * TODO:
     */

    return HAL::Result::Unsupported;
}

const Runtime& GetRuntime(
    Region region)
{
    return s_runtime[
        static_cast<uint8_t>(region)];
}

}
