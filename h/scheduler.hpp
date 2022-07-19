//
// Created by os on 7/19/22.
//

#ifndef OS1_2022_SCHEDULER_HPP
#define OS1_2022_SCHEDULER_HPP

#include "list.hpp"
class TCB;

class Scheduler
{
private:
    static List<TCB> readyCoroutineQueue;

public:
    static TCB *get();

    static void put(TCB *ccb);

};


#endif //OS1_2022_SCHEDULER_HPP
