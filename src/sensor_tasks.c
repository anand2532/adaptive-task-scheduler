#include "sensor_tasks.h"
#include "scheduler.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 12345

static QueueHandle_t sensorQueues[NUM_SENSORS];
static int sock;

void initializeSensorReceiver() {
    struct sockaddr_in server_addr;

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sock, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Sensor receiver initialized and listening on port %d\n", PORT);
}

void sensorTask(void *pvParameters) {
    int sensorId = (int)(intptr_t)pvParameters;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    
    sensorQueues[sensorId] = xQueueCreate(10, sizeof(float));

    while (1) {
        int n = recvfrom(sock, (char *)buffer, BUFFER_SIZE, MSG_DONTWAIT,
                         (struct sockaddr *)&client_addr, &len);
        
        if (n > 0) {
            buffer[n] = '\0';
            int recv_sensor_id;
            float sensorData;
            sscanf(buffer, "%d:%f", &recv_sensor_id, &sensorData);
            
            if (recv_sensor_id == sensorId + 1) {  // +1 because Python script uses 1-based indexing
                xQueueSend(sensorQueues[sensorId], &sensorData, 0);
                printf("Sensor %d received: %f\n", sensorId, sensorData);
                
                // Adjust task priority
                adjustTaskPriority(NULL);
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));  // Small delay to prevent busy-waiting
    }
}

QueueHandle_t getSensorQueue(int sensorId) {
    if (sensorId >= 0 && sensorId < NUM_SENSORS) {
        return sensorQueues[sensorId];
    }
    return NULL;
}