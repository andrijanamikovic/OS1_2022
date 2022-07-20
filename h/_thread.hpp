//
// Created by os on 7/19/22.
//

#ifndef OS1_2022__THREAD_HPP
#define OS1_2022__THREAD_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"

class _thread {
public:

    ~_thread() { delete[] stack; }

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    using Body = void (*)();

    static _thread *createThread(Body body, void* arg);

    static void yield();

    static uint64 getTimeSliceCounter();

    static void setTimeSliceCounter(uint64 timeSliceCounter);

    static _thread *running;
    static uint64 timeSliceCounter;

    void *operator new (size_t size);
    void *operator new[] (size_t size);
    void operator delete (void* p);
    void operator delete[] (void* p);
//    //added..
//    //static void wrapper(); ono body je wrapper valjda
//    void start();
//    static void run();
//    //
private:
    _thread(Body body, void* arg) :
            body(body),
            arg(arg),
            stack(body != nullptr ? new uint64[DEFAULT_STACK_SIZE] : nullptr),
            context({body != nullptr ? (uint64) body : 0,
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            finished(false)
    {
        if (body != nullptr) { Scheduler::put(this); }
    }

    struct Context
    {
        uint64 ra; //pc gde treba da se vrati data corrutia
        uint64 sp;
    };

    Body body;
    void *arg;
    uint64 *stack; //smanjuje se kako se stavljaju stvari na njega
    Context context;
    bool finished;

    static void contextSwitch(Context *oldContext, Context *runningContext);

    static void dispatch();

    static uint64 constexpr STACK_SIZE = DEFAULT_STACK_SIZE;


    friend class Thread;
    friend class Riscv;
};

#endif //OS1_2022__THREAD_HPP
