#include "syscall.h"
#include "console.h"
#include "pico/stdlib.h"

void syscall_handler(int syscall, const char *arg) {
    switch (syscall) {
        case SYS_PRINT:
            console_print(arg);
            break;
        case SYS_LED_ON:
            console_print("Syscall: Turning LED ON\n");
            gpio_put(25, 1);
            break;
        case SYS_LED_OFF:
            console_print("Syscall: Turning LED OFF\n");
            gpio_put(25, 0);
            break;
        default:
            console_print("Syscall: Unknown syscall\n");
            break;
    }
}
