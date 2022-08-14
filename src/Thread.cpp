//
// Created by os on 7/19/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.hpp"
#include "../h/riscv.hpp"


Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle,body,arg);
}

Thread::Thread() {
    thread_create(&myHandle,wrapper,this);
}

Thread::~Thread() {
    delete &myHandle;
}

int Thread::start() {
    return thread_start(&myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0; //ovo mi nije otkucano....
}

void Thread::wrapper(void *p) {
    ((Thread*)p)->run();
}