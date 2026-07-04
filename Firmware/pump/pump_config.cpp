/******************************************************************************
 * File        : pump_config.cpp
 ******************************************************************************/

#include "pump_config.h"
#include "pins.h"

/******************************************************************************
 * Pump Configuration Table
 ******************************************************************************/

static const PumpConfig_t g_pumpConfig[PUMP_COUNT] =
{
    /* PUMP_PH_UP */

    {
        .gpio       = RELAY_PH_UP_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "pH Up"
    },

    /* PUMP_PH_DOWN */

    {
        .gpio       = RELAY_PH_DOWN_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "pH Down"
    },
     /* PUMP_NUTRIENT_A */
    {
        .gpio       = RELAY_PH_DOWN_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient A"
    },
     /* PUMP_NUTRIENT_B */
    {
        .gpio       = RELAY_PH_DOWN_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient B"
    },
     /* PUMP_NUTRIENT_C */
    {
        .gpio       = RELAY_PH_DOWN_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient C"
    },
    
    

    /* PUMP_NUTRIENT_D */

    {
        .gpio       = RELAY_NUTRIENT_A_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient D"
    },

    /* PUMP_NUTRIENT_E */

    {
        .gpio       = RELAY_NUTRIENT_B_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient E"
    },
    
        /* PUMP_NUTRIENT_F */

    {
        .gpio       = RELAY_NUTRIENT_B_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Nutrient F"
    },

    /* PUMP_WATER_FILL */

    {
        .gpio       = RELAY_WATER_PUMP_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Water Fill"
    },

    /* PUMP_DRAIN */

    {
        .gpio       = RELAY_DRAIN_PUMP_PIN,
        .enabled    = true,
        .activeHigh = true,
        .name       = "Drain"
    }
};

/******************************************************************************
 * Get Configuration
 ******************************************************************************/

const PumpConfig_t* PumpConfig_Get(PumpId_t pump)
{
    if (pump >= PUMP_COUNT)
    {
        return nullptr;
    }

    return &g_pumpConfig[pump];
}

/******************************************************************************
 * Number of Pumps
 ******************************************************************************/

uint8_t PumpConfig_GetCount(void)
{
    return PUMP_COUNT;
}
