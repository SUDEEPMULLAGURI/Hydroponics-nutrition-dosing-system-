#ifndef PUMP_CONFIG_H
#define PUMP_CONFIG_H

/******************************************************************************
 * File        : pump_config.h
 * Description : Pump Configuration
 * Project     : Smart Hydroponics Controller
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "pump_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Pump Configuration Structure
 ******************************************************************************/

typedef struct
{
    uint8_t gpio;

    bool enabled;

    bool activeHigh;

    const char *name;

} PumpConfig_t;

typedef enum
{
    PUMP_PH_UP,
    PUMP_PH_DOWN,
    PUMP_NUTRIENT_A,
    PUMP_NUTRIENT_B,
    PUMP_NUTRIENT_C,
    PUMP_NUTRIENT_D,
    PUMP_NUTRIENT_E,
    PUMP_NUTRIENT_F,
    PUMP_WATER_FILL,
    PUMP_DRAIN,
    PUMP_COUNT

} PumpId_t;


/******************************************************************************
 * Public API
 ******************************************************************************/

const PumpConfig_t* PumpConfig_Get(PumpId_t pump);

uint8_t PumpConfig_GetCount(void);

#ifdef __cplusplus
}
#endif

#endif