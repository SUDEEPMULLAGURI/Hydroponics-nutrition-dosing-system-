/******************************************************************************
 * @file        hal_pwm.h
 * @brief       Hardware Abstraction Layer for PWM peripherals.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 *
 * @details
 * This module provides a hardware-independent interface for configuring
 * and controlling PWM peripherals used throughout the firmware.
 *
 * Higher software layers shall never access MCU timer registers directly.
 *
 ******************************************************************************/

#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdint.h>

#include "../hal_types.h"

namespace HAL::PWM
{

/*=============================================================================
 * PWM Channels
 *===========================================================================*/

enum class Channel : uint8_t
{
    PumpA = 0,
    PumpB,
    PumpC,
    PumpD,
    Mixer,

    Count
};

/*=============================================================================
 * PWM State
 *===========================================================================*/

enum class State : uint8_t
{
    Stopped,
    Running
};

/*=============================================================================
 * PWM Errors
 *===========================================================================*/

enum class Status : uint8_t
{
    Ok,

    InvalidChannel,

    InvalidDutyCycle,

    InvalidFrequency,

    AlreadyRunning,

    AlreadyStopped,

    Error
};

/*=============================================================================
 * PWM Configuration
 *===========================================================================*/

struct Config
{
    uint32_t frequencyHz;

    float dutyCyclePercent;

    HAL::Polarity polarity;
};

/*=============================================================================
 * PWM Runtime Information
 *===========================================================================*/

struct Runtime
{
    HAL::InitState initState;

    State state;

    Config config;
};

/*=============================================================================
 * Public API
 *===========================================================================*/

/**
 * @brief Initializes all PWM peripherals.
 */
HAL::Result Init();

/**
 * @brief Configures one PWM channel.
 *
 * @param channel PWM channel.
 * @param config PWM configuration.
 *
 * @return HAL::Result
 */
HAL::Result Configure(
    Channel channel,
    const Config& config);

/**
 * @brief Starts PWM output.
 *
 * @param channel PWM channel.
 *
 * @return HAL::Result
 */
HAL::Result Start(
    Channel channel);

/**
 * @brief Stops PWM output.
 *
 * @param channel PWM channel.
 *
 * @return HAL::Result
 */
HAL::Result Stop(
    Channel channel);

/**
 * @brief Sets PWM duty cycle.
 *
 * @param channel PWM channel.
 * @param duty Duty cycle (0.0 - 100.0 %)
 *
 * @return HAL::Result
 */
HAL::Result SetDutyCycle(
    Channel channel,
    float duty);

/**
 * @brief Sets PWM frequency.
 *
 * @param channel PWM channel.
 * @param frequencyHz PWM frequency.
 *
 * @return HAL::Result
 */
HAL::Result SetFrequency(
    Channel channel,
    uint32_t frequencyHz);

/**
 * @brief Returns current duty cycle.
 *
 * @param channel PWM channel.
 *
 * @return float Duty cycle percentage.
 */
float GetDutyCycle(
    Channel channel);

/**
 * @brief Returns configured frequency.
 *
 * @param channel PWM channel.
 *
 * @return uint32_t Frequency in Hz.
 */
uint32_t GetFrequency(
    Channel channel);

/**
 * @brief Returns current PWM state.
 *
 * @param channel PWM channel.
 *
 * @return State
 */
State GetState(
    Channel channel);

/**
 * @brief Returns runtime information.
 *
 * @param channel PWM channel.
 *
 * @return const Runtime&
 */
const Runtime& GetRuntime(
    Channel channel);

} // namespace HAL::PWM

#endif // HAL_PWM_H
