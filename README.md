# Adaptive Task Scheduler for Multi-Sensor Data Fusion

<!-- ## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Dependencies](#dependencies)
4. [Setup and Installation](#setup-and-installation)
5. [Building the Project](#building-the-project)
6. [Running the Project](#running-the-project)
7. [Testing](#testing)
8. [Project Components](#project-components)
9. [Recent Changes and Troubleshooting](#recent-changes-and-troubleshooting)
10. [Contributing](#contributing) -->

## Introduction

This project implements an adaptive task scheduler for a multi-sensor system, optimizing CPU usage and power consumption based on sensor priorities and data rates. It uses FreeRTOS to manage tasks, implement inter-task communication, and showcase adaptive scheduling based on runtime task behavior.

<!-- ## Project Structure

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
``` -->

## Dependencies

- CMake (version 3.12 or higher)
- GCC compiler
- FreeRTOS (included as a submodule)
- Unity (included as a submodule for testing)

## Setup and Installation

1. Clone the repository:
   ```
   git clone https://github.com/anand2532/adaptive-task-scheduler.git
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

<!-- ## Testing

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
``` -->

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

### Recent Changes

1. **CMakeLists.txt Updates**:
   * Added FreeRTOS as a static library
   * Included Unity for testing (later removed)
   * Separated main executable and test executable builds
   * Added pthread and rt library linking for POSIX support

2. **Test Files Restructuring**:
   * Removed duplicate main(), setUp(), and tearDown() functions
   * Created a separate test_main.c to run all tests (later removed)
   * Implemented Python-based sensor simulator for more realistic testing

3. **Build Process Fixes**:
   * Resolved issues with multiple definitions of main()
   * Fixed linking problems with FreeRTOS libraries
   * Ensured correct inclusion of FreeRTOS headers

4. **Sensor Data Reception**:
   * Implemented POSIX thread-based sensor data receiver
   * Added UDP socket communication for receiving simulated sensor data

5. **Data Fusion Implementation**:
   * Created a separate data fusion task that runs periodically
   * Implemented a simple averaging algorithm for fusing sensor data

6. **Adaptive Scheduling**:
   * Added framework for adjusting task priorities based on runtime behavior
   * Implemented getLatestSensorData() function for efficient data access

7. **Configuration and Flexibility**:
   * Added config.h for centralized project configuration
   * Made the number of sensors and their sampling rates configurable

### Troubleshooting

1. **Multiple Definition of main() Error**:
   * Issue: Compilation fails due to multiple definitions of the main() function.
   * Solution: Ensure that only one file (main.c) contains a main() function. Remove any main() functions from test files or other source files.

2. **Undefined FreeRTOS Functions**:
   * Issue: Compiler reports undefined references to FreeRTOS functions.
   * Solution: 
     - Check that the FreeRTOS submodule is properly initialized: 
       ```
       git submodule update --init --recursive
       ```
     - Verify that CMakeLists.txt correctly includes FreeRTOS headers and links the library:
       ```cmake
       target_include_directories(${PROJECT_NAME} PRIVATE ${FREERTOS_INCLUDE_DIRS})
       target_link_libraries(${PROJECT_NAME} PRIVATE freertos)
       ```

3. **Sensor Data Not Being Received**:
   * Issue: The program runs but doesn't receive any sensor data.
   * Solution: 
     - Ensure the Python sensor simulator is running.
     - Check that the UDP port (default 12345) is not blocked by a firewall.
     - Verify that the IP address in the simulator matches your local machine's IP.

4. **Build Fails Due to Missing pthread**:
   * Issue: Compilation fails with errors related to pthread functions.
   * Solution: 
     - Install pthread development libraries. On Ubuntu/Debian:
       ```
       sudo apt-get install libpthread-stubs0-dev
       ```
     - Ensure CMakeLists.txt links against pthread:
       ```cmake
       target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
       ```

5. **Data Fusion Task Not Running**:
   * Issue: The data fusion task doesn't seem to be executing.
   * Solution:
     - Check that the task is created with sufficient stack size and appropriate priority.
     - Verify that FUSION_INTERVAL_MS in config.h is set to a reasonable value.
     - Add debug print statements in the data fusion task to confirm it's being called.

6. **Adaptive Scheduling Not Working**:
   * Issue: Task priorities don't seem to be adjusting as expected.
   * Solution:
     - Implement the adjustTaskPriority() function in scheduler.c with your desired logic.
     - Add debug print statements to show when and how priorities are being adjusted.
     - Ensure RUNTIME_THRESHOLD in config.h is set appropriately for your system.

7. **CMake Configuration Fails**:
   * Issue: CMake fails to configure the project.
   * Solution:
     - Ensure you have CMake version 3.12 or higher installed.
     - Check that all required libraries and dependencies are installed on your system.
     - Verify that the project structure matches what's expected in CMakeLists.txt.

Remember to always check the console output for specific error messages, as they often provide valuable clues about the root cause of any issues you encounter.

## Contributing

Contributions to this project are welcome. Please follow these steps:

1. Fork the repository
2. Create a new branch for your feature
3. Commit your changes
4. Push to your branch
5. Create a new Pull Request


```
https://dev-demo-editor.perceiv.io/#/paused-reality/view-pr/67cc141c18defe0b1bebc3ee?az=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoiNDllZjMwNDYtZDljMS00NTBiLWFmMGUtNmNiZGM3MTE1MGFlIiwiaWF0IjoxNzM5NTM0ODU3fQ.oqUaDm8K3Fbm65Vhlsh5UcOiE05Sohdyfs2nwKX3Wr8
```

```
https://dev-demo-editor.perceiv.io/#/paused-reality/view-pr/67d13f1e0a4d960b1b79712f?az=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoiNDllZjMwNDYtZDljMS00NTBiLWFmMGUtNmNiZGM3MTE1MGFlIiwiaWF0IjoxNzM5NTM0ODU3fQ.oqUaDm8K3Fbm65Vhlsh5UcOiE05Sohdyfs2nwKX3Wr8
```

```
gst-launch-1.0 nvarguscamerasrc ! 'video/x-raw(memory:NVMM), width=1920, height=1080, format=NV12, framerate=30/1' ! \
nvvidconv ! 'video/x-raw, format=I420' ! x264enc tune=zerolatency bitrate=4000 speed-preset=superfast ! \
rtph264pay config-interval=1 pt=96 ! udpsink host=127.0.0.1 port=5000
```

```
gst-launch-1.0 nvarguscamerasrc ! 'video/x-raw(memory:NVMM), width=1280, height=720, format=NV12, framerate=30/1' ! nvvidconv ! nvoverlaysink -e
```

* i have a imx477 camera and  i have connected it to my jetson nano i have also connected the jetson nano to the monitor and i want to stream video, give me full step, i can use vlc to see the video, use  udp


```
https://rustpad.io/#7tWY41
```

```
gst-launch-1.0 udpsrc port=5000 caps="application/x-rtp, media=video, encoding-name=H264" ! \
rtph264depay ! avdec_h264 ! autovideosink
```

```
gst-launch-1.0 nvarguscamerasrc ! \
'video/x-raw(memory:NVMM), width=1920, height=1080, framerate=30/1' ! \
nvvidconv ! nvoverlaysink
```
```
gst-launch-1.0 nvarguscamerasrc ! \
'video/x-raw(memory:NVMM), width=1280, height=720, framerate=30/1' ! \
nvvidconv ! videoconvert ! autovideosink
```


```python
import cv2

cap = cv2.VideoCapture("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=1280, height=720, framerate=30/1 ! nvvidconv ! video/x-raw, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink", cv2.CAP_GSTREAMER)

if not cap.isOpened():
    print("Camera could not be opened.")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        break
    cv2.imshow("IMX477 Camera", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
```