cmake_minimum_required(VERSION 3.12)
project(AdaptiveTaskScheduler C)

set(CMAKE_C_STANDARD 11)

# Add FreeRTOS source files
file(GLOB FREERTOS_SOURCES
    "lib/FreeRTOS/Source/*.c"
    "lib/FreeRTOS/Source/portable/MemMang/heap_4.c"
    "lib/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c"
)

# Add project source files
file(GLOB PROJECT_SOURCES "src/*.c")

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${FREERTOS_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    lib/FreeRTOS/Source/include
    lib/FreeRTOS/Source/portable/GCC/ARM_CM4F
)

# Compiler definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    FREERTOS
    ARM_MATH_CM4
)

# Enable testing
enable_testing()

# Add test executable
add_executable(run_tests tests/test_scheduler.c tests/test_data_fusion.c ${PROJECT_SOURCES} ${FREERTOS_SOURCES})
target_include_directories(run_tests PRIVATE
    src
    lib/FreeRTOS/Source/include
    lib/FreeRTOS/Source/portable/GCC/ARM_CM4F
)
target_compile_definitions(run_tests PRIVATE
    FREERTOS
    ARM_MATH_CM4
)

# Add test
add_test(NAME UnitTests COMMAND run_tests)