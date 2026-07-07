#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "../sensors/sensor_types.h"

enum class DeviceState
{
    IDLE,
    MONITORING,
    REGENERATION_REQUIRED,
    REGENERATING,
    FAULT
};

class StateMachine
{
public:

    void begin();

    void update(const SensorData &data);

    DeviceState getState() const;

    void setState(DeviceState state);

private:

    DeviceState currentState;
};

#endif