//
// Created by os on 8/15/22.
//

#include "../h/_sem.hpp"
#include "../h/_thread.hpp"

int _sem::sem_close(_sem *sem) {
    if (!sem) return -3;
//    sem->value = 0;
    _thread* current = sem->waiting->removeFirst();
    while (current) {
        current->setState(0);
        current->start();
        current = sem->waiting->removeFirst();
    }
    sem->waiting = nullptr;
    __mem_free(sem);
    return 0;
}

_sem* _sem::sem_open(unsigned int val) {
    _sem* sem = (_sem *)(__mem_alloc(sizeof(_sem)));
    if (sem == nullptr) return nullptr;
    sem->value = val;
    sem->waiting = (List*)(__mem_alloc(sizeof (List)));
    sem->waiting->init();

//    sem->waiting->init();
//    sem->waiting = new List();
    return sem;
}

int _sem::sem_wait(_sem *sem) {
    if (sem == nullptr) return -3;
    sem->value--;
    if (sem->value < 0) sem->block();
    return 0;
}

int _sem::sem_signal(_sem *sem) {
    if (sem == nullptr) return -3;
    sem->value++;
    if (sem->value <= 0 ) sem->unblock();
    return 0;
}

//void *_sem::operator new(size_t size) {
//    return __mem_alloc(size);
//}
//
//void _sem::operator delete(void *p) {
//    __mem_free(p);
//}
//
//void _sem::operator delete[](void *p) {
//    __mem_free(p);
//}
//
//void *_sem::operator new[](size_t size) {
//    return __mem_alloc(size);
//}

void _sem::block() {
    if (_thread::running)
        _thread::running->setState(4);
    if (waiting) {
//        printstring("\n\n\nAdding to list: \n");
//        printinteger((uint64 )_thread::running);
//        printstring("\n\n\n");
        waiting->addLast(_thread::running);
    }
    else {
        waiting = new List();
//        printstring("\n\n\nAdding to list: \n");
//        printinteger((uint64 )_thread::running);
//        printstring("\n\n\n");
        waiting->addLast(_thread::running);
    }
//    printString("\n Lista blokiranih niti: \n");
//    waiting->printList();
    _thread::exit();
//    _thread::yield();
}

void _sem::unblock() {
    if (waiting != nullptr) {
        _thread *current = waiting->removeFirst();
        if (current) {
            current->setState(0);
            current->start();
        }
    }
}

//_sem::~_sem() {
//    sem_close(this);
//}

