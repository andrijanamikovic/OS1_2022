//
// Created by os on 6/17/22.
//

#include "../h/BlockHeader.hpp"
#include "../h/print.hpp"

BlockHeader* BlockHeader::putBlock(BlockHeader* newBlck) {
    if (newBlck == nullptr) return nullptr;
    if (first == nullptr) {
        last = first = newBlck;
        return newBlck;
    } else if (newBlck < first){
        first->prev = newBlck;
        newBlck->next = first;
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
    return first;

}

BlockHeader* BlockHeader::removeBlock(BlockHeader *Blck) {
    if (Blck == first){
        first = first->next;
        if (first == nullptr) {
            last = nullptr;
        }
    } else if (Blck == last){
        last = last->prev;
    }
    if (Blck->prev)
        Blck->prev->next = Blck->next;
    if (Blck->next)
        Blck->next->prev = Blck->prev;
    return first;
}

BlockHeader::BlockHeader() {
    first=last= nullptr;
}

void BlockHeader::printList() {
    BlockHeader* current = first;
    int i =1;
    while (current){
        printString("\n Element adresa pocetka i tog elementa u listi: ");
        printInteger(i);
        printString(" : ");
        printInteger(reinterpret_cast<uint64>(current));
        printString("\n Velicina adresnog prostora je: \n");
        printInteger(current->size);
        i++;
        current = current->next;
    }
}

void BlockHeader::joinFreeBlocks() {
    BlockHeader* current = first;
    while (current->next && ((char*)current + current->size + sizeof (BlockHeader) >= (char*)current->next)){
        current->size += current->next->size + sizeof(BlockHeader);
        if (current->next->next) {
            current->next->next->prev = current;
        }
        current->next = current->next->next;
    }
}
