#include "sensor_manager.h"

void SensorManager::begin()
{
    randomSeed(millis());   // it initilizes the random number generator

    sensorData.flowRate = 15.0;
    sensorData.pressure = 2.5;
    sensorData.tds = 180;
    sensorData.saltLevel = 100;
    sensorData.powerAvailable = true;
}

void SensorManager::update()
{
    // sensorData.flowRate = random(120, 200) / 10.0;
    sensorData.flowRate = 2.0;
    // sensorData.pressure = random(20, 40) / 10.0;
    sensorData.pressure = 5;
    sensorData.tds = random(150, 250);

    // sensorData.saltLevel -= 0.05;

    // if(sensorData.saltLevel < 0)
    //     sensorData.saltLevel = 100;

    sensorData.saltLevel = 40;

    sensorData.timestamp = millis();
}

SensorData SensorManager::getData() const
{
    return sensorData;
}