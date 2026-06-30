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

/******************************************************************************
 * Public API
 ******************************************************************************/

const PumpConfig_t* PumpConfig_Get(PumpId_t pump);

uint8_t PumpConfig_GetCount(void);

#ifdef __cplusplus
}
#endif

#endif