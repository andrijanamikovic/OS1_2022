//
// Created by os on 6/17/22.
//

#ifndef OS1_2022_LIST_H
#define OS1_2022_LIST_H

#include "../lib/hw.h"

class BlockHeader {
public:
    BlockHeader();
    void putBlock(BlockHeader* newBlck);
    void removeBlock(BlockHeader* Blck);
    size_t getList();
    BlockHeader* init(BlockHeader* address);
    void printList();
    void join(BlockHeader* blck);

protected:
    size_t size;
    BlockHeader* next;
    BlockHeader* prev;
    BlockHeader(size_t size, BlockHeader* next = nullptr, BlockHeader* prev = nullptr): size(size), next(next),prev(prev), first(nullptr), last(nullptr){}
    ~BlockHeader(){ size= 0; next = nullptr; prev = nullptr; first=last= nullptr;}
    BlockHeader *first, *last;
    friend class MemoryAllocator;
};


#endif //OS1_2022_LIST_H
