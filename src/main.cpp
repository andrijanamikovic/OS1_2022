//
// Created by os on 6/18/22.
//
#include "../h/BlockHeader.hpp"
#include "../h/print.hpp"
#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"
int main() {
    printInteger(MemoryAllocator::getFirst());
    printString("\n");
    MemoryAllocator::mem_alloc(50);
    void* p = MemoryAllocator::mem_alloc(100);
    MemoryAllocator::mem_alloc(150);
    MemoryAllocator::FreeMemoryBlocks->printList();
    printString("\n Zauzeti: \n");
    MemoryAllocator::AllocatedMemoryBlocks->printList();
    printString("After deleting \n");
    MemoryAllocator::mem_free(p);
    MemoryAllocator::FreeMemoryBlocks->printList();
    printString("\n Zauzeti: \n");
    MemoryAllocator::AllocatedMemoryBlocks->printList();


    return  0;
}