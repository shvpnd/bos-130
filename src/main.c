#include "pico/stdlib.h"
#include "kernel.h"
#include "task.h"
#include "shell.h"
#include "console.h"
#include "syscall.h"

void blink_task()
{
    static int count = 0;

    console_print("Task: Blinking LED ON\n");
    gpio_put(25, 1);
    sleep_ms(500);
    console_print("Task: Blinking LED OFF\n");
    gpio_put(25, 0);
    sleep_ms(500);
    console_print("Task: Blinking LED ON\n");
    gpio_put(25, 1);
    sleep_ms(500);
    console_print("Task: Blinking LED OFF\n");
    gpio_put(25, 0);
    sleep_ms(500);

    count++;
    if (count < 5)
    {
        syscall_handler(SYS_YIELD, NULL);
    }
    else
    {
        console_print("Task: Blink task exiting...\n");
        syscall_handler(SYS_EXIT, NULL);
    }
}

void shell_task()
{
    shell_loop();
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);

    console_print("BOS-130 Booting...\n");

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    task_init();
    task_create(blink_task);
    task_create(shell_task);

    kernel_main();

    return 0;
}
