//
// Created by os on 7/19/22.
//

#ifndef OS1_2022_TCB_HPP
#define OS1_2022_TCB_HPP

#include "../lib/hw.h"
#include "scheduler.hpp"

// Coroutine Control Block
class TCB {
public:

    ~TCB() { delete[] stack; }

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    using Body = void (*)();

    static TCB *createCoroutine(Body body);

    static void yield();

    static TCB *running;

private:
    explicit TCB(Body body) :
            body(body),
            stack(body != nullptr ? new uint64[STACK_SIZE] : nullptr),
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
    uint64 *stack; //smanjuje se kako se stavljaju stvari na njega
    Context context;
    bool finished;

    static void contextSwitch(Context *oldContext, Context *runningContext);

    static void dispatch();

    static uint64 constexpr STACK_SIZE = 1024;
};

#endif //OS1_2022_TCB_HPP
