//
// Created by os on 8/15/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/_sem.hpp"

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    if (myHandle){
        sem_close(myHandle);
    }
}

int Semaphore::signal() {
    if (myHandle) {
        return sem_signal(myHandle);
    }
    return -3;
}

int Semaphore::wait() {
    if (myHandle){
        return sem_wait(myHandle);
    }
    return -3;
}

