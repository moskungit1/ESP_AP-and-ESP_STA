#include <WiFi.h>

const char* ssid = "ESP32-PBUA";
const char* password = "11501150";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Connect to Server!");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Connected client");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        data.trim();
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
    Serial.println("Disconeect from Client!");
  }
}
