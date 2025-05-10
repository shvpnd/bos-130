#ifndef SYSCALL_H
#define SYSCALL_H

enum SyscallNumbers {
    SYS_PRINT = 1,
    SYS_LED_ON,
    SYS_LED_OFF
};

void syscall_handler(int syscall, const char *arg);

#endif
