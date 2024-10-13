# Adaptive Task Scheduler for Multi-Sensor Data Fusion

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Dependencies](#dependencies)
4. [Setup and Installation](#setup-and-installation)
5. [Building the Project](#building-the-project)
6. [Running the Project](#running-the-project)
7. [Testing](#testing)
8. [Project Components](#project-components)
9. [Recent Changes and Troubleshooting](#recent-changes-and-troubleshooting)
10. [Contributing](#contributing)
11. [License](#license)

## Introduction

This project implements an adaptive task scheduler for a multi-sensor system, optimizing CPU usage and power consumption based on sensor priorities and data rates. It uses FreeRTOS to manage tasks, implement inter-task communication, and showcase adaptive scheduling based on runtime task behavior.

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
│   └── config.h
├── lib/
│   ├── FreeRTOS/  (submodule)
│   └── Unity/     (submodule)
├── tests/
│   ├── test_main.c
│   ├── test_scheduler.c
│   └── test_data_fusion.c
└── cmake/
    └── arm-none-eabi-toolchain.cmake
```

## Dependencies

- CMake (version 3.12 or higher)
- GCC compiler
- FreeRTOS (included as a submodule)
- Unity (included as a submodule for testing)

## Setup and Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/adaptive-task-scheduler.git
   cd adaptive-task-scheduler
   ```

2. Initialize and update the submodules:
   ```
   git submodule init
   git submodule update
   ```

## Building the Project

1. Create a build directory:
   ```
   mkdir build && cd build
   ```

2. Run CMake:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   make
   ```

This will create two executables:
- `AdaptiveTaskScheduler`: The main project executable
- `run_tests`: The test executable

## Running the Project

To run the main program:
```
./AdaptiveTaskScheduler
```

## Testing

To run the tests:
```
./run_tests
```

For formatted test output, create a `run_tests.sh` script with the following content:

```bash
#!/bin/bash

output=$(./run_tests)

total_tests=$(echo "$output" | grep -oP '\d+(?= Tests)')
failed_tests=$(echo "$output" | grep -oP '\d+(?= Failures)')
ignored_tests=$(echo "$output" | grep -oP '\d+(?= Ignored)')
passed_tests=$((total_tests - failed_tests - ignored_tests))

echo "TEST RESULTS"
echo "============"
echo "Total Tests: $total_tests"
echo "Passed:      $passed_tests"
echo "Failed:      $failed_tests"
echo "Ignored:     $ignored_tests"
echo ""
echo "DETAILS"
echo "======="
echo "$output" | sed -n '/^test_/,/^$/p'

if [ "$failed_tests" -eq 0 ]; then
    echo ""
    echo "OVERALL RESULT: PASSED"
else
    echo ""
    echo "OVERALL RESULT: FAILED"
fi
```

Make it executable and run:
```
chmod +x run_tests.sh
./run_tests.sh
```

## Project Components

1. **Scheduler (scheduler.c, scheduler.h)**: 
   - Implements the adaptive scheduling algorithm
   - Manages task priorities dynamically

2. **Sensor Tasks (sensor_tasks.c, sensor_tasks.h)**:
   - Simulates multiple sensor inputs
   - Sends data to the data fusion task

3. **Data Fusion (data_fusion.c, data_fusion.h)**:
   - Combines data from multiple sensors
   - Implements a simple fusion algorithm

4. **Main Program (main.c)**:
   - Sets up FreeRTOS tasks
   - Initializes the scheduler and starts the FreeRTOS scheduler

5. **Configuration (config.h)**:
   - Contains project-wide configuration parameters

6. **Tests**:
   - test_main.c: Main entry point for tests
   - test_scheduler.c: Tests for the scheduler component
   - test_data_fusion.c: Tests for the data fusion component

## Recent Changes and Troubleshooting

1. **CMakeLists.txt Updates**:
   - Added FreeRTOS as a static library
   - Included Unity for testing
   - Separated main executable and test executable builds

2. **Test Files Restructuring**:
   - Removed duplicate main(), setUp(), and tearDown() functions
   - Created a separate test_main.c to run all tests

3. **Build Process Fixes**:
   - Resolved issues with multiple definitions of main()
   - Fixed linking problems with FreeRTOS and Unity libraries

4. **Common Issues and Solutions**:
   - If you encounter "multiple definition of main" errors, ensure that only one file (either main.c or test_main.c) contains a main() function in each executable.
   - If FreeRTOS functions are undefined, check that the FreeRTOS submodule is properly initialized and that CMakeLists.txt correctly includes FreeRTOS headers and links the library.

## Contributing

Contributions to this project are welcome. Please follow these steps:

1. Fork the repository
2. Create a new branch for your feature
3. Commit your changes
4. Push to your branch
5. Create a new Pull Request
