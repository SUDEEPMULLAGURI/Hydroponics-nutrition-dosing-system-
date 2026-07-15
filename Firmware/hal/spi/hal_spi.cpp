/******************************************************************************
 * @file        hal_spi.cpp
 * @brief       Hardware Abstraction Layer for SPI communication.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 ******************************************************************************/

#include "hal_spi.h"

#include <Arduino.h>
#include <SPI.h>

namespace HAL::SPI
{

/*=============================================================================
 * Local Constants
 *===========================================================================*/

constexpr std::size_t BusCount =
    static_cast<std::size_t>(Bus::Count);

/*=============================================================================
 * Local Runtime Storage
 *===========================================================================*/

static Runtime s_runtime[BusCount];

/*=============================================================================
 * Local Helper Functions
 *===========================================================================*/

static bool IsValidBus(Bus bus)
{
    return static_cast<uint8_t>(bus) <
           static_cast<uint8_t>(Bus::Count);
}

static SPISettings CreateSettings(const Config& config)
{
    uint8_t mode = SPI_MODE0;

    switch(config.mode)
    {
        case Mode::Mode0:
            mode = SPI_MODE0;
            break;

        case Mode::Mode1:
            mode = SPI_MODE1;
            break;

        case Mode::Mode2:
            mode = SPI_MODE2;
            break;

        case Mode::Mode3:
            mode = SPI_MODE3;
            break;
    }

    BitOrder order =
        (config.bitOrder == BitOrder::MSB_First)
        ? MSBFIRST
        : LSBFIRST;

    return SPISettings(
        config.clockHz,
        order,
        mode);
}

/*=============================================================================
 * Public Functions
 *===========================================================================*/

HAL::Result Init(
    Handle& handle,
    Bus bus,
    const Config& config)
{
    if(!IsValidBus(bus))
    {
        return HAL::Result::InvalidParameter;
    }

    handle.bus = bus;

    uint8_t index =
        static_cast<uint8_t>(bus);

    s_runtime[index].initState =
        HAL::InitState::Initialized;

    s_runtime[index].config = config;

    s_runtime[index].busy = false;

    SPI.begin();

    return HAL::Result::Ok;
}

HAL::Result Transmit(
    Handle& handle,
    const uint8_t* txData,
    uint16_t length)
{
    uint8_t index =
        static_cast<uint8_t>(handle.bus);

    if(s_runtime[index].initState !=
       HAL::InitState::Initialized)
    {
        return HAL::Result::NotInitialized;
    }

    s_runtime[index].busy = true;

    SPI.beginTransaction(
        CreateSettings(
            s_runtime[index].config));

    for(uint16_t i = 0; i < length; i++)
    {
        SPI.transfer(txData[i]);
    }

    SPI.endTransaction();

    s_runtime[index].busy = false;

    return HAL::Result::Ok;
}

HAL::Result Receive(
    Handle& handle,
    uint8_t* rxData,
    uint16_t length)
{
    uint8_t index =
        static_cast<uint8_t>(handle.bus);

    if(s_runtime[index].initState !=
       HAL::InitState::Initialized)
    {
        return HAL::Result::NotInitialized;
    }

    s_runtime[index].busy = true;

    SPI.beginTransaction(
        CreateSettings(
            s_runtime[index].config));

    for(uint16_t i = 0; i < length; i++)
    {
        rxData[i] = SPI.transfer(0xFF);
    }

    SPI.endTransaction();

    s_runtime[index].busy = false;

    return HAL::Result::Ok;
}

HAL::Result Transfer(
    Handle& handle,
    const uint8_t* txData,
    uint8_t* rxData,
    uint16_t length)
{
    uint8_t index =
        static_cast<uint8_t>(handle.bus);

    if(s_runtime[index].initState !=
       HAL::InitState::Initialized)
    {
        return HAL::Result::NotInitialized;
    }

    s_runtime[index].busy = true;

    SPI.beginTransaction(
        CreateSettings(
            s_runtime[index].config));

    for(uint16_t i = 0; i < length; i++)
    {
        rxData[i] =
            SPI.transfer(txData[i]);
    }

    SPI.endTransaction();

    s_runtime[index].busy = false;

    return HAL::Result::Ok;
}

const Runtime& GetRuntime(
    const Handle& handle)
{
    return s_runtime[
        static_cast<uint8_t>(handle.bus)];
}

} // namespace HAL::SPI
