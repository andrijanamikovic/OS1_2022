//
// Created by os on 6/17/22.
//
//
#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"
#include "../h/print.hpp"

List* MemoryAllocator::FreeMemoryBlocks = new List();
List* MemoryAllocator::AllocatedMemoryBlocks = new List();
MemoryAllocator* MemoryAllocator::memoryAllocator_ = nullptr;

void* MemoryAllocator::__mem_alloc(size_t size){
    if (memoryAllocator_== nullptr) {
        memoryAllocator_ = new MemoryAllocator();
    }
    BlockHeader* current = FreeMemoryBlocks->getFirst();
    while(current){
        if (current->size >= size) break;
        current = current->next;
    }
    if (current == nullptr) return nullptr;
    BlockHeader* newBlck;

    size_t remaining = current->size - size;
    if (remaining >= sizeof (BlockHeader*) + MEM_BLOCK_SIZE){
        if (AllocatedMemoryBlocks == nullptr){
            AllocatedMemoryBlocks = (List*)(current+remaining-sizeof (BlockHeader*));
        }
        newBlck = (BlockHeader*)(current+remaining-sizeof (BlockHeader*)); //sizeof list* ....
        newBlck->size = size;
        newBlck->next = nullptr;
        newBlck->prev = nullptr;
        AllocatedMemoryBlocks->putBlock(newBlck);
        current->size = remaining - sizeof(BlockHeader*);
    } else {
        newBlck = current;
        FreeMemoryBlocks->removeBlock(current);
        if (AllocatedMemoryBlocks == nullptr){
            AllocatedMemoryBlocks = (List*)(current+remaining-sizeof (BlockHeader*));
        }

        //moram da prevezem listu ako nemama dovoljno velike free segmente
        //lakse mi je da je dvostruko ulancam ipak
    }

    return newBlck;
};

int MemoryAllocator::__mem_free(void* ptr){
    if (memoryAllocator_== nullptr) {
        memoryAllocator_ = new MemoryAllocator();
    }
    return 0;
};

MemoryAllocator::MemoryAllocator() {
    //I initialize Free memory - hole heap, at start address, and Allocated is null at the begging
    FreeMemoryBlocks= (List*) HEAP_START_ADDR;
    BlockHeader* first = FreeMemoryBlocks->init((BlockHeader*) HEAP_START_ADDR + sizeof (List*));
    first->size = (char*)HEAP_END_ADDR - (char*)HEAP_START_ADDR - 1;
    first->prev = first->next = nullptr;
    AllocatedMemoryBlocks = nullptr;
}

uint64 MemoryAllocator::getFirst() {
    if (memoryAllocator_== nullptr) {
        memoryAllocator_ = new MemoryAllocator();
    }
    return  FreeMemoryBlocks->getList();
}
