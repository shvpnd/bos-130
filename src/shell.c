#include "shell.h"
#include "console.h"
#include "syscall.h"
#include "fs.h"
#include "fetch.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

extern FileNode *current_dir; // from fs.c

void shell_loop()
{
    char input[64];
    char command[32], arg1[32], arg2[64];

    console_print("Starting BOS-130 Shell...\n");

    while (1)
    {
        // dynamic prompt showing current path
        char path[128];
        get_path(current_dir, path);
        console_print("\nbos-130:");
        console_print(path);
        console_print("> ");

        memset(input, 0, sizeof(input));
        memset(command, 0, sizeof(command));
        memset(arg1, 0, sizeof(arg1));
        memset(arg2, 0, sizeof(arg2));

        int index = 0;
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

        // parse command and arguments
        sscanf(input, "%s %s %s", command, arg1, arg2);

        // handle commands
        if (strcmp(command, "hello") == 0)
        {
            syscall_handler(SYS_PRINT, "Hello from BOS-130!\n");
        }
        else if (strcmp(command, "led_on") == 0)
        {
            syscall_handler(SYS_LED_ON, NULL);
        }
        else if (strcmp(command, "led_off") == 0)
        {
            syscall_handler(SYS_LED_OFF, NULL);
        }
        else if (strcmp(command, "yield") == 0)
        {
            console_print("Shell: Yielding CPU...\n");
            syscall_handler(SYS_YIELD, NULL);
        }
        else if (strcmp(command, "ls") == 0)
        {
            fs_list(current_dir);
        }
        else if (strcmp(command, "mkdir") == 0)
        {
            if (strlen(arg1) > 0)
                fs_mkdir(arg1);
            else
                console_print("Usage: mkdir <dir>\n");
        }
        else if (strcmp(command, "touch") == 0)
        {
            if (strlen(arg1) > 0)
                fs_create(arg1);
            else
                console_print("Usage: touch <file>\n");
        }
        else if (strcmp(command, "echo") == 0)
        {
            if (strlen(arg1) > 0 && strlen(arg2) > 0)
                fs_write(arg1, arg2);
            else
                console_print("Usage: echo <text> > <file>\n");
        }
        else if (strcmp(command, "cat") == 0)
        {
            if (strlen(arg1) > 0)
            {
                const char *content = fs_read(arg1);
                if (content)
                    console_print(content);
            }
            else
                console_print("Usage: cat <file>\n");
        }
        else if (strcmp(command, "fetch") == 0)
        {
            console_print("Shell received command: fetch\n");
            cmd_fetch();
        }

        else if (strcmp(command, "cd") == 0)
        {
            if (strlen(arg1) > 0)
            {
                if (strcmp(arg1, "..") == 0)
                {
                    if (current_dir->parent)
                    {
                        current_dir = current_dir->parent;
                        console_print("Went up to parent directory\n");
                    }
                    else
                    {
                        console_print("Already at root\n");
                    }
                }
                else
                {
                    FileNode *dir = find_node(current_dir, arg1);
                    if (dir && dir->is_directory)
                    {
                        current_dir = dir;
                        console_print("Changed directory\n");
                    }
                    else
                    {
                        console_print("Directory not found\n");
                    }
                }
            }
            else
            {
                console_print("Usage: cd <dir>\n");
            }
        }
        else if (strcmp(command, "exit") == 0)
        {
            console_print("Shell: Exiting...\n");
            syscall_handler(SYS_EXIT, NULL);
        }
        else
        {
            console_print("Unknown command\n");
        }
    }
}
