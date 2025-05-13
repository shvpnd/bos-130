cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK import file
include(pico_sdk_import.cmake)

project(bos-130 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add the executable and source files
add_executable(${PROJECT_NAME} 
    src/main.c
    src/kernel.c
    src/startup.s
    src/console.c
    src/syscall.c
    src/shell.c
    src/task.c
    src/fs.c
    src/fetch.c
)

# Include your header files
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME} pico_stdlib)

# Enable USB and UART output (optional for debugging)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# Create output formats (UF2 and binary)
pico_add_extra_outputs(${PROJECT_NAME})