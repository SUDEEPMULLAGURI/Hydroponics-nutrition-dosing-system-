#ifndef PINS_H
#define PINS_H

/******************************************************************************
 * File        : pins.h
 * Description : Hardware Pin Definitions
 * Project     : Smart Hydroponics Controller
 *
 * This file contains ONLY GPIO assignments.
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * Analog Sensor Inputs
 ******************************************************************************/

// pH Sensor
#define PH_SENSOR_PIN              34

// EC Sensor
#define EC_SENSOR_PIN              35

// Water Temperature (DS18B20)
#define WATER_TEMP_PIN             4

// Water Level Sensor (Analog)
#define WATER_LEVEL_PIN            32

/******************************************************************************
 * Relay Outputs
 ******************************************************************************/

#define RELAY_PH_UP_PIN            16
#define RELAY_PH_DOWN_PIN          17

#define RELAY_NUTRIENT_A_PIN       18
#define RELAY_NUTRIENT_B_PIN       19
#define RELAY_NUTRIENT_C_PIN       19
#define RELAY_NUTRIENT_D_PIN       19
#define RELAY_NUTRIENT_E_PIN       19
#define RELAY_NUTRIENT_F_PIN       19


#define RELAY_WATER_PUMP_PIN       21
#define RELAY_DRAIN_PUMP_PIN       22

/******************************************************************************
 * Status LEDs
 ******************************************************************************/

#define LED_STATUS_PIN             2

/******************************************************************************
 * User Interface
 ******************************************************************************/

#define BUTTON_RESET_PIN           0

/******************************************************************************
 * I2C Bus
 ******************************************************************************/

#define I2C_SDA_PIN                25
#define I2C_SCL_PIN                26

/******************************************************************************
 * SPI Bus (Reserved)
 ******************************************************************************/

#define SPI_MOSI_PIN               23
#define SPI_MISO_PIN               19
#define SPI_SCK_PIN                18
#define SPI_CS_PIN                 5

/******************************************************************************
 * UART
 ******************************************************************************/

#define UART_RX_PIN                3
#define UART_TX_PIN                1

#ifdef __cplusplus
}
#endif

#endif // PINS_H