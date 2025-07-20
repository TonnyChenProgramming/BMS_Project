#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "Tonny";
const char* password = "38767475";

// Firebase Realtime Database
const char* firebase_host = "batterymanagingsystem-default-rtdb.asia-southeast1.firebasedatabase.app";
String firebase_path = "/esp8266.json";  // Use JSON extension for PUT

// JSON buffer
String uartJsonBuffer = "";

void connectToWiFi() {
  Serial.begin(115200);
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void pushToFirebase(const String& payload) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();  // Accept insecure certs

    HTTPClient http;
    String url = "https://" + String(firebase_host) + firebase_path;

    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PUT(payload);
    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());

    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

void setup() {
  connectToWiFi();

  // UART listener from STM32 — default RX pin (GPIO3)
  Serial.setTimeout(100);  // Set read timeout
}

void loop() {
  if (Serial.available()) {
    uartJsonBuffer = Serial.readStringUntil('\n');  // Read complete line
    uartJsonBuffer.trim();  // Remove whitespace or \r

    if (uartJsonBuffer.startsWith("{") && uartJsonBuffer.endsWith("}")) {
      
      Serial.println("Received JSON:");
      Serial.println(uartJsonBuffer);
      Serial.print("Raw JSON bytes: ");
      //for (size_t i = 0; i < uartJsonBuffer.length(); i++) {
        //Serial.print((int)uartJsonBuffer[i]);
        //Serial.print(" ");
      //}
      Serial.println();
      pushToFirebase(uartJsonBuffer);
    } else {
      Serial.println("Invalid JSON received, ignored.");
    }
  }
}
