// #include <Arduino.h>
// #include <WiFi.h>
// #include <esp_now.h>
// #include <AsyncTCP.h>

// #include "main.h"
// #include "ws.h"
// #include "oled.h"
// #include "bluepill_uart.h"
// #include "pinout.h"

// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");
// const char* ssid = "iPhone von Benedikt";
// const char* password = "gabi1234";
// uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xA5, 0xB6, 0xC7};

// // function declaration
// void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

// void wsSetup() {
//     // Serial.println("Connecting to WiFi...");

//     WiFi.mode(WIFI_STA);
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//     }

//     ws.onEvent(onWsEvent);
//     server.addHandler(&ws);
//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//         request->send(200, "text/plain", "WebSocket server running.");
//     });
//     server.begin();

//     // Serial.println("Servers started!"); 
//     // Serial.println("IP: " + WiFi.localIP().toString());
//     // Serial.println("ESP1 MAC: " + WiFi.macAddress());
// }

// void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
//     if (type == WS_EVT_CONNECT) {
//         ws.textAll("WebSocket client connected");
//         // oledDisplay("WebSocket client connected");
//     } else if (type == WS_EVT_DISCONNECT) {
//         // oledDisplay("WebSocket client disconnected");
//     } else if (type == WS_EVT_DATA) {
//         AwsFrameInfo *info = (AwsFrameInfo*)arg;
//         if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//             data[len] = 0; // Null-terminate the data

//             bluepillUartSend("WS received: " + String((char*)data));
//             ws.textAll("WS received: " + String((char*)data));
//             if(String((char*)data) == "stop") {
//                 run = false;
//             } else if(String((char*)data) == "start") {
//                 run = true;
//             }
//             // oledDisplay((char*)data);
//         }
//     }
// }

// void wsSend(String message) {
//     ws.textAll(message);
// }