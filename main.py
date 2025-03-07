import socket
import time

ESP32_IP = "192.168.4.1"
PORT = 80

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
client_socket.connect((ESP32_IP, PORT))
print("Connected to ESP32")

while True:
    data_to_send = input("Enter data to send: ")

    if data_to_send.lower() == 'exit':
        break

    client_socket.send((data_to_send + '\r').encode())
    time.sleep(1)

client_socket.close()
print("Connection closed")
