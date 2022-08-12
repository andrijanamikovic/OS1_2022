//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP

#include "./mem.h"
#include "../test/printing.hpp"

class _thread;

class List
{
public:
    struct Elem
    {
        _thread *data;
        Elem *next;

        Elem(_thread *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;

    List() : head(0), tail(0) {}

    List(const List&) = delete;

    List&operator=(const List&) = delete;

    void addFirst(_thread *data)
    {
        Elem *elem = new Elem(data, head);
        head = elem;
        if (!tail) { tail = head; }
    }

    void addLast(_thread *data)
    {
        Elem *elem = (Elem*) __mem_alloc(sizeof (Elem(data, 0))) ;
        elem->data = data;
//        printString("\n Adresa elementa koji se dodaje u listu schedulera: ");
//        printInt((uint64)elem->data);
        if (tail)
        {
            tail->next = elem;
            tail = elem;
        } else
        {
            head = tail = elem;
        }
    }

    _thread *removeFirst()
    {
        if (!head) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        _thread *ret = elem->data;
        __mem_free((void*)elem);
        return ret;
    }

    _thread *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    _thread *removeLast()
    {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        _thread *ret = elem->data;
        __mem_free((void*)elem);
        return ret;
    }

    _thread *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }
};

//void List::operator delete[](void *p) {
//    __mem_free(p);
//}
//
//void *List::operator new(size_t size) {
//    return __mem_alloc(size);
//}
//
//void *List::operator new[](size_t size) {
//    return __mem_alloc(size);;
//}
//
//void List::operator delete(void *p) {
//    __mem_free(p);
//}

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
