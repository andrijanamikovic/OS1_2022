#include "../h/TCB.hpp"
#include "../h/workers.hpp"
#include "../h/print.hpp"

int main()
{
    TCB *coroutines[3];

    coroutines[0] = TCB::createCoroutine(nullptr);
    TCB::running = coroutines[0];

    coroutines[1] = TCB::createCoroutine(workerBodyA);
    printString("CoroutineA created\n");
    coroutines[2] = TCB::createCoroutine(workerBodyB);
    printString("CoroutineB created\n");

    while (!(coroutines[1]->isFinished() &&
             coroutines[2]->isFinished()))
    {
        TCB::yield();
    }

    for (auto &coroutine: coroutines)
    {
        delete coroutine;
    }
    printString("Finished\n");

    return 0;
}
