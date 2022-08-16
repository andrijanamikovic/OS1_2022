//
// Created by os on 7/15/22.
//

#ifndef OS1_2022_SYSCALL_C_H
#define OS1_2022_SYSCALL_C_H

#endif //OS1_2022_SYSCALL_C_H

#include "../lib//hw.h"

void* mem_alloc(size_t size);
int mem_free(void* p);

class _thread;
typedef _thread* thread_t;
int thread_create (
    thread_t *handle,
    void(*start_routine)(void*),
    void* arg
);
int thread_start(thread_t *handle);
int thread_exit();
void thread_dispatch();

class _sem;
typedef _sem *sem_t;
int sem_open(
        sem_t *handle,
        unsigned init
);

int sem_close(sem_t handle);
int sem_wait(sem_t id);
int sem_signal(sem_t id);

//const int EOF = -1;
void putc(char);

char getc();