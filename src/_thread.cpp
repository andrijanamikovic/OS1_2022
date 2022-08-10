//
// Created by os on 7/19/22.
//

#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
#include "../h/mem.h"


_thread *_thread::running = nullptr;
uint64 _thread::timeSliceCounter = 0;

_thread *_thread::createThread(Body body, void* args)
{
    //treba da napravim novu nit ali da zovem memory allocator, u blokovima???
    //mozda treba da saljem velicinu pokazivaca negde????
    return new _thread(body, args);
}

void _thread::yield()
{
   __asm__ volatile("ecall");
}

void _thread::dispatch() {
    _thread *old = running;
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();

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


