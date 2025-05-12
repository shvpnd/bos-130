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
            console_print("Task created\n");
            return;
        }
    }
}

void task_yield()
{
    task_switch();
}

void task_switch()
{
    int start_task = current_task;
    do
    {
        current_task = (current_task + 1) % MAX_TASKS;
    } while (!tasks[current_task].active && current_task != start_task);

    if (tasks[current_task].active)
    {
        console_print("Task System: Switching task\n");
        tasks[current_task].function();
    }
}
