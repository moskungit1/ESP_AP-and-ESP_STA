#include <WiFi.h>

const char* ssid = "ESP32_PBUA";
const char* password = "11501150";

#define IN1 13
#define IN2 12
#define ENA 14

const int speed = 255;  // ความเร็ว (255 = 100% ความเร็วสูงสุด)

WiFiServer server(80);
WiFiClient staClient; // Client connection to the STA

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // ตั้งค่าการควบคุม PWM (ความเร็ว)
  analogWrite(ENA, speed);   // ใช้ analogWrite สำหรับ PWM

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started!");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  server.begin();
  Serial.println("Server Started!");

  // Connect to the STA
  if (staClient.connect("192.168.4.2", 80)) {
    Serial.println("Connected to STA");
  } else {
    Serial.println("Failed to connect to STA");
  }
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client Connected!");

    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.print("Data from client: ");
        Serial.println(data);

        // Forward the data to the STA (motor control commands)
        if (staClient.connected()) {
          staClient.print(data + '\r');
          Serial.println("Data sent to STA");
        } else {
          Serial.println("STA not connected!");
        }

        // Execute motor commands on the AP side
        if (data == "w") {
          moveForward();
        } else if (data == "s") {
          moveBackward();
        } else if (data == "a") {
          turnLeft();
        } else if (data == "d") {
          turnRight();
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected");
  }

  // Reconnect to STA if disconnected
  if (!staClient.connected()) {
    Serial.println("Reconnecting to STA...");
    if (staClient.connect("192.168.4.2", 80)) {
      Serial.println("Reconnected to STA");
    } else {
      Serial.println("Failed to reconnect to STA");
    }
  }
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);  // ใช้ analogWrite สำหรับ PWM
  delay(1000);
  stop();
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);  // ใช้ analogWrite สำหรับ PWM
  delay(1000);
  stop();
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);  // ใช้ analogWrite สำหรับ PWM
  delay(250);
  stop();
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);  // ใช้ analogWrite สำหรับ PWM
  delay(250);
  stop();
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);  // ปิด PWM
}
