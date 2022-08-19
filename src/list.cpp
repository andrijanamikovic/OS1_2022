//
// Created by os on 8/17/22.
//
#include "../h/list.hpp"

void List::addFirst(_thread *data)
{
    Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
    elem->data = data;
    elem->next = head;
    this->head = elem;
    if (!this->tail) { this->tail = this->head; }
}

_thread *List::removeFirst()
{
    if (head == nullptr) { return nullptr; }
    if (head == (void *)0x10) {
        printstring("\n\n\n\nGospode pomiluj.... \n\n\n\n");
        return nullptr;
    }
//    printstring("\n\n\n Removing from list\n\n\n");
//    void *ptr = (void*)0x1010101010101;
//    if (head == ptr ) {
//        head = nullptr;
//        return nullptr;
//    }
    Elem *elem = head;
//
//        printString("\n Adresa elementa koji se vadi iz schedulera: ");
//        printInt((uint64)(elem->data));
//    printstring("Head is in remove first: \n");
//    printinteger((uint64)&head);
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
    }
    _thread *ret = elem->data;
    int i  = MemoryAllocator::mem_free(elem);
    if (i<0) {
        head = tail = nullptr;
    }
//        __mem_free(elem);
//    printstring("\n\n\nRet value is: \n");
//    printinteger((uint64 )ret);
    return ret;
}

void List::addLast(_thread *data)
{
//    printstring("\n\n\nAdding to list: \n\n\n");
    Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
    elem->data = data;
    elem->next = nullptr;
    if (head == (void *)0x10) {
        printstring("\n\n\n\nGospode pomiluj 2.... \n\n\n\n");
//        if (tail != nullptr && tail!= (void *) 0x10){
//            head = tail;
//        } else {
            head = tail = nullptr;
//        }
    }
//    printstring("\n\n\n Adresa elementa koji se dodaje u listu: \n");
//    printinteger((uint64)elem->data);
//    printstring("\n");
    if (tail)
    {
        tail->next = elem;
        tail = elem;
    } else
    {
        head = tail = elem;
    }
}



_thread *List::peekFirst()
{
    if (!head) { return 0; }
    return head->data;
}

_thread *List::removeLast()
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

_thread *List::peekLast()
{
    if (!tail) { return 0; }
    return tail->data;
}
void List::printList(){
//        Elem* current = head;
////        int i = 0;
////        printString("Head is: ");
////        printInt((uint64)head);
//        while (current) {
////            printString("\n Adresa i-tog elementa liste je: ");
//            _thread* data = current->data;
////            printInt((uint64) (data));
//            current = current->next;
//        }
//
}

List::List() {
    this->head = 0;
    this->tail = 0;
}

void List::init() {
    this->head = 0;
    this->tail = 0;
}
