#include "task.h"
#include "console.h"

Task tasks[MAX_TASKS];
int current_task = 0;

void task_init() {
    console_print("Task System: Initializing...\n");
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = 0;
    }
}

void task_create(void (*func)(void)) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].active) {
            tasks[i].function = func;
            tasks[i].active = 1;
            printf("Task System: Task %d created\n", i);
            return;
        }
    }
}

void task_switch() {
    current_task = (current_task + 1) % MAX_TASKS;
    if (tasks[current_task].active) {
        printf("Task System: Switching to task %d\n", current_task);
        tasks[current_task].function();
    }
}
