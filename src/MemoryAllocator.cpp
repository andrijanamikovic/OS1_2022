//
// Created by os on 6/17/22.
//
//
#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"
#include "../h/print.hpp"

List* MemoryAllocator::FreeMemoryBlocks = new List();
List* MemoryAllocator::AllocatedMemoryBlocks = new List();


void* MemoryAllocator::__mem_alloc(size_t size){
    return nullptr;
};

int MemoryAllocator::__mem_free(void* ptr){
    return 0;
};

MemoryAllocator::MemoryAllocator() {
    //I initialize Free memory - hole heap, and Allocated is null
    FreeMemoryBlocks->pushList(reinterpret_cast<void *>((&HEAP_END_ADDR - &HEAP_START_ADDR - 1) / MEM_BLOCK_SIZE));

}