#ifndef TASK_H
#define TASK_H

#define MAX_TASKS 4

typedef struct {
    void (*function)(void);
    int active;
} Task;

void task_init();
void task_create(void (*func)(void));
void task_switch();

#endif
