#include "task.h"
#include "console.h"

Task tasks[MAX_TASKS];
int current_task = 0;

void task_init()
{
    console_print("Task System: Initializing...\n");
    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].active = 0;
    }
}

void task_create(void (*func)(void))
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (!tasks[i].active)
        {
            tasks[i].function = func;
            tasks[i].active = 1;
            console_print("Task System: Task created\n");
            return;
        }
    }
}

void task_exit()
{
    console_print("Task System: Task exiting\n");
    tasks[current_task].active = 0; // mark task as inactive
    task_switch();                  // switch to next active task
}

void task_yield()
{
    task_switch();
}

void task_switch()
{
    int start_task = current_task;

    while (1)
    {
        current_task = (current_task + 1) % MAX_TASKS;

        if (tasks[current_task].active)
        {
            console_print("Task System: Switching task\n");
            tasks[current_task].function();
            return;
        }

        // prevent infinite loop if no tasks are active
        if (current_task == start_task)
        {
            console_print("Task System: No active tasks!\n");
            break;
        }
    }
}
