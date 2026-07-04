#ifndef TEMPERATURE_H
#define TEMPERATURE_H

/******************************************************************************
 * File        : temperature.h
 * Description : DS18B20 Temperature Sensor Driver
 * Project     : Hydroponic Nutrient Dosing Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Sensor Status
 ******************************************************************************/

typedef enum
{
    SENSOR_NOT_INITIALIZED = 0,

    SENSOR_OK,

    SENSOR_DISCONNECTED,

    SENSOR_OUT_OF_RANGE,

    SENSOR_TIMEOUT,

    SENSOR_ERROR

} SensorStatus_t;

/******************************************************************************
 * Public API
 ******************************************************************************/

/**
 * @brief Initialize DS18B20 sensor.
 *
 * @return true  Initialization successful.
 * @return false Initialization failed.
 */
bool Temperature_Init(void);

/**
 * @brief Read and update temperature.
 *
 * This function should be called periodically.
 *
 * @return true  New reading available.
 * @return false Reading failed.
 */
bool Temperature_Update(void);

/**
 * @brief Get filtered temperature.
 *
 * @return Temperature in degree Celsius.
 */
float Temperature_GetValue(void);

/**
 * @brief Get current sensor status.
 *
 * @return SensorStatus_t
 */
SensorStatus_t Temperature_GetStatus(void);

/**
 * @brief Check whether the current reading is valid.
 *
 * This function verifies both the sensor status and
 * timeout conditions.
 *
 * @return true  Valid reading.
 * @return false Invalid reading.
 */
bool Temperature_IsValid(void);

#ifdef __cplusplus
}
#endif

#endif /* TEMPERATURE_H */