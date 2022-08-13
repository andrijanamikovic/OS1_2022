//
// Created by os on 7/19/22.
//

#ifndef OS1_2022__THREAD_HPP
#define OS1_2022__THREAD_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"
#include "../h/MemoryAllocator.hpp"


class _thread {
public:
    friend class Thread;
    friend class Riscv;
//    friend class Scheduler;

    //da li ja ovde treba da imam start/finish/exit itd????
    //msm da da

    enum ThreadState{
        CREATED, RUNNING, FINISHED, SLEEPING
    };
    ~_thread() { delete[] stack; }

    using Body = void (*)(void*);

    bool isFinished();

    static _thread *createThread(Body body, void* arg);

    static void yield();
    int start();

    static uint64 getTimeSliceCounter();

    static void setTimeSliceCounter(uint64 timeSliceCounter);

    static _thread* initMain();

    static _thread *running;
    static uint64 timeSliceCounter;

    static _thread* threadInit(Body body, void* arg, uint64* stack);

    void *operator new (size_t size);
    void *operator new[] (size_t size);
    void operator delete (void* p);
    void operator delete[] (void* p);
    friend class List;
//    //added..
//    //static void wrapper(); ono body je wrapper valjda
//    void start();
//    static void run();
//    //

private:
    _thread(Body body, void* arg) :
            body(body),
            arg(arg),
            stack(body != nullptr ? (uint64 *)MemoryAllocator::mem_alloc(DEFAULT_STACK_SIZE * sizeof (uint64)) : nullptr),
            context({body != nullptr ? (uint64) body : 0, //proveri da tu ne treba wrraper??? negde mozda treba da setujem finish na true
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            state(CREATED),
            timeSlice(DEFAULT_TIME_SLICE),
            mainFlag(false)
    {
        if (body != nullptr) {
            Scheduler::put(this);
        }
    }

    _thread(Body body, void* arg, uint64* stack) :
            body(body),
            arg(arg),
            stack(stack),
            context({body != nullptr ? (uint64) &threadWrapper: 0, //proveri da tu ne treba wrraper??? negde mozda treba da setujem finish na true
                     stack != nullptr ? (uint64) &stack[STACK_SIZE] : 0
                    }),
            state(CREATED),
            timeSlice(DEFAULT_TIME_SLICE),
            mainFlag(false)
    {
        if (body != nullptr) {
            Scheduler::put(this);
        }
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
    static _thread* main;
    bool mainFlag;


    static void contextSwitch(Context *oldContext, Context *runningContext);



    static int exit();
    static int sleep(time_t timeout);
    static void dispatch();

    static void threadWrapper();

    static uint64 constexpr STACK_SIZE = DEFAULT_STACK_SIZE;



};

#endif //OS1_2022__THREAD_HPP

//u wrraperu mozda treba negde da pozivam poopSppSpite to on radi u 7 vezbama, treba...
//pogledaj threadWrraper u njegovom tcb-u i gde ti on treba i sta tacno predstavlja