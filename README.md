# adaptive-task-scheduler
 Adaptive Task Scheduler for Multi-Sensor Data Fusion
 
# Adaptive Task Scheduler for Multi-Sensor Data Fusion

This project implements an adaptive task scheduler for a multi-sensor system, optimizing CPU usage and power consumption based on sensor priorities and data rates. It's built using FreeRTOS and demonstrates effective use of real-time operating system features.

## Key Features

1. Multi-Task Management: Handles multiple sensor tasks with different priorities and periods.
2. Inter-Task Communication: Uses FreeRTOS queues for efficient data passing between tasks.
3. Adaptive Scheduling: Dynamically adjusts task priorities based on their execution patterns.
4. Resource Management: Employs semaphores to protect shared resources.
5. Data Fusion: Implements a simple data fusion algorithm combining data from multiple sensors.

## Prerequisites

- CMake (version 3.12 or higher)
- A C compiler compatible with your target platform
- FreeRTOS source code (included as a submodule)

## Building the Project

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/adaptive-task-scheduler.git
   cd adaptive-task-scheduler
   ```

2. Initialize and update the FreeRTOS submodule:
   ```
   git submodule init
   git submodule update
   ```

3. Create a build directory and run CMake:
   ```
   mkdir build
   cd build
   cmake ..
   ```

4. Build the project:
   ```
   make
   ```

## Running the Project

After building, you can run the project on your target hardware or simulator. The exact process will depend on your specific setup.

## Running Tests

To run the tests, use the following command from the build directory:

```
make test
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.