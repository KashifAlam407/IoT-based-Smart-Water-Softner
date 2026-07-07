#include "wifi_manager.h"
#include "../config/config.h"

void WiFiManager::begin()
{
    WiFi.mode(WIFI_STA);   // station mode, connect to router, hotspot mode

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // start connecting, returns: WL_CONNECTED or Disconnected
}

void WiFiManager::update()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    if (millis() - reconnectTimer > 5000)  // we reconnect every 5 sec
    {
        reconnectTimer = millis();

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
}

bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}