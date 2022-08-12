//
// Created by os on 7/19/22.
//

#include "../h/scheduler.hpp"
#include "../test/printing.hpp"

List Scheduler::readyCoroutineQueue;

_thread *Scheduler::get()
{
//    printString("\n Adresa prvog u scheduleru: ");
//    printInt((uint64)readyCoroutineQueue.head->data);
    return readyCoroutineQueue.removeFirst();
}

void Scheduler::put(_thread *ccb)
{
    readyCoroutineQueue.addLast(ccb);
}