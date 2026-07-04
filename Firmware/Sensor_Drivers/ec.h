#ifndef EC_H
#define EC_H

#include <stdint.h>
#include <stdbool.h>
#include "sensor_types.h"

bool EC_Init(void);

bool EC_Update(void);

float EC_GetValue(void);

float EC_GetVoltage(void);

SensorStatus_t EC_GetStatus(void);

bool EC_IsValid(void);

void EC_SetCalibration(float slope, float offset);

#endif