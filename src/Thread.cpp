//
// Created by os on 7/19/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.hpp"
#include "../h/riscv.hpp"


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
    delete &myHandle; //mozda moram iz _thread neki delete?
}

int Thread::start() {
    return thread_start(&myHandle);
}

void Thread::dispatch() {
    //dispatch iz C API a on iz CCB
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0; //ovo mi nije otkucano....
}

void Thread::wrapper(void *p) {
    ((Thread*)p)->run(); //on ga negde prebacuje na body da li to treba da imam i u tcbu???

    //da li ovde treba da sklanjam privilegije???
    //da vratimo SPE na ono sto je bilo
    //da li mi treba finished negde flag za nit
}