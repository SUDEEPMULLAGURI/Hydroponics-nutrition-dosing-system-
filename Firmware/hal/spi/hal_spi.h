/******************************************************************************
 * @file        hal_spi.h
 * @brief       Hardware Abstraction Layer for SPI communication.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 *
 * @details
 * This module provides a hardware-independent interface for SPI peripherals.
 * Higher software layers shall never access MCU SPI registers directly.
 *
 ******************************************************************************/

#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>

#include "../hal_types.h"

namespace HAL::SPI
{

/*=============================================================================
 * SPI Bus Selection
 *===========================================================================*/

enum class Bus : uint8_t
{
    Bus0,
    Bus1,

    Count
};

/*=============================================================================
 * SPI Clock Mode
 *===========================================================================*/

enum class Mode : uint8_t
{
    Mode0,
    Mode1,
    Mode2,
    Mode3
};

/*=============================================================================
 * SPI Bit Order
 *===========================================================================*/

enum class BitOrder : uint8_t
{
    MSB_First,
    LSB_First
};

/*=============================================================================
 * SPI Chip Select
 *===========================================================================*/

enum class ChipSelect : uint8_t
{
    Manual,
    Automatic
};

/*=============================================================================
 * SPI Configuration
 *===========================================================================*/

struct Config
{
    uint32_t clockHz;

    Mode mode;

    BitOrder bitOrder;

    ChipSelect chipSelect;
};

/*=============================================================================
 * SPI Runtime Information
 *===========================================================================*/

struct Runtime
{
    HAL::InitState initState;

    Config config;

    bool busy;
};

/*=============================================================================
 * SPI Handle
 *===========================================================================*/

struct Handle
{
    Bus bus;
};

/*=============================================================================
 * Public API
 *===========================================================================*/

/**
 * @brief Initializes one SPI peripheral.
 */
HAL::Result Init(
    Handle& handle,
    Bus bus,
    const Config& config);

/**
 * @brief Transmit data.
 */
HAL::Result Transmit(
    Handle& handle,
    const uint8_t* txData,
    uint16_t length);

/**
 * @brief Receive data.
 */
HAL::Result Receive(
    Handle& handle,
    uint8_t* rxData,
    uint16_t length);

/**
 * @brief Full duplex transfer.
 */
HAL::Result Transfer(
    Handle& handle,
    const uint8_t* txData,
    uint8_t* rxData,
    uint16_t length);

/**
 * @brief Returns runtime information.
 */
const Runtime& GetRuntime(
    const Handle& handle);

}

#endif
