//
// Created by os on 7/19/22.
//

#ifndef OS1_2022_SCHEDULER_HPP
#define OS1_2022_SCHEDULER_HPP

#include "list.hpp"
//class _thread;
//class List;
class Scheduler
{
private:
    static List readyCoroutineQueue;

public:
    static _thread *get();

    static void put(_thread *ccb);

};


#endif //OS1_2022_SCHEDULER_HPP
