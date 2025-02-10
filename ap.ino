#include <WiFi.h> 

const char* ssid = "ESP32_Network";
const char* password = "12345678";  

WiFiServer server(80); 

// กำหนดพินควบคุมมอเตอร์
#define ENA 14
#define IN1 13
#define IN2 12
int speed = 150; 

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);  
    server.begin();  // เริ่มต้น TCP Server
    Serial.println("ESP32 Server started.");

    // ตั้งค่าพิน
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

// ฟังก์ชันการเคลื่อนที่
void moveForward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, speed);
}

void moveBackward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
}

void turnRight() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, speed);
}

void turnLeft() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, speed);
}

void stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
}

void loop() {
    WiFiClient client = server.available(); 
    if (client) {
        Serial.println("Client connected!");
        String command = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n') break;
                command += c;
            }
        }

        Serial.println("Received: " + command);

        
        if (command == "W") {
            moveForward();
            Serial.println("Moving Forward");
        } else if (command == "S") {
            moveBackward();
            Serial.println("Moving Backward");
        } else if (command == "A") {
            turnLeft();
            Serial.println("Turning Left");
        } else if (command == "D") {
            turnRight();
            Serial.println("Turning Right");
        } else if (command == "X") {
            stop();
            Serial.println("Stop");
        } else {
            Serial.println("Unknown Command");
        }

        client.println("Command Received: " + command);
        client.stop();
    }
}
