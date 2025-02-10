#include <WiFi.h>

const char* ssid = "ESP32_Network";
const char* password = "12345678";

WiFiServer server(81); 

// กำหนดขามอเตอร์
#define ENB 25
#define IN3 33
#define IN4 32
int speed = 150; 

void setup() {
    Serial.begin(115200);

    
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to ESP32 AP...");
    }
    Serial.println("Connected to ESP32 AP!");

    server.begin(); 
}

void moveForward() {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, speed);
}

void moveBackward() {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
}

void turnRight() {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, speed);
}

void turnLeft() {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, speed);
}

void stopMotors() {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);  
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
            stopMotors();
            Serial.println("Stopping");
        } else {
            Serial.println("Unknown Command");
        }

        client.println("ESP2 Received: " + command);
        client.stop();
    }
}
