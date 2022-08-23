//
// Created by os on 7/19/22.
//

#ifndef OS1_2022__THREAD_HPP
#define OS1_2022__THREAD_HPP

#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"


class _thread {
public:
    friend class Thread;
    friend class Riscv;
    friend class _sem;


    enum ThreadState{
        CREATED, RUNNING, FINISHED, SLEEPING, BLOCKED
    };
    ~_thread() { delete[] stack;}

    using Body = void (*)(void*);

    bool isFinished();
    void setFinished(bool finished);
    void setState(int i);

    static _thread *createThread(Body body, void* arg);

    static void yield();
    int start();

    static uint64 getTimeSliceCounter();

    static void setTimeSliceCounter(uint64 timeSliceCounter);

    static _thread* initMain();

    static _thread *running;
    static uint64 timeSliceCounter;

    static _thread* threadInit(Body body, void* arg);

    void *operator new (size_t size);
    void *operator new[] (size_t size);
    void operator delete (void* p);
    void operator delete[] (void* p);

    static _thread* main;
    static bool finished;


private:
    _thread(Body body, void* arg) :
            body(body),
            arg(arg),
            stack(body != nullptr ? (uint64 *)MemoryAllocator::mem_alloc(DEFAULT_STACK_SIZE * sizeof (uint64)) : nullptr),
            context({body != nullptr ? (uint64) body : 0,
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            state(CREATED),
            timeSlice(DEFAULT_TIME_SLICE),
            mainFlag(false)
    {
    }

    _thread(Body body, void* arg, uint64* stack) :
            body(body),
            arg(arg),
            stack(stack),
            context({body != nullptr ? (uint64) &threadWrapper: 0,
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            state(CREATED),
            timeSlice(DEFAULT_TIME_SLICE),
            mainFlag(false)
    {
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
    ThreadState state;
    uint64 timeSlice;

    bool mainFlag;


    static void contextSwitch(Context *oldContext, Context *runningContext);



    static int exit();
    static int sleep(time_t timeout);
    static void dispatch();

    static void threadWrapper();

    static uint64 constexpr STACK_SIZE = DEFAULT_STACK_SIZE;



};

#endif //OS1_2022__THREAD_HPP
