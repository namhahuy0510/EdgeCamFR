#pragma once
#include <WiFi.h>

class WifiConnection {
public:
    WifiConnection(const char* ssid, const char* password);
    void connect();
    IPAddress getIP();
private:
    const char* _ssid;
    const char* _password;
};
