#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiManager
{
public:

    void begin();

    void update();

    bool isConnected();

private:

    unsigned long reconnectTimer = 0;    // it stores last reconnect time
};

#endif