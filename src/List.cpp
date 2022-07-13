//
// Created by os on 6/17/22.
//

#include "../h/List.hpp"
#include "../h/syscall_cpp.hpp"

List::List() {
    first=last=0;
}

List::~List() {
//    BlockHeader* temp;
//    while (first){
//        temp = first;
//        first = first->next;
//        if (temp)
//            delete temp;
//    }
    last = first = nullptr;
}

uint64 List::popList() {
    if (!first) return -1;
    uint64 size = first->size;
    first = first->next;
    if (!first) last = first;
    return size;
}

void List::putBlock(BlockHeader* newBlck) {
    if (newBlck == nullptr) return;
    if (!first) {
        last = first = newBlck;
        return;
    }
    else if (last) {
        if (newBlck > last){
            last->next = newBlck;
            newBlck->prev = last;
            last = newBlck;
            return;
        }
        BlockHeader* current = first;
        while (current < newBlck){
            current = current->next;
        }
        current->prev->next = newBlck;
        newBlck->prev = current->prev;
        current->prev = newBlck;
        newBlck->next = current;
    }
}
uint64 List::getList() {
    if (!first) return -1;
    uint64 size = first->size;
    return size;
}

BlockHeader *List::getFirst() {
    return first;
}

BlockHeader *List::getLast() {
    return last;
}

BlockHeader *List::init(BlockHeader *address) {
    if (address == nullptr || first != nullptr)
        return nullptr;
    first = last = address;
    return first;
}

void List::removeBlock(BlockHeader *Blck) {
    if (Blck == first){
        first = first->next;
        if (first == nullptr) last= nullptr;
    } else if (Blck == last){
        last = last->prev;
    }
    Blck->prev->next = Blck->next;
    Blck->next->prev = Blck->prev;
}


