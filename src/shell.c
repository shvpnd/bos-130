#include <stdio.h>
#include "shell.h"
#include "console.h"
#include "syscall.h"
#include "pico/stdlib.h"
#include <string.h>

void shell_loop()
{
    char input[32];
    int index = 0;

    console_print("Starting BOS-130 Shell...\n");

    while (1)
    {
        console_print("\nbos-130> ");
        index = 0;
        memset(input, 0, sizeof(input));

        while (1)
        {
            int c = getchar_timeout_us(50000);
            if (c == PICO_ERROR_TIMEOUT)
                continue;

            if (c == '\r' || c == '\n')
            {
                input[index] = '\0';
                console_print("\n");
                break;
            }
            else if (c == 127 || c == '\b')
            {
                if (index > 0)
                {
                    index--;
                    console_print("\b \b");
                }
            }
            else if (index < (sizeof(input) - 1))
            {
                input[index++] = c;
                putchar(c);
                fflush(stdout);
            }
        }

        console_print("Shell received command: ");
        console_print(input);
        console_print("\n");

        if (strcmp(input, "hello") == 0)
        {
            syscall_handler(SYS_PRINT, "Hello from BOS-130!\n");
        }
        else if (strcmp(input, "led_on") == 0)
        {
            syscall_handler(SYS_LED_ON, NULL);
        }
        else if (strcmp(input, "led_off") == 0)
        {
            syscall_handler(SYS_LED_OFF, NULL);
        }
        else if (strcmp(input, "yield") == 0)
        {
            console_print("Shell: Yielding CPU...\n");
            syscall_handler(SYS_YIELD, NULL);
        }
        else
        {
            syscall_handler(SYS_PRINT, "Unknown command\n");
        }
    }
}
