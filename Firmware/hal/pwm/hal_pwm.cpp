/******************************************************************************
 * @file        hal_pwm.cpp
 * @brief       Hardware Abstraction Layer for PWM peripherals.
 *
 * @author      Sudeep
 * @project     Commercial Hydroponics Nutrition Dosing System
 ******************************************************************************/

#include "hal_pwm.h"
#include "../../pins.h"

#include <Arduino.h>

namespace HAL::PWM
{

/*=============================================================================
 * Local Runtime Storage
 *===========================================================================*/

static Runtime s_runtime[static_cast<uint8_t>(Channel::Count)];

/*=============================================================================
 * Local Helper Functions
 *===========================================================================*/

static uint8_t GetPin(Channel channel)
{
    switch (channel)
    {
        case Channel::PumpA:
            return PIN_PUMP_A_PWM;

        case Channel::PumpB:
            return PIN_PUMP_B_PWM;

        case Channel::PumpC:
            return PIN_PUMP_C_PWM;

        case Channel::PumpD:
            return PIN_PUMP_D_PWM;

        case Channel::Mixer:
            return PIN_MIXER_PWM;

        default:
            return 255;
    }
}

static bool IsValidChannel(Channel channel)
{
    return (static_cast<uint8_t>(channel) <
            static_cast<uint8_t>(Channel::Count));
}

/*=============================================================================
 * Public Functions
 *===========================================================================*/

HAL::Result Init()
{
    for (uint8_t i = 0;
         i < static_cast<uint8_t>(Channel::Count);
         ++i)
    {
        s_runtime[i].initState = HAL::InitState::Initialized;

        s_runtime[i].state = State::Stopped;

        s_runtime[i].config.frequencyHz = 1000;

        s_runtime[i].config.dutyCyclePercent = 0.0f;

        s_runtime[i].config.polarity = HAL::Polarity::Normal;
    }

    return HAL::Result::Ok;
}

HAL::Result Configure(
    Channel channel,
    const Config& config)
{
    if (!IsValidChannel(channel))
    {
        return HAL::Result::InvalidParameter;
    }

    if (config.dutyCyclePercent < 0.0f ||
        config.dutyCyclePercent > 100.0f)
    {
        return HAL::Result::InvalidParameter;
    }

    uint8_t index = static_cast<uint8_t>(channel);

    s_runtime[index].config = config;

    /*
     * NOTE:
     * Arduino analogWrite() does not allow frequency
     * configuration on every platform.
     *
     * This configuration is stored so the future
     * MAX32630 SDK implementation can apply it.
     */

    return HAL::Result::Ok;
}

HAL::Result Start(Channel channel)
{
    if (!IsValidChannel(channel))
    {
        return HAL::Result::InvalidParameter;
    }

    uint8_t index = static_cast<uint8_t>(channel);

    uint8_t pin = GetPin(channel);

    uint8_t pwm =
        static_cast<uint8_t>(
            (s_runtime[index]
                 .config
                 .dutyCyclePercent /
             100.0f) *
            255.0f);

    analogWrite(pin, pwm);

    s_runtime[index].state = State::Running;

    return HAL::Result::Ok;
}

HAL::Result Stop(Channel channel)
{
    if (!IsValidChannel(channel))
    {
        return HAL::Result::InvalidParameter;
    }

    uint8_t pin = GetPin(channel);

    analogWrite(pin, 0);

    s_runtime[static_cast<uint8_t>(channel)].state =
        State::Stopped;

    return HAL::Result::Ok;
}

HAL::Result SetDutyCycle(
    Channel channel,
    float duty)
{
    if (!IsValidChannel(channel))
    {
        return HAL::Result::InvalidParameter;
    }

    if (duty < 0.0f || duty > 100.0f)
    {
        return HAL::Result::InvalidParameter;
    }

    uint8_t index =
        static_cast<uint8_t>(channel);

    s_runtime[index].config.dutyCyclePercent =
        duty;

    if (s_runtime[index].state ==
        State::Running)
    {
        Start(channel);
    }

    return HAL::Result::Ok;
}

HAL::Result SetFrequency(
    Channel channel,
    uint32_t frequencyHz)
{
    if (!IsValidChannel(channel))
    {
        return HAL::Result::InvalidParameter;
    }

    s_runtime[static_cast<uint8_t>(channel)]
        .config
        .frequencyHz = frequencyHz;

    /*
     * Arduino implementation:
     * Frequency is stored only.
     *
     * MAX32630 implementation:
     * Will configure timer registers.
     */

    return HAL::Result::Ok;
}

float GetDutyCycle(Channel channel)
{
    return s_runtime
        [static_cast<uint8_t>(channel)]
            .config
            .dutyCyclePercent;
}

uint32_t GetFrequency(Channel channel)
{
    return s_runtime
        [static_cast<uint8_t>(channel)]
            .config
            .frequencyHz;
}

State GetState(Channel channel)
{
    return s_runtime
        [static_cast<uint8_t>(channel)]
            .state;
}

const Runtime& GetRuntime(Channel channel)
{
    return s_runtime
        [static_cast<uint8_t>(channel)];
}

} // namespace HAL::PWM
