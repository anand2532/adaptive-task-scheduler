#include "sensor_tasks.h"
#include "scheduler.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>

#define BUFFER_SIZE 1024
#define PORT 12345

static QueueHandle_t sensorQueues[NUM_SENSORS];
static float latestSensorData[NUM_SENSORS];
static int sock;
static volatile int keep_running = 1;

void* receiver_thread(void* arg) {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    printf("Receiver thread started\n");

    while (keep_running) {
        printf("Receiver thread: Waiting for data...\n");
        int n = recvfrom(sock, (char *)buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &len);
        
        if (n > 0) {
            buffer[n] = '\0';
            printf("Receiver thread: Received raw data: %s\n", buffer);

            int recv_sensor_id;
            float sensorData;
            if (sscanf(buffer, "%d:%f", &recv_sensor_id, &sensorData) == 2) {
                printf("Receiver thread: Parsed data - Sensor ID: %d, Value: %f\n", recv_sensor_id, sensorData);
                if (recv_sensor_id >= 1 && recv_sensor_id <= NUM_SENSORS) {
                    latestSensorData[recv_sensor_id - 1] = sensorData;
                    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                    if (xQueueSendFromISR(sensorQueues[recv_sensor_id - 1], &sensorData, &xHigherPriorityTaskWoken) == pdPASS) {
                        printf("Receiver thread: Data sent to queue for Sensor %d\n", recv_sensor_id);
                    } else {
                        printf("Receiver thread: Failed to send data to queue for Sensor %d\n", recv_sensor_id);
                    }
                    if (xHigherPriorityTaskWoken) {
                        sched_yield();
                    }
                } else {
                    printf("Receiver thread: Invalid sensor ID: %d\n", recv_sensor_id);
                }
            } else {
                printf("Receiver thread: Invalid data format received: %s\n", buffer);
            }
        } else if (n < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                perror("Receiver thread: recvfrom failed");
            }
        } else {
            printf("Receiver thread: No data received\n");
        }

        usleep(10000);  // 10ms
    }

    printf("Receiver thread exiting\n");
    return NULL;
}

void initializeSensorReceiver() {
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, receiver_thread, NULL) != 0) {
        perror("Failed to create receiver thread");
        exit(EXIT_FAILURE);
    }

    printf("Sensor receiver initialized and listening on port %d\n", PORT);
}

void sensorTask(void *pvParameters) {
    int sensorId = (int)(intptr_t)pvParameters;
    float receivedData;

    printf("Sensor task %d started\n", sensorId);

    while (1) {
        if (xQueueReceive(sensorQueues[sensorId], &receivedData, portMAX_DELAY) == pdTRUE) {
            printf("Sensor task %d: Received data: %f\n", sensorId, receivedData);
            
            // Adjust task priority
            adjustTaskPriority(NULL);
        }
    }
}

QueueHandle_t getSensorQueue(int sensorId) {
    if (sensorId >= 0 && sensorId < NUM_SENSORS) {
        return sensorQueues[sensorId];
    }
    return NULL;
}

float getLatestSensorData(int sensorId) {
    if (sensorId >= 0 && sensorId < NUM_SENSORS) {
        return latestSensorData[sensorId];
    }
    return 0.0f;
}

void createSensorQueues() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        sensorQueues[i] = xQueueCreate(1, sizeof(float));
        if (sensorQueues[i] == NULL) {
            printf("Failed to create queue for Sensor %d\n", i);
            exit(EXIT_FAILURE);
        }
        printf("Created queue for Sensor %d\n", i);
        latestSensorData[i] = 0.0f;
    }
}