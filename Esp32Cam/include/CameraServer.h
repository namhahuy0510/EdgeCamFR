#pragma once
#include "esp_camera.h"
#include <WebServer.h>

class CameraServer {
public:
    CameraServer(int port = 80);
    void initCamera();
    void start();
    void handleClient();
private:
    WebServer _server;
    void handleStream();
};
