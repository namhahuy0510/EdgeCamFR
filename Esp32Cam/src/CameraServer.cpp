#include "CameraServer.h"

CameraServer::CameraServer(int port) : _server(port) {}

void CameraServer::initCamera() {
    camera_config_t config;
    // Pin ESP32-CAM AI Thinker
    config.pin_pwdn = 32;
    config.pin_reset = -1;
    config.pin_xclk = 0;
    config.pin_sccb_sda = 26;
    config.pin_sccb_scl = 27;
    config.pin_d7 = 35;
    config.pin_d6 = 34;
    config.pin_d5 = 39;
    config.pin_d4 = 36;
    config.pin_d3 = 21;
    config.pin_d2 = 19;
    config.pin_d1 = 18;
    config.pin_d0 = 5;
    config.pin_vsync = 25;
    config.pin_href = 23;
    config.pin_pclk = 22;

    // Cấu hình an toàn
    config.xclk_freq_hz = 10000000;              // giảm tần số XCLK xuống 10 MHz
    config.pixel_format = PIXFORMAT_JPEG;        // JPEG nhẹ hơn RGB
    config.frame_size   = FRAMESIZE_QQVGA;       // 160x120, cực nhẹ
    config.jpeg_quality = 15;                    // chất lượng thấp hơn, giảm tải
    config.fb_count     = 1;                     // chỉ 1 frame buffer

    config.ledc_timer   = LEDC_TIMER_0;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.fb_location  = CAMERA_FB_IN_PSRAM;    // nếu PSRAM lỗi có thể đổi sang CAMERA_FB_IN_DRAM
    config.grab_mode    = CAMERA_GRAB_WHEN_EMPTY;

    if (esp_camera_init(&config) != ESP_OK) {
        Serial.println("Camera init failed");
        while (true) delay(1000);
    }
}

void CameraServer::start() {
    _server.on("/", HTTP_GET, [this]() { handleStream(); });
    _server.begin();
}

void CameraServer::handleClient() {
    _server.handleClient();
}

void CameraServer::handleStream() {
    WiFiClient client = _server.client();
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    client.print(response);

    while (client.connected()) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Camera capture failed");
            return;
        }
        client.printf("--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n", fb->len);
        client.write(fb->buf, fb->len);
        client.print("\r\n");
        esp_camera_fb_return(fb);
        delay(100);
    }
}
