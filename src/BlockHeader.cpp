//
// Created by os on 6/17/22.
//

#include "../h/BlockHeader.hpp"

BlockHeader* BlockHeader::putBlock(BlockHeader* newBlck) {
    if (newBlck == nullptr) return nullptr;
    newBlck->next = newBlck->prev = nullptr;
    if (first == nullptr) {
        last = first = newBlck;
        newBlck->next = newBlck->prev = nullptr;
        return newBlck;
    } else if (newBlck < first){
        first->prev = newBlck;
        newBlck->next = first;
        newBlck->prev = nullptr;
        first = newBlck;
        return newBlck;
    } else {
        BlockHeader* current = first;
        while (current){
            if (newBlck < current){
                if (current->prev!= nullptr) {
                    current->prev->next = newBlck;
                }
                newBlck->prev = current->prev;
                current->prev = newBlck;
                newBlck->next = current;
                return first;
            }
            current = current->next;
        }
    }
    last->next = newBlck;
    newBlck->prev = last;
    last = newBlck;
    newBlck->next = nullptr;
    return first;

}

BlockHeader* BlockHeader::removeBlock(BlockHeader *Blck) {
    if (!Blck) return first;
    if (Blck == first){
        first = first->next;
        if (first) {
            first->prev = nullptr;
        }
        else {
            last = nullptr;
        }
        return first;
    } else if (Blck == last){
        last = last->prev;
        if (last){
            last->next = nullptr;
        }//added after testing allocator
        return first;
    } else {
        BlockHeader* current = first;
        while (current && current!=Blck) {
            current = current->next;
        }
        if (current) {
            if (current->prev ){
                current->prev->next = current->next;
    }
    if (current->next)
        current->next->prev = current->prev;
            current = nullptr;
        }
        return first;
    }
//    }
//    void *ptr = (void*)0x1010101010101;
//    if (Blck->prev  && Blck->prev != ptr){
////        if (Blck!=ptr)
//            Blck->prev->next = Blck->next;
//    }
//    if (Blck->next && Blck->next!= ptr)
//        Blck->next->prev = Blck->prev;
//    Blck = nullptr;
    return first;
}

BlockHeader::BlockHeader() {
    first=last= nullptr;
}

void BlockHeader::printList() {
    BlockHeader* current = first;
    int i =1;
    while (current){
        i++;
        current = current->next;
    }
}

void BlockHeader::joinFreeBlocks() {
    BlockHeader* current = first;
    if (!current) return;
    while (current->next && ((char*)current + current->size + sizeof (BlockHeader) >= (char*)current->next)){
        current->size += current->next->size + sizeof(BlockHeader);
        if (current->next->next) {
            current->next->next->prev = current;
        }
        current->next = current->next->next;
    }
}
