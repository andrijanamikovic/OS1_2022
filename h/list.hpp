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
    struct Elem
    {
        _thread *data;
        Elem *next;

        Elem(_thread *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;
public:


    List() : head(nullptr), tail(nullptr) {}

    List(const List&) = delete;

    List&operator=(const List&) = delete;

    void addFirst(_thread *data)
    {
        Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
        elem->data = data;
        elem->next = head;
        head = elem;
        if (!tail) { tail = head; }
    }

    _thread *removeFirst()
    {
        if (!head) { return nullptr; }

        Elem *elem = head;
//
//        printString("\n Adresa elementa koji se vadi iz schedulera: ");
//        printInt((uint64)(elem->data));
        head = head->next;
        if (head == nullptr) { tail = nullptr; }

        _thread *ret = elem->data;
        __mem_free(elem);
        return ret;
    }

    void addLast(_thread *data)
    {
        Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
        elem->data = data;
        elem->next = nullptr;
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
    void printList(){
        Elem* current = head;
//        int i = 0;
        printString("Head is: ");
        printInt((uint64)head);
        while (current) {
            printString("\n Adresa i-tog elementa liste je: ");
            _thread* data = current->data;
            printInt((uint64) (data));
            current = current->next;
        }

    }
};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_LIST_HPP
