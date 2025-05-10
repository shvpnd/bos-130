#include "console.h"
#include "pico/stdlib.h"
#include <stdio.h>  // Include this header for printf

void console_print(const char *message) {
    printf("%s", message);
}
