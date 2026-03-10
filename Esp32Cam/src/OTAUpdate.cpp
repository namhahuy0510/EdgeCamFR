#include "OTAUpdate.h"

void OTAUpdate::begin() {
    ArduinoOTA.setHostname("esp32cam");
    ArduinoOTA.begin();
    Serial.println("OTA ready");
}

void OTAUpdate::handle() {
    ArduinoOTA.handle();
}
