#ifndef APP_H
#define APP_H

#include "../logger/logger.h"
#include "../sensors/sensor_manager.h"
#include "../state_machine/state_machine.h"
#include "../wifi/wifi_manager.h"
#include "../mqtt/mqtt_manager.h"

class App
{
public:

    void begin();

    void update();

    void executeCommand(const String &command);

private:

    Logger logger;

    SensorManager sensorManager;

    StateMachine stateMachine;

    WiFiManager wifiManager;

    MQTTManager mqttManager;

    bool valveOpen = false;    // Device state

    bool regenerationRunning = false;

    unsigned long regenerationStartTime = 0;

    String regenerationStatus = "IDLE";

    String regenerationRejectReason = "";

    bool canStartRegeneration(SensorData data);

    String activeAlerts = "";

};

#endif