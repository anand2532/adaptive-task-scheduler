cmake_minimum_required(VERSION 3.12)
project(AdaptiveTaskScheduler C)

set(CMAKE_C_STANDARD 11)

# Set FreeRTOS port
set(FREERTOS_PORT GCC_POSIX CACHE STRING "")

# FreeRTOS configuration
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include FreeRTOS
add_subdirectory(lib/FreeRTOS)

# Add project source files
file(GLOB PROJECT_SOURCES "src/*.c")

# Create executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    lib/FreeRTOS/include
    lib/FreeRTOS/portable/GCC/Posix
)

# Link FreeRTOS
target_link_libraries(${PROJECT_NAME} PRIVATE freertos freertos_config)

# Compiler definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    FREERTOS
    projCOVERAGE_TEST=0
)

# Enable testing
enable_testing()

# Add test executable
add_executable(run_tests tests/test_scheduler.c tests/test_data_fusion.c ${PROJECT_SOURCES})
target_include_directories(run_tests PRIVATE
    src
    lib/FreeRTOS/include
    lib/FreeRTOS/portable/GCC/Posix
)
target_link_libraries(run_tests PRIVATE freertos freertos_config)
target_compile_definitions(run_tests PRIVATE
    FREERTOS
    projCOVERAGE_TEST=0
)

# Add test
add_test(NAME UnitTests COMMAND run_tests)