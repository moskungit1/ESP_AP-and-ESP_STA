import socket
import time

ESP32_AP_IP = "192.168.4.1"
PORT = 80

socket_ap = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    socket_ap.connect((ESP32_AP_IP, PORT))
    print("Connected to ESP32 (AP)")
except Exception as e:
    print("Failed to connect to AP:", e)
    exit()

while True:
    data = input("Enter data to send (w/a/s/d): ")
    if data.lower() == 'exit':
        break

    try:
        socket_ap.send((data + '\r').encode())  # Send the data with carriage return
        print(f"Data sent: {data}")
    except Exception as e:
        print("Error sending to AP:", e)

    time.sleep(0.1)  # Reduced delay to minimize lag

socket_ap.close()