#include "WifiConnection.h"

WifiConnection::WifiConnection(const char* ssid, const char* password)
: _ssid(ssid), _password(password) {}

void WifiConnection::connect() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

IPAddress WifiConnection::getIP() {
    return WiFi.localIP();
}
