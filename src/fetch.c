#include "console.h"
#include "syscall.h"
#include "fs.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/clocks.h"

const char *ascii_logo =
    "██████╗  ██████╗ ███████╗       ██╗██████╗  ██████╗\n"
    "██╔══██╗██╔═══██╗██╔════╝      ███║╚════██╗██╔═████╗\n"
    "██████╔╝██║   ██║███████╗█████╗╚██║ █████╔╝██║██╔██║\n"
    "██╔══██╗██║   ██║╚════██║╚════╝ ██║ ╚═══██╗████╔╝██║\n"
    "██████╔╝╚██████╔╝███████║       ██║██████╔╝╚██████╔╝\n"
    "╚═════╝  ╚═════╝ ╚══════╝       ╚═╝╚═════╝  ╚═════╝ \n";

int get_uptime_seconds()
{
    return to_ms_since_boot(get_absolute_time()) / 1000;
}

unsigned int get_cpu_freq()
{
    return clock_get_hz(clk_sys) / 1000000;
}

void get_ram_info(int *used, int *total)
{
    *total = 256; // 256KB on rp2040
    *used = 42;   // placeholder
}

void get_fs_info(int *file_count, int *dir_count)
{
    *file_count = 0;
    *dir_count = 0;
    count_nodes(root, file_count, dir_count);
}

void cmd_fetch()
{
    console_print("\n");
    console_print(ascii_logo);
    console_print("\n");

    console_print("=== BOS-130 System Info ===\n");
    console_print("OS: BOS-130\n");
    console_print("Kernel: 0.1 (Preemptive)\n");
    console_print("CPU: RP2040 (Dual Cortex-M0+)\n");

    int uptime = get_uptime_seconds();
    int mins = uptime / 60;
    int secs = uptime % 60;
    char uptime_str[32];
    sprintf(uptime_str, "Uptime: %d min %d sec\n", mins, secs);
    console_print(uptime_str);

    char freq_str[32];
    sprintf(freq_str, "CPU Freq: %d MHz\n", get_cpu_freq());
    console_print(freq_str);

    int used_ram, total_ram;
    get_ram_info(&used_ram, &total_ram);
    char ram_str[32];
    sprintf(ram_str, "RAM Usage: %d KB / %d KB\n", used_ram, total_ram);
    console_print(ram_str);

    int files, dirs;
    get_fs_info(&files, &dirs);
    char fs_str[64];
    sprintf(fs_str, "Files: %d, Directories: %d\n", files, dirs);
    console_print(fs_str);

    console_print("============================\n");
}
