/******************************************************************************
 * @file        hal_i2c.h
 * @brief       Hardware Abstraction Layer for I2C communication.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 *
 ******************************************************************************/

#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>

#include "../hal_types.h"

namespace HAL::I2C
{

/*=============================================================================
 * I2C Bus
 *===========================================================================*/

enum class Bus : uint8_t
{
    Bus0,
    Bus1,

    Count
};

/*=============================================================================
 * Address Mode
 *===========================================================================*/

enum class AddressMode : uint8_t
{
    Bits7,
    Bits10
};

/*=============================================================================
 * Transfer State
 *===========================================================================*/

enum class TransferState : uint8_t
{
    Idle,
    Busy
};

/*=============================================================================
 * Configuration
 *===========================================================================*/

struct Config
{
    uint32_t clockHz;

    AddressMode addressMode;
};

/*=============================================================================
 * Runtime Information
 *===========================================================================*/

struct Runtime
{
    HAL::InitState initState;

    TransferState transferState;

    Config config;
};

/*=============================================================================
 * Handle
 *===========================================================================*/

struct Handle
{
    Bus bus;
};

/*=============================================================================
 * Public API
 *===========================================================================*/

HAL::Result Init(
    Handle& handle,
    Bus bus,
    const Config& config);

HAL::Result Write(
    Handle& handle,
    uint8_t address,
    const uint8_t* data,
    uint16_t length);

HAL::Result Read(
    Handle& handle,
    uint8_t address,
    uint8_t* data,
    uint16_t length);

HAL::Result WriteRead(
    Handle& handle,
    uint8_t address,
    const uint8_t* txData,
    uint16_t txLength,
    uint8_t* rxData,
    uint16_t rxLength);

HAL::Result Scan(
    Handle& handle);

const Runtime& GetRuntime(
    const Handle& handle);

}

#endif
