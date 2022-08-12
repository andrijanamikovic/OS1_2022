//
// Created by os on 7/19/22.
//

#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
#include "../h/mem.h"
#include "../h/syscall_c.hpp"
#include "../test/printing.hpp"

_thread *_thread::running = nullptr;
uint64 _thread::timeSliceCounter = 0;
_thread* _thread::main = nullptr;

_thread *_thread::createThread(Body body, void* args)
{
    return new _thread(body, args);
}

void _thread::yield()
{
   __asm__ volatile("ecall");
}

void _thread::dispatch() {
    _thread *old = running;
    if (old->state!=FINISHED && old!=main) {
        Scheduler::put(old);
    }
    _thread* current = Scheduler::get();
//    printString("\n Adresa current iz schedulera je  je: ");
//    printInt((uint64 )current);
    running = current;
    if (running){
//        printString("\n Adresa runninga je: ");
//        printInt((uint64 )running);
//        printString("\n Heap end: ");
//        printInt((uint64)HEAP_END_ADDR);
        running->state = RUNNING;
    } else {
        running = main;
    }
    _thread::contextSwitch(&old->context, &running->context);

}

void *_thread::operator new(size_t size) {
    return __mem_alloc(size);
}

void _thread::operator delete(void *p) {
    __mem_free(p);
}

void _thread::operator delete[](void *p) {
    __mem_free(p);
}

void *_thread::operator new[](size_t size) {
    return __mem_alloc(size);
}

uint64 _thread::getTimeSliceCounter() {
    return timeSliceCounter;
}

void _thread::setTimeSliceCounter(uint64 timeSliceCounter) {
    _thread::timeSliceCounter = timeSliceCounter;
}

_thread*  _thread::threadInit(_thread::Body body, void *arg, uint64 *stack) {
    return new _thread(body, arg, stack);
}

int _thread::start() {
    if (state!=CREATED){
        return -3;
    }
    if (this!=main)
        Scheduler::put(this);
    return 0;
}

int _thread::exit() {
    running->state = FINISHED;
    dispatch();
    return 0;
}

int _thread::sleep(time_t timeout) {
    running->state = SLEEPING;
    //waiting list neki
    //waitingList.add(running,timeout);
    dispatch();
    return 0;
}

void _thread::threadWrapper() {
    Riscv::popSppSpie();
//    running->body(running->arg);
    running->body();
    thread_exit();
}

void _thread::initMain() {
    if (main) return;
    running = new _thread(nullptr, nullptr);
    running->state = RUNNING;
//    printString("\n Adresa runninga maina je: ");
//    printInt((uint64)running);
}


