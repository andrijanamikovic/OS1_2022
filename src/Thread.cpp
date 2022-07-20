//
// Created by os on 7/19/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.hpp"


Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle,body,arg); //mozda run treba?
    //konstrukror iz CCB?
    //i stavljam u scheduler
}

Thread::Thread() {
    thread_create(&myHandle,wrapper,this);
    //isto ali ne u scheduler
    //konstrukror iz CCB?
    //a ovde umesto body stavljam wraper a ne run
}

Thread::~Thread() {
    delete myHandle;
}

int Thread::start() {
    thread_start(&myHandle);
}

void Thread::dispatch() {
    //dispatch iz C API a on iz CCB
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0;
}

void Thread::wrapper(void *p) {
    ((Thread*)p)->run();
}