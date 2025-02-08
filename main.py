import socket
import time

ESP32_AP_IP = "192.168.4.1"
ESP32_STA_IP = "192.168.4.2"  # ใช้ IP ของ STA ให้ถูกต้อง
PORT = 80

socket_ap = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_sta = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    socket_ap.connect((ESP32_AP_IP, PORT))
    print("Connected to ESP32 (AP)")
except Exception as e:
    print("Failed to connect to AP:", e)

try:
    socket_sta.connect((ESP32_STA_IP, PORT))  # แก้ให้ใช้ IP ของ STA
    print("Connected to ESP32 (STA)")
except Exception as e:
    print("Failed to connect to STA:", e)

while True:
    data = input("Enter data to send: ")
    if data.lower() == 'exit':
        break

    try:
        socket_ap.send((data + '\r').encode())
    except Exception as e:
        print("Error sending to AP:", e)

    try:
        socket_sta.send((data + '\r').encode())
    except Exception as e:
        print("Error sending to STA:", e)

    time.sleep(1)

socket_ap.close()
socket_sta.close()