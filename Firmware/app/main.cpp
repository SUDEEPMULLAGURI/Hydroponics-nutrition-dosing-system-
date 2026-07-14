/******************************************************************************
 * File        : main.cpp
 * Description : Main Application
 * Project     : Smart Hydroponics Controller
 * Author      : Sudeep Mullaguri
 ******************************************************************************/

#include <Arduino.h>

#include "system.h"

/******************************************************************************
 * Arduino Setup
 ******************************************************************************/

void setup(void)
{
    if(!System_Init())
    {
        while(1)
        {
            /* Fatal initialization error */

            delay(100);
        }
    }
}

/******************************************************************************
 * Arduino Main Loop
 ******************************************************************************/

void loop(void)
{
    System_Update();
}

