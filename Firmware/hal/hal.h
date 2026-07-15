/******************************************************************************
 * @file    hal.h
 * @brief   Hardware Abstraction Layer (HAL) Master Interface
 *
 * ----------------------------------------------------------------------------
 * Hydroponics Nutrition Dosing System
 * ----------------------------------------------------------------------------
 *
 * This file is the main entry point for the Hardware Abstraction Layer.
 *
 * Responsibilities:
 *  - Initialize all HAL peripherals
 *  - Provide firmware-wide HAL status
 *  - Abstract the underlying hardware implementation
 *
 * Application code must only include this file and should never access
 * Arduino APIs directly.
 *
 ******************************************************************************/

#ifndef HAL_H
#define HAL_H

#include "hal_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * HAL Version
 ******************************************************************************/

#define HAL_VERSION_MAJOR      1
#define HAL_VERSION_MINOR      0
#define HAL_VERSION_PATCH      0

/******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 * @brief Initialize the complete Hardware Abstraction Layer.
 *
 * Initializes every HAL peripheral module in the correct order.
 *
 * Initialization sequence:
 *
 * GPIO
 * ADC
 * PWM
 * UART
 * Timer
 * Flash
 * Watchdog
 *
 * @return HAL_OK if successful.
 */
HAL_Status_t HAL_Init(void);

/**
 * @brief Periodic HAL update.
 *
 * Called every scheduler cycle.
 */
void HAL_Update(void);

/**
 * @brief Returns true when HAL has been initialized.
 */
HAL_Bool_t HAL_IsInitialized(void);

/**
 * @brief Get HAL version numbers.
 */
uint8_t HAL_GetMajorVersion(void);

uint8_t HAL_GetMinorVersion(void);

uint8_t HAL_GetPatchVersion(void);

#ifdef __cplusplus
}
#endif

#endif
