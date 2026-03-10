#include <Arduino.h>
#include "WifiConnection.h"
#include "CameraServer.h"
#include "OTAUpdate.h"

const char* ssid = "TP-LINK_0F54";
const char* password = "68377038";

WifiConnection wifi(ssid, password);
CameraServer camServer(80);
OTAUpdate ota;

void setup() {
  Serial.begin(115200);
  wifi.connect();
  camServer.initCamera();
  camServer.start();
  ota.begin();
}

void loop() {
  camServer.handleClient();
  ota.handle();
}
