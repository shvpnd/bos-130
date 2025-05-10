cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(bos-130 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME} 
    src/main.c
    src/kernel.c
    src/startup.s
    src/console.c
    src/syscall.c
    src/shell.c
    src/task.c 
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} pico_stdlib)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
