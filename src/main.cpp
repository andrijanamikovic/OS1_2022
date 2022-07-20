#include "../h/_thread.hpp"
#include "../h/workers.hpp"
#include "../h/print.hpp"

int main()
{
    _thread *coroutines[3];

    coroutines[0] = _thread::createThread(nullptr);
    _thread::running = coroutines[0];

    coroutines[1] = _thread::createThread(workerBodyA);
    printString("CoroutineA created\n");
    coroutines[2] = _thread::createThread(workerBodyB);
    printString("CoroutineB created\n");

    while (!(coroutines[1]->isFinished() &&
             coroutines[2]->isFinished()))
    {
        _thread::yield();
    }

    for (auto &coroutine: coroutines)
    {
        delete coroutine;
    }
    printString("Finished\n");

    return 0;
}
