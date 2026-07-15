/******************************************************************************
 * @file        hal_i2c.cpp
 * @brief       Hardware Abstraction Layer for I2C communication.
 ******************************************************************************/

#include "hal_i2c.h"

#include <Arduino.h>
#include <Wire.h>

namespace HAL::I2C
{

constexpr std::size_t BusCount =
    static_cast<std::size_t>(Bus::Count);

static Runtime s_runtime[BusCount];

static bool IsValidBus(Bus bus)
{
    return static_cast<uint8_t>(bus) <
           static_cast<uint8_t>(Bus::Count);
}

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

    s_runtime[index].transferState =
        TransferState::Idle;

    s_runtime[index].config = config;

    Wire.begin();

    Wire.setClock(config.clockHz);

    return HAL::Result::Ok;
}

HAL::Result Write(
    Handle& handle,
    uint8_t address,
    const uint8_t* data,
    uint16_t length)
{
    uint8_t index =
        static_cast<uint8_t>(handle.bus);

    s_runtime[index].transferState =
        TransferState::Busy;

    Wire.beginTransmission(address);

    for(uint16_t i = 0; i < length; i++)
    {
        Wire.write(data[i]);
    }

    Wire.endTransmission();

    s_runtime[index].transferState =
        TransferState::Idle;

    return HAL::Result::Ok;
}

HAL::Result Read(
    Handle& handle,
    uint8_t address,
    uint8_t* data,
    uint16_t length)
{
    uint8_t index =
        static_cast<uint8_t>(handle.bus);

    s_runtime[index].transferState =
        TransferState::Busy;

    Wire.requestFrom(address, length);

    uint16_t i = 0;

    while(Wire.available() && i < length)
    {
        data[i++] = Wire.read();
    }

    s_runtime[index].transferState =
        TransferState::Idle;

    return HAL::Result::Ok;
}

HAL::Result WriteRead(
    Handle& handle,
    uint8_t address,
    const uint8_t* txData,
    uint16_t txLength,
    uint8_t* rxData,
    uint16_t rxLength)
{
    HAL::Result result;

    result = Write(
        handle,
        address,
        txData,
        txLength);

    if(result != HAL::Result::Ok)
    {
        return result;
    }

    return Read(
        handle,
        address,
        rxData,
        rxLength);
}

HAL::Result Scan(
    Handle& handle)
{
    (void)handle;

    for(uint8_t address = 1;
        address < 127;
        address++)
    {
        Wire.beginTransmission(address);

        if(Wire.endTransmission() == 0)
        {
            /* Device Found */
        }
    }

    return HAL::Result::Ok;
}

const Runtime& GetRuntime(
    const Handle& handle)
{
    return s_runtime[
        static_cast<uint8_t>(handle.bus)];
}

}
