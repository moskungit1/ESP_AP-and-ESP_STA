#include <WiFi.h>
const char* ssid = "ESP32_PBUA";
const char* password = "11501150";

#define IN1 13
#define IN2 12
#define ENA 14

const int speed = 255;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started!");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP Address");
  Serial.println(IP);

  server.begin();
  Serial.println("Server Started!");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client Connect!");

    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.print("Data: ");
        Serial.println(data);

        if (data == "w") {
          Serial.println("Foward");
        } else if (data == "s") {
          Serial.println("Backward");
        } else if (data == "a") {
          Serial.println("TurnLeft");
        } else if (data == "d") {
          Serial.println("Backward");
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}