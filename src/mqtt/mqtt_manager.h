#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class MQTTManager
{
public:

    MQTTManager();

    void begin();

    void update();

    bool connected();

    void publish(const String &payload);

    bool hasNewCommand();
    String getLastCommand();

private:

    WiFiClientSecure wifiClient;

    PubSubClient mqttClient;

    unsigned long reconnectTimer = 0;

    String lastCommand = "";
    bool newCommandReceived = false;

    void callback(
        char* topic, 
        byte* payload, 
        unsigned int length
    );
};

#endif