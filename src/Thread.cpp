//
// Created by os on 7/19/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.hpp"

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle,body,arg);
    this->myHandle = myHandle;
}

Thread::Thread() {
    thread_create_only(&myHandle,wrapper,this);
    this->myHandle = myHandle;
}

Thread::~Thread() {
    mem_free((void*)myHandle);
}

int Thread::start() {
    return thread_start(myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0; //....
}

void Thread::wrapper(void *p) {
    ((Thread*)p)->run();
}