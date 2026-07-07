#include "mqtt_manager.h"
#include "../config/config.h"

MQTTManager::MQTTManager() : mqttClient(wifiClient)   // before the constructor starts, create mqttClient using wifiClient
{
}

void MQTTManager::begin()
{
    wifiClient.setInsecure();
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    mqttClient.setCallback(
        [this](char* topic, byte* payload, unsigned int length)
        {
            this->callback(topic, payload, length);
        }
    );
}

void MQTTManager::update()
{
    if (!mqttClient.connected())
    {
        if (millis() - reconnectTimer > 5000)
        {
            reconnectTimer = millis();
            
            Serial.println("Connecting to HiveMQ...");

            if(mqttClient.connect(
                DEVICE_ID, 
                MQTT_USERNAME, 
                MQTT_PASSWORD))
            {
                Serial.println("MQTT Connected");
                
                mqttClient.subscribe(MQTT_SUB_TOPIC);

                Serial.println("Subscribed to command topic");
            }
            else
            {
                Serial.println("MQTT Failed : ");
                Serial.println(mqttClient.state());
            }
        }
    }

    mqttClient.loop();   // this funciton keep mqtt alive without this mqtt disconnets
}

bool MQTTManager::connected()
{
    return mqttClient.connected();
}

void MQTTManager::publish(const String &payload)
{
    mqttClient.publish(MQTT_PUB_TOPIC, payload.c_str());
}

bool MQTTManager::hasNewCommand()
{
    return newCommandReceived;
}

String MQTTManager::getLastCommand()
{
    newCommandReceived = false;

    return lastCommand;
}

void MQTTManager::callback(
    char* topic,
    byte* payload,
    unsigned int length)
{
    Serial.print("Topic : ");
    Serial.println(topic);

    String message = "";

    for(unsigned int i=0;i<length;i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Message : ");
    Serial.println(message);

    lastCommand = message;

    newCommandReceived = true;
}