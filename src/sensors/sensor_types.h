#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H

#include <Arduino.h>

struct SensorData
{
    float flowRate;         // L/min
    float pressure;         // Bar
    float tds;              // ppm
    float saltLevel;        // %
    bool powerAvailable;

    unsigned long timestamp;
};

#endif