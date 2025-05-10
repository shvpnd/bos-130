#include "pico/stdlib.h"
#include "kernel.h"
#include "task.h"
#include "shell.h"

void blink_task() {
    while (1) {
        console_print("Task: Blinking LED ON\n");
        gpio_put(25, 1);
        sleep_ms(500);
        console_print("Task: Blinking LED OFF\n");
        gpio_put(25, 0);
        sleep_ms(500);
        task_switch();
    }
}

int main() {
    stdio_init_all();
    sleep_ms(2000);

    console_print("BOS-130 Booting...\n");
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    kernel_main();
    console_print("Starting shell...\n");
    shell_loop();

    return 0;
}