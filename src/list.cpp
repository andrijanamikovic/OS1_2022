//
// Created by os on 8/17/22.
//
#include "../h/list.hpp"

void List::addFirst(_thread *data)
{
    Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
    elem->data = data;
    elem->next = headList;
    this->headList = elem;
    if (!this->tailList) { this->tailList = this->headList; }
}

_thread *List::removeFirst()
{
    if (headList == nullptr) { return nullptr; }
    Elem *elem = headList;
    if (headList == tailList) {
        headList = tailList = nullptr;
    } else {
        headList = headList->next;
    }
    _thread *ret = elem->data;
    int i  = MemoryAllocator::mem_free(elem);
    if (i<0) {
        headList = tailList = nullptr;
    }
//        __mem_free(elem);
    return ret;
}

void List::addLast(_thread *data)
{
    Elem *elem = (Elem*) __mem_alloc(sizeof (Elem)) ;
    elem->data = data;
    elem->next = nullptr;
    if (tailList)
    {
        tailList->next = elem;
        tailList = elem;
    } else
    {
        headList = tailList = elem;
    }
}



_thread *List::peekFirst()
{
    if (!headList) { return 0; }
    return headList->data;
}

_thread *List::removeLast()
{
    if (!headList) { return 0; }

    Elem *prev = 0;
    for (Elem *curr = headList; curr && curr != tailList; curr = curr->next)
    {
        prev = curr;
    }

    Elem *elem = tailList;
    if (prev) { prev->next = 0; }
    else { headList = 0; }
    tailList = prev;

    _thread *ret = elem->data;
    __mem_free((void*)elem);
    return ret;
}

_thread *List::peekLast()
{
    if (!tailList) { return 0; }
    return tailList->data;
}
void List::printList(){
        Elem* current = headList;
        printstring("Head is: ");
        printinteger((uint64)headList);
        while (current) {
            _thread* data = current->data;
            printinteger((uint64) (data));
            current = current->next;
        }

}

List::List() {
    this->headList = 0;
    this->tailList = 0;
}

void List::init() {
    this->headList = 0;
    this->tailList = 0;
}
