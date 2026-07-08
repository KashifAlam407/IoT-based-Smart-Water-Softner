#ifndef CONFIG_H

#define CONFIG_H

#include <Arduino.h>

/************ Device ************/
#define DEVICE_ID           "SOFTENER_001"
#define DEVICE_NAME         "EcoWell Smart Softener"

/************ WiFi ************/
#define WIFI_SSID           "your ssid"
#define WIFI_PASSWORD       "your password"

/************ MQTT ************/
#define MQTT_HOST           "you mqqt host url"
#define MQTT_PORT           8883

#define MQTT_USERNAME   "mqtt username"
#define MQTT_PASSWORD   "mqtt password"

#define MQTT_PUB_TOPIC      "ecowell/softener/data"
#define MQTT_SUB_TOPIC      "ecowell/softener/cmd"

/************ Timing ************/
#define SENSOR_UPDATE_MS    1000
#define MQTT_UPDATE_MS      2000

/*********** Alert Threshold *******/
#define LOW_SALT_THRESHOLD        20
#define HIGH_TDS_THRESHOLD        500
#define LOW_PRESSURE_THRESHOLD    1.0
#define NO_FLOW_THRESHOLD         5.0

#define REGENERATION_REQUIRED_THRESHOLD 30
#endif