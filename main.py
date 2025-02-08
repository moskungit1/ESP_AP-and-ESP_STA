import socket
import time

ESP32_AP_IP = "192.168.4.1"
ESP32_STA_IP = "192.168.4.2"
PORT = 80

socket_ap = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
socket_sta = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

socket_ap.connect((ESP32_AP_IP, PORT))
print("Connect to ESP32 (AP)")
socket_sta.connect((ESP32_AP_IP, PORT))
print("Connect to ESP32 (STA)")

while True:
    data = input("Enter data to send: ")
    if data.lower() == 'exit':
        break

    socket_ap.send((data + '\r').encode())
    socket_sta.send((data + '\r').encode())
    time.sleep(1)
    
socket_ap.close()
socket_sta.close()
