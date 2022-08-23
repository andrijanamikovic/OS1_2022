//
// Created by os on 8/15/22.
//

#ifndef OS1_2022__SEM_HPP
#define OS1_2022__SEM_HPP



#include "list.hpp"
#include "syscall_c.hpp"

class _sem {

public:
     static int sem_close(_sem* sem);
     static _sem* sem_open(unsigned int val);
     static int sem_wait(_sem* sem);
     static int sem_signal(_sem* sem);

//    void *operator new (size_t size);
//    void *operator new[] (size_t size);
//    void operator delete (void* p);
//    void operator delete[] (void* p);

private:
    _sem(int init = 1){
        value = init;
        waiting = new List();

    }
    int value;
    List* waiting;

protected:
    void block();
    void unblock();

};



#endif //OS1_2022__SEM_HPP