import time
import random
import socket

def simulate_sensor(sensor_id, ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    while True:
        # Simulate sensor data (random float between 0 and 100)
        data = random.uniform(0, 100)
        message = f"{sensor_id}:{data}"
        sock.sendto(message.encode(), (ip, port))
        print(f"Sensor {sensor_id} sent: {data}")
        time.sleep(random.uniform(0.5, 2.0))  # Random delay between 0.5 and 2 seconds

if __name__ == "__main__":
    IP = "127.0.0.1"  # localhost
    PORT = 12345  # Choose an available port

    # Simulate 3 sensors
    for i in range(3):
        sensor_id = i + 1
        simulate_sensor(sensor_id, IP, PORT)