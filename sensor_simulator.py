import time
import random
import socket
import threading

def simulate_sensor(sensor_id, interval, sock, ip, port):
    while True:
        data = random.uniform(0, 100)
        message = f"{sensor_id}:{data:.2f}"
        sock.sendto(message.encode(), (ip, port))
        print(f"Sensor {sensor_id} sent: {data:.2f}")
        time.sleep(interval)

if __name__ == "__main__":
    IP = "127.0.0.1"
    PORT = 12345

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Define different intervals for each sensor
    sensor_intervals = [0.5, 1, 1.5]  # Sensor 1: 0.5s, Sensor 2: 1s, Sensor 3: 1.5s

    threads = []
    for i in range(3):
        sensor_id = i + 1
        interval = sensor_intervals[i]
        thread = threading.Thread(target=simulate_sensor, args=(sensor_id, interval, sock, IP, PORT))
        thread.start()
        threads.append(thread)

    try:
        for thread in threads:
            thread.join()
    except KeyboardInterrupt:
        print("Stopping sensor simulation")
    finally:
        sock.close()