//
// Created by os on 7/19/22.
//

#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
#include "../h/mem.h"


_thread *_thread::running = nullptr;

_thread *_thread::createThread(Body body, void* args)
{
    //treba da napravim novu nit ali da zovem memory allocator, u blokovima???

    return new _thread(body, args);
}

void _thread::yield()
{
    Riscv::pushRegisters();

    _thread::dispatch();

    Riscv::popRegisters();
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

}

void *_thread::operator new[](size_t size) {
    return nullptr;
}


