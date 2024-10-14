# Adaptive Task Scheduler Software Architecture Diagram

## Components

1. Main Application (main.c)
2. Scheduler (scheduler.c/h)
3. Sensor Tasks (sensor_tasks.c/h)
4. Data Fusion (data_fusion.c/h)
5. Configuration (config.h)
6. FreeRTOS Kernel
7. POSIX Thread (Receiver Thread)

## Diagram Structure

[Main Application]
  |
  ├─ [Scheduler]
  |    |
  |    └─ (adjustTaskPriority function)
  |
  ├─ [Sensor Tasks]
  |    |
  |    ├─ (POSIX Receiver Thread)
  |    ├─ (Sensor Task 1)
  |    ├─ (Sensor Task 2)
  |    └─ (Sensor Task 3)
  |
  └─ [Data Fusion]
       |
       └─ (Data Fusion Task)

## Data Flow and Variable Scope

1. Configuration (config.h)
   - Scope: Global
   - Variables: NUM_SENSORS, SENSOR_PERIOD_MS, RUNTIME_THRESHOLD
   - Accessed by: All components

2. Main Application (main.c)
   - Creates and initializes all tasks
   - Starts FreeRTOS scheduler
   - No specific variables, orchestrates the system

3. Scheduler (scheduler.c/h)
   - Function: adjustTaskPriority
   - Scope: Global (can be called by any task)
   - Variables: 
     - currentPriority (local to function)
     - RUNTIME_THRESHOLD (from config.h)

4. Sensor Tasks (sensor_tasks.c/h)
   - Components:
     a. POSIX Receiver Thread
     b. Sensor Tasks (FreeRTOS tasks)
   - Variables:
     - sensorQueues[NUM_SENSORS] (static, file scope)
     - latestSensorData[NUM_SENSORS] (static, file scope)
     - sock (static, file scope)
     - keep_running (static, volatile, file scope)
   - Functions:
     - receiver_thread (POSIX thread function)
     - sensorTask (FreeRTOS task function)
     - initializeSensorReceiver (called from main)
     - getSensorQueue (global, used by Data Fusion)
     - getLatestSensorData (global, used by Data Fusion)

5. Data Fusion (data_fusion.c/h)
   - Function: dataFusionTask (FreeRTOS task)
   - Variables:
     - fusedData (local to dataFusionTask)
     - sensorData (local to dataFusionTask)
   - Accesses: 
     - getSensorQueue (from sensor_tasks.h)
     - getLatestSensorData (from sensor_tasks.h)

## Interactions and Data Flow

1. Main Application:
   - Initializes FreeRTOS
   - Creates Sensor Tasks, Data Fusion Task, and Receiver Init Task
   - Starts FreeRTOS scheduler

2. Receiver Thread:
   - Runs continuously in background
   - Receives UDP packets from Python simulator
   - Parses sensor data
   - Updates latestSensorData array
   - Sends data to appropriate sensorQueue

3. Sensor Tasks:
   - Wait for data in their respective queues
   - Process received sensor data
   - Call adjustTaskPriority to adapt their priority

4. Data Fusion Task:
   - Runs periodically
   - Retrieves latest sensor data using getLatestSensorData
   - Fuses data from all sensors
   - Outputs fused result

5. Scheduler:
   - adjustTaskPriority function is called by Sensor Tasks
   - Modifies task priorities based on runtime behavior

## Key Points

- The POSIX Receiver Thread operates outside of FreeRTOS, handling real-time data reception.
- Sensor data is passed from the Receiver Thread to Sensor Tasks via FreeRTOS queues.
- The Data Fusion Task accesses sensor data through getter functions, not directly.
- The Scheduler's adjustTaskPriority function is called by tasks to adapt their priorities.
- Configuration parameters in config.h affect the behavior of multiple components.

This diagram illustrates the modular structure of the software, the separation of concerns between components, and the flow of data from sensor input to fused output, while highlighting the adaptive nature of the task scheduling.