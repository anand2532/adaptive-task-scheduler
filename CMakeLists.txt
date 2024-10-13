cmake_minimum_required(VERSION 3.12)
project(AdaptiveTaskScheduler C)

set(CMAKE_C_STANDARD 11)

# FreeRTOS Source Files
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS)
set(FREERTOS_PORT_DIR ${FREERTOS_DIR}/portable/GCC/Posix)

file(GLOB FREERTOS_SOURCES
    ${FREERTOS_DIR}/*.c
    ${FREERTOS_PORT_DIR}/*.c
    ${FREERTOS_PORT_DIR}/utils/*.c
    ${FREERTOS_DIR}/portable/MemMang/heap_3.c
)

# FreeRTOS Include Directories
set(FREERTOS_INCLUDE_DIRS
    ${FREERTOS_DIR}/include
    ${FREERTOS_PORT_DIR}
    ${FREERTOS_PORT_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add FreeRTOS as a library
add_library(freertos STATIC ${FREERTOS_SOURCES})

target_include_directories(freertos PUBLIC ${FREERTOS_INCLUDE_DIRS})

# Unity
set(UNITY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/Unity/src)
include_directories(${UNITY_DIR})
add_library(unity STATIC ${UNITY_DIR}/unity.c)

# Your project source files
set(PROJECT_SOURCES
    src/data_fusion.c
    src/scheduler.c
    src/sensor_tasks.c
)

# Create main executable
add_executable(${PROJECT_NAME} 
    src/main.c
    ${PROJECT_SOURCES}
)

# Include directories for main executable
target_include_directories(${PROJECT_NAME} PRIVATE
    ${FREERTOS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link FreeRTOS for main executable
target_link_libraries(${PROJECT_NAME} PRIVATE freertos pthread rt)

# Enable testing
enable_testing()

# Add test executable
add_executable(run_tests 
    tests/test_main.c
    tests/test_scheduler.c 
    tests/test_data_fusion.c 
    ${PROJECT_SOURCES}
)

# Include directories for test executable
target_include_directories(run_tests PRIVATE
    ${FREERTOS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${UNITY_DIR}
)

# Link libraries for test executable
target_link_libraries(run_tests PRIVATE freertos unity pthread rt)

# Add test
add_test(NAME UnitTests COMMAND run_tests)