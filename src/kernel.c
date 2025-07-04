#include "kernel.h"
#include "syscall.h"
#include "console.h"
#include "task.h"

void kernel_main(void)
{
    console_print("Kernel: Booting BOS-130...\n");
    syscall_handler(SYS_PRINT, "Kernel is now running!\n");

    while (1)
    {
        task_switch(); // switch tasks in the main loop continuously
    }
}
