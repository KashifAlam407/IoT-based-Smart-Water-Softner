#include "state_machine.h"
#include "../config/config.h"

void StateMachine::begin()
{
    currentState = DeviceState::MONITORING;
}

void StateMachine::update(const SensorData &data)
{
    // If already regenerating, don't change the state
    if (currentState == DeviceState::REGENERATING)
    {
        return;
    }

    if (!data.powerAvailable)
    {
        currentState = DeviceState::FAULT;
    }
    else if (data.saltLevel < REGENERATION_REQUIRED_THRESHOLD)
    {
        currentState = DeviceState::REGENERATION_REQUIRED;
    }
    else
    {
        currentState = DeviceState::MONITORING;
    }
}

void StateMachine::setState(DeviceState state)
{
    currentState = state;
}

DeviceState StateMachine::getState() const
{
    return currentState;
}