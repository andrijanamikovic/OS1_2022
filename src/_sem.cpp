//
// Created by os on 8/15/22.
//

#include "../h/_sem.hpp"
#include "../h/mem.h"
#include "../h/_thread.hpp"

int _sem::sem_close(_sem *sem) {
    if (!sem) return -3;
    sem->value = 0;
    _thread* current = sem->waiting->removeFirst();
    while (current) {
        current->setState(0);
        current->start();
        current = sem->waiting->removeFirst();
    }
    sem->waiting = nullptr;
    delete sem;
    return 0;
}

_sem* _sem::sem_open(unsigned int val) {
    _sem* sem = new _sem(val);
    return sem;
}

int _sem::sem_wait(_sem *sem) {
    if (!sem) return -3;
    sem->value--;
    if (sem->value < 0) sem->block();
    return 0;
}

int _sem::sem_signal(_sem *sem) {
    if (!sem) return -3;
    sem->value++;
    if (sem->value <= 0 ) sem->unblock();
    return 0;
}

void *_sem::operator new(size_t size) {
    return __mem_alloc(size);
}

void _sem::operator delete(void *p) {
    __mem_free(p);
}

void _sem::operator delete[](void *p) {
    __mem_free(p);
}

void *_sem::operator new[](size_t size) {
    return __mem_alloc(size);
}

void _sem::block() {
    _thread::running->setState(4);
    waiting->addLast(_thread::running);
    printString("\n Lista blokiranih niti: \n");
    waiting->printList();
    _thread::yield();
}

void _sem::unblock() {
    _thread* current = waiting->removeFirst();
    if (current){
        current->setState(0);
        current->start();
    }
}

