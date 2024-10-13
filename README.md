# Adaptive Task Scheduler for Multi-Sensor Data Fusion

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Prerequisites](#prerequisites)
4. [Project Structure](#project-structure)
5. [Setting Up the Project](#setting-up-the-project)
   - [Cloning the Repository](#cloning-the-repository)
   - [Importing FreeRTOS](#importing-freertos)
6. [Configuration](#configuration)
   - [FreeRTOS Configuration](#freertos-configuration)
   - [Project Configuration](#project-configuration)
7. [Building the Project](#building-the-project)
   - [For Desktop/Simulator](#for-desktopsimulator)
   - [For Embedded Targets](#for-embedded-targets)
8. [Running Tests](#running-tests)
9. [Using the Adaptive Task Scheduler](#using-the-adaptive-task-scheduler)
10. [Customization and Extension](#customization-and-extension)
11. [Troubleshooting](#troubleshooting)
12. [Contributing](#contributing)
13. [License](#license)

## Introduction

The Adaptive Task Scheduler for Multi-Sensor Data Fusion is a real-time embedded software project that demonstrates advanced task scheduling techniques in a multi-sensor environment. It uses FreeRTOS to manage tasks, implement inter-task communication, and showcase adaptive scheduling based on runtime task behavior.

## Features

- Multi-Task Management for handling multiple sensor inputs
- Inter-Task Communication using FreeRTOS queues
- Adaptive Scheduling that adjusts task priorities dynamically
- Resource Management with semaphores
- Simple Data Fusion algorithm
- Configurable for different embedded targets
- Unit tests for core components

## Prerequisites

To build and use this project, you'll need:

- CMake (version 3.12 or higher)
- A C compiler (GCC recommended, version 7.0 or higher)
- Git
- ARM GCC toolchain (for embedded targets)
- FreeRTOS (will be imported as a submodule)
- (Optional) A compatible embedded development board

## Project Structure

```
adaptive-task-scheduler/
├── .gitignore
├── README.md
├── LICENSE
├── CMakeLists.txt
├── src/
│   ├── main.c
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── sensor_tasks.c
│   ├── sensor_tasks.h
│   ├── data_fusion.c
│   ├── data_fusion.h
│   ├── config.h
│   └── FreeRTOSConfig.h
├── lib/
│   └── FreeRTOS/  (submodule)
├── tests/
│   ├── test_scheduler.c
│   └── test_data_fusion.c
└── cmake/
    └── arm-none-eabi-toolchain.cmake
```

## Setting Up the Project

### Cloning the Repository

1. Open a terminal and navigate to your desired directory.
2. Clone the repository:
   ```
   git clone https://github.com/yourusername/adaptive-task-scheduler.git
   cd adaptive-task-scheduler
   ```

### Importing FreeRTOS

FreeRTOS is included as a Git submodule. To import it:

1. Initialize the submodule:
   ```
   git submodule init
   ```

2. Update the submodule to fetch FreeRTOS:
   ```
   git submodule update
   ```

This will clone the FreeRTOS kernel into the `lib/FreeRTOS` directory.

## Configuration

### FreeRTOS Configuration

The FreeRTOS configuration is defined in `src/FreeRTOSConfig.h`. You can modify this file to adjust FreeRTOS settings according to your needs. Some key configurations include:

- `configUSE_PREEMPTION`: Enables preemptive scheduler
- `configCPU_CLOCK_HZ`: CPU clock frequency
- `configTICK_RATE_HZ`: RTOS tick rate
- `configMAX_PRIORITIES`: Maximum number of priorities
- `configMINIMAL_STACK_SIZE`: Minimal stack size for tasks

### Project Configuration

Project-specific configurations are in `src/config.h`. Here you can adjust:

- `NUM_SENSORS`: Number of simulated sensors
- `SENSOR_PERIOD_MS`: Sensor sampling period
- `RUNTIME_THRESHOLD`: Threshold for task runtime before priority adjustment

## Building the Project

### For Desktop/Simulator

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Run CMake:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   make
   ```

### For Embedded Targets

1. Ensure you have the ARM GCC toolchain installed.

2. Create a build directory:
   ```
   mkdir build_arm
   cd build_arm
   ```

3. Run CMake with the ARM toolchain file:
   ```
   cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-toolchain.cmake ..
   ```

4. Build the project:
   ```
   make
   ```

## Running Tests

After building the project, you can run the tests:

```
make test
```

This will execute the unit tests defined in the `tests/` directory.

## Using the Adaptive Task Scheduler

The main application creates multiple sensor tasks and a data fusion task. To use it:

1. For desktop/simulator: Run the executable generated in the build directory.
   ```
   ./AdaptiveTaskScheduler
   ```

2. For embedded targets: Flash the generated binary to your development board using appropriate tools for your hardware.

The application will start the FreeRTOS scheduler, create sensor tasks, and begin the adaptive scheduling and data fusion process.

## Customization and Extension

To customize or extend the project:

1. Add new sensor types: Modify `sensor_tasks.c` to include different sensor behaviors.
2. Enhance data fusion: Improve the algorithm in `data_fusion.c`.
3. Adjust scheduling behavior: Modify the adaptive algorithm in `scheduler.c`.
4. Add new tasks: Create new task functions and add them to `main.c`.

## Troubleshooting

- If CMake fails to find FreeRTOS, ensure the submodule is correctly initialized and updated.
- For compilation errors related to FreeRTOS, check that `FreeRTOSConfig.h` is correctly set up for your target.
- If the scheduler behaves unexpectedly, review the priority settings and adaptive algorithm in `scheduler.c`.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.