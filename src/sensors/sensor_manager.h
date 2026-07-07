#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "sensor_types.h"

class SensorManager
{
public:
    void begin();

    void update();
    
    SensorData getData() const;

private:
    SensorData sensorData;
};


#endif