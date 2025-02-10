import socket
import threading

def send_command(ip, port, command):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((ip, port))
        sock.sendall(command.encode())
        response = sock.recv(1024)
        print(f"Response from {ip}: {response.decode()}")
        sock.close()
    except Exception as e:
        print(f"Error with {ip}: {e}")


esp1_ip = "192.168.4.1"  
esp1_port = 80

esp2_ip = "192.168.4.2"  
esp2_port = 81

while True:
    command = input("Enter command (W: forward, S: backward, X: stop, Q: quit): ").strip().upper()

    if command == "Q":
        print("Exiting program...")
        break

    if command in ["W", "S", "X", "A", "D"]:
        thread1 = threading.Thread(target=send_command, args=(esp1_ip, esp1_port, command))
        thread2 = threading.Thread(target=send_command, args=(esp2_ip, esp2_port, command))

        thread1.start()
        thread2.start()

        thread1.join()
        thread2.join()
    else:
        print("Invalid command. Please enter W, S, X, A, D, or Q.")
