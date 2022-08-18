//
// Created by os on 6/17/22.
//

#ifndef _syscall_cpp
#define _syscall_cpp

#include "../lib/hw.h"
//#include "syscall_c.hpp"

//#include "syscall_c.hpp"


void *operator new (size_t size);
void operator delete (void* p);

class _thread;
typedef _thread* thread_t;
class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);
    static void wrapper(void *p);
protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
};

class _sem;
typedef _sem *sem_t;
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};
//
//class PeriodicThread : public Thread {
//protected:
//    PeriodicThread (time_t period);
//    virtual void periodicActivation () {}
//};
//
class Console {
public:
    static char getc ();
    static void putc (char);
};
#endif

