//
// Created by os on 6/17/22.
//
//
#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"
#include "../h/print.hpp"
#include "../h/BlockHeader.hpp"

BlockHeader* MemoryAllocator::FreeMemoryBlocks = nullptr;
BlockHeader* MemoryAllocator::AllocatedMemoryBlocks = nullptr;
bool MemoryAllocator::initialize = false;

void* MemoryAllocator::mem_alloc(size_t size){
    if (initialize == false) MemoryAllocator::init();
    BlockHeader* current = FreeMemoryBlocks->first;
    while(current){
        if (current->size >= size) break;
        current = current->next;
    }
    if (current == nullptr) return nullptr;
    BlockHeader* newBlck;

    size_t remaining = current->size - size;
    if (remaining >= sizeof (BlockHeader) + MEM_BLOCK_SIZE){
        if (AllocatedMemoryBlocks == nullptr) {
            AllocatedMemoryBlocks = (BlockHeader *) ((char*) current + remaining - sizeof(BlockHeader)); //meni ova linija setuje first na 101010.... zasto?
            AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->last = nullptr;
        }
        newBlck = (BlockHeader*)((char*)current+remaining-sizeof (BlockHeader));
        newBlck->size = size;
        printInteger(newBlck->size);
        newBlck->next = nullptr;
        newBlck->prev = nullptr;
        AllocatedMemoryBlocks->putBlock(newBlck);
        current->size = remaining - sizeof(BlockHeader);
    } else {
        newBlck = current;
        FreeMemoryBlocks->removeBlock(current);
        if (AllocatedMemoryBlocks == nullptr){
            AllocatedMemoryBlocks = (BlockHeader*)(current + remaining - sizeof (BlockHeader));
        }
        AllocatedMemoryBlocks->putBlock(newBlck);
    }

    return (newBlck + sizeof(BlockHeader)); // + sizeof(BlockHeader) treba da vrati pokazivac na mesto odmah posle zaglavlja? ali misim da mi to onda remeti i ostatak koda
};

int MemoryAllocator::mem_free(void* ptr){
    if (initialize == false) {
        MemoryAllocator::init();
    }
    if (AllocatedMemoryBlocks == nullptr) return -1;
    BlockHeader* blck = (BlockHeader*)ptr - sizeof(BlockHeader);
    AllocatedMemoryBlocks->removeBlock(blck);
    blck->next = nullptr;
    blck->prev = nullptr;
    FreeMemoryBlocks->putBlock((BlockHeader*) blck);
    FreeMemoryBlocks->join((BlockHeader*)blck);
    return 0;
};

void MemoryAllocator::init() {
    BlockHeader* initBlock = (BlockHeader*) HEAP_START_ADDR;
    initBlock->next = initBlock->prev = nullptr;
    initBlock->size = (char*)HEAP_END_ADDR - (char*)HEAP_START_ADDR - 1;
    FreeMemoryBlocks = (BlockHeader*) HEAP_START_ADDR;
    FreeMemoryBlocks->putBlock(initBlock);
    initialize = true;
}

uint64 MemoryAllocator::getFirst() {
    if (initialize == false) {
        MemoryAllocator::init();
    }
    return  FreeMemoryBlocks->getList();
}

