//
// Created by os on 7/19/22.
//

#include "../h/TCB.hpp"
#include "../h/riscv.hpp"
#include "../h/mem.h"


TCB *TCB::running = nullptr;

TCB *TCB::createCoroutine(Body body)
{
    return new TCB(body);
}

void TCB::yield()
{
    Riscv::pushRegisters();

    TCB::dispatch();

    Riscv::popRegisters();
}

void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}