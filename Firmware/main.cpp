#include <Arduino.h>

#include "temperature.h"

TemperatureSensor tempSensor;

void setup()
{
    Serial.begin(115200);

    tempSensor.begin();
}

void loop()
{
    tempSensor.update();

    if (tempSensor.isValid())
    {
        Serial.print("Temperature : ");

        Serial.print(tempSensor.getTemperature());

        Serial.println(" C");
    }
    else
    {
        Serial.println("Temperature Sensor Error");
    }

    delay(1000);
}
