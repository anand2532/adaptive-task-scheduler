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

# project source files
set(PROJECT_SOURCES
    src/main.c
    src/data_fusion.c
    src/scheduler.c
    src/sensor_tasks.c
)

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${FREERTOS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link FreeRTOS and pthread
target_link_libraries(${PROJECT_NAME} PRIVATE freertos pthread rt)