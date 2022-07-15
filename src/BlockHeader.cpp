//
// Created by os on 6/17/22.
//

#include "../h/BlockHeader.hpp"
#include "../h/print.hpp"

void BlockHeader::putBlock(BlockHeader* newBlck) {
    if (newBlck == nullptr) return;
    if (!first) {
        last = first = newBlck;
        return;
    } else if (newBlck < first){
        first->prev = newBlck;
        newBlck->next = first;
        first = newBlck;
        return;
    } else if (last) {
        if (newBlck >= last){
            last->next = newBlck;
            newBlck->prev = last;
            last = newBlck;
            return;
        }
        BlockHeader* current = first;
        while (current->next){
            if (newBlck < current){
                if (current->prev!= nullptr) {
                    current->prev->next = newBlck;
                }
                newBlck->prev = current->prev;
                current->prev = newBlck;
                newBlck->next = current;
                return;
            }
            current = current->next;
        }
    }
}
size_t BlockHeader::getList() {
    if (!first) return -1;
    size_t size = first->size;
    return size;
}

void BlockHeader::init(BlockHeader *address) {
    if (address == nullptr) { //i would check first!=nullptr also but it breaks?
        return;
    }
    first = last = address;
   // return first; //maybe void as return value?
}

void BlockHeader::removeBlock(BlockHeader *Blck) {
    if (Blck == first){
        first = first->next;
        if (first == nullptr) last= nullptr;
    } else if (Blck == last){
        last = last->prev;
    }
    if (Blck->prev)
        Blck->prev->next = Blck->next;
    if (Blck->next)
        Blck->next->prev = Blck->prev;
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

void BlockHeader::join(BlockHeader *blck) {
    if (blck == first && blck == last) return;
    if (blck->prev) {
        if ((char*)blck->prev + blck->prev->size == (char*)blck ) { //mozda nesto treba da se castuje????
            blck->prev->size += blck->size + sizeof(BlockHeader); //imam razliku 190 i onda ne dolazi do spajanja blokova????
            if (blck->next)
                blck->next->prev = blck->prev;

            blck->prev->next = blck->next;
            blck = blck->prev;
        }
    }
//    printString("Velicine adresa redom: \n");
//    printInteger(reinterpret_cast<uint64>((char *) blck->prev));
//    printString("\n");
//    printInteger(blck->prev->size);
//    printString("\n");
//    printInteger(reinterpret_cast<uint64>((char *) blck));
//    printString("\n");
//    printInteger(reinterpret_cast<uint64>((char *) blck->prev + blck->prev->size + sizeof(BlockHeader)));
//    printString("\n");
//    printInteger(sizeof (BlockHeader));
    if(blck->next){
        if ((char*)blck + blck->size  == (char*)blck->next)  {
            blck->size += blck->next->size + sizeof(BlockHeader);
            if (blck->next->next) {
                blck->next->next->prev = blck;
                blck->next = blck->next->next;
            } else {
                blck->next = nullptr;
            }
        }
    }
}


