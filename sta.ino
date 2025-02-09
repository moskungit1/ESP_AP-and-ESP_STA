#include <WiFi.h>

const char* ssid = "ESP32_PBUA";
const char* password = "11501150";

const char* AP_IP = "192.168.4.1";
const int PORT = 80;

WiFiClient client;

#define IN3 33
#define IN4 32
#define ENB 25

const int speed = 255;

void setup() {
  Serial.begin(115200);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("STA IP Address: ");
  Serial.println(WiFi.localIP());


  if (client.connect(AP_IP, PORT)) {
    Serial.println("Connected to AP Server!");
  } else {
    Serial.println("Connection Failed!");
  }
}

void loop() {

  if (!client.connected()) {
    Serial.println("Reconnecting to AP...");
    if (client.connect(AP_IP, PORT)) {
      Serial.println("Reconnected to AP");
    } else {
      Serial.println("Failed to reconnect to AP");
    }
  }

  if (client.connected() && client.available()) {
    String data = client.readStringUntil('\r');
    data.trim();
    Serial.print("Data from AP: ");
    Serial.println(data);


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

void moveForward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  delay(1000);
  stop();
}

void moveBackward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
  delay(1000);
  stop();
}

void turnLeft() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  delay(1000);
  stop();
}

void turnRight() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
  delay(1000);
  stop();
}

void stop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0); 
}
