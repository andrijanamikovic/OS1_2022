//
// Created by os on 7/19/22.
//

#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
#include "../h/scheduler.hpp"
#include "../h/print.hpp"

_thread *_thread::running = nullptr;
uint64 _thread::timeSliceCounter = 0;
_thread* _thread::main = nullptr;
bool _thread::finished = false;

_thread *_thread::createThread(Body body, void* args)
{
    return new _thread(body, args);
}

void _thread::yield()
{
    dispatch();
}

void _thread::dispatch() {

    _thread *old = running;
    if (old->state != FINISHED && !old->mainFlag && old->state!=BLOCKED) {
        Scheduler::put(old);
    }
    running = Scheduler::get();
    while (running && running->state == FINISHED){
        running = Scheduler::get();
    }
    if (running == nullptr) {
        running = main;
//        Scheduler::printScheduler();
    }
    running->state = RUNNING;
    if (running == main) {
        running->state = FINISHED;
//        Riscv::ms_sstatus(Riscv::SSTATUS_SPP);
    } else {
        Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
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

_thread*  _thread::threadInit(_thread::Body body, void *arg) {
    _thread* current = (_thread*)__mem_alloc((sizeof (_thread) + MEM_BLOCK_SIZE - 1)/MEM_BLOCK_SIZE);
    uint64* stack = (uint64*)__mem_alloc((DEFAULT_STACK_SIZE * sizeof (uint64)+MEM_BLOCK_SIZE-1)/MEM_BLOCK_SIZE);
    current->arg = arg;
    current ->body = body;
    current ->stack = body != nullptr ? stack : nullptr;
    current -> context = {body != nullptr ? (uint64) &threadWrapper: 0,
                          stack != nullptr ? (uint64) &(current->stack[STACK_SIZE]) : 0};
    current->state = CREATED;
    current->timeSlice = DEFAULT_TIME_SLICE;
    current->mainFlag = false;
    return current;
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

int _thread::sleep(time_t timeout) { //to do...
//    running->state = SLEEPING;
    //waiting list neki
    //waitingList.add(running,timeout);
//    dispatch();
    return 0;
}

void _thread::threadWrapper() {
    Riscv::popSppSpie();
    running->state = RUNNING;
    running->body(running->arg);
    exit();
}

_thread* _thread::initMain() {
    if (main) return main;
    running = new _thread(nullptr, nullptr);
    running->state = RUNNING;
    main = running;
    running->mainFlag = true;
    return running;
}

bool _thread::isFinished() {
    return running->state==FINISHED;
}

void _thread::setFinished(bool value) {
    if (value) {
        this->state = FINISHED;
    }
}
void _thread::setState(int i) {
    switch (i) {
        case 0: {
            this->state = CREATED;
            break;
        }
        case 1: {
            this->state = RUNNING;
            break;
        }
        case 2:{
            this->state = FINISHED;
            break;
        }
        case 3: {
            this->state = SLEEPING;
            break;
        }
        case 4: {
            this->state = BLOCKED;
            break;
        }
    }
}




