//
// Created by os on 6/17/22.
//

#ifndef OS1_2022_LIST_H
#define OS1_2022_LIST_H

#include "../lib/hw.h"

struct BlockHeader {
    uint64 size;
    BlockHeader* next;
    BlockHeader* prev;
    BlockHeader(uint64 size, BlockHeader* next = nullptr, BlockHeader* prev = nullptr): size(size), next(next),prev(prev){};
    ~BlockHeader(){ size= 0; next = nullptr; prev = nullptr;}
};

class List {
public:
    List();
    ~List();
    void putBlock(BlockHeader* newBlck);
    void removeBlock(BlockHeader* Blck);
    uint64 popList();
    uint64 getList();
    BlockHeader* getFirst();
    BlockHeader* init(BlockHeader* address);
    BlockHeader* getLast();
private:
    BlockHeader *first, *last;

};


#endif //OS1_2022_LIST_H
