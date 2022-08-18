//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP

#include "./mem.h"
#include "../h/MemoryAllocator.hpp"
#include "../h/print.hpp"
//#include "../test/printing.hpp"

class _thread;
class List {
private:
    struct Elem {
        _thread *data;
        Elem *next;

        Elem(_thread *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;
public:


    List() : head(nullptr), tail(nullptr) {}

    List(const List &) = delete;

    List &operator=(const List &) = delete;

    void addFirst(_thread *data);
    _thread *removeFirst();
    void addLast(_thread *data);
    _thread *peekFirst();
    _thread *removeLast();
    _thread *peekLast();
    void printList();
};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP