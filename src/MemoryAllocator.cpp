//
// Created by os on 6/17/22.
//
//
#include "../h/MemoryAllocator.hpp"

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
            AllocatedMemoryBlocks = (BlockHeader *) ((char*) current + remaining); //meni ova linija setuje first na 101010.... zasto?
            AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->last = nullptr;
        }
        newBlck = (BlockHeader*)((char*)current+remaining);
        newBlck->size = size;
        newBlck->next = nullptr;
        newBlck->prev = nullptr;
        AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->putBlock(newBlck);
        current->size = remaining - sizeof(BlockHeader);
    } else {
        newBlck = current;
        FreeMemoryBlocks->first = FreeMemoryBlocks->removeBlock(current);
        if (AllocatedMemoryBlocks == nullptr){
            AllocatedMemoryBlocks = (BlockHeader*)(current + remaining - sizeof (BlockHeader));
            AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->last = nullptr;
        }
        AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->putBlock(newBlck);
    }

    return (void*)((char*)newBlck + sizeof(BlockHeader));
};

int MemoryAllocator::mem_free(void* ptr){
    if (initialize == false) {
        MemoryAllocator::init();
    }
    if (AllocatedMemoryBlocks == nullptr) return -1;
    BlockHeader* blck = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    blck->next = nullptr;
    blck->prev = nullptr;
    AllocatedMemoryBlocks->first = AllocatedMemoryBlocks->removeBlock(blck);
    if (AllocatedMemoryBlocks->first==AllocatedMemoryBlocks->last && AllocatedMemoryBlocks->first == nullptr){
        AllocatedMemoryBlocks = nullptr;
    }
    FreeMemoryBlocks->first = FreeMemoryBlocks->putBlock((BlockHeader*) blck);
    FreeMemoryBlocks->joinFreeBlocks();
    return 0;
};

void MemoryAllocator::init() {
    BlockHeader* initBlock = (BlockHeader*) HEAP_START_ADDR;
    initBlock->next = initBlock->prev = nullptr;
    initBlock->size = (char*)HEAP_END_ADDR - (char*)HEAP_START_ADDR - 1 - sizeof (BlockHeader);
    FreeMemoryBlocks = (BlockHeader*) HEAP_START_ADDR;
    FreeMemoryBlocks->first = FreeMemoryBlocks->last = nullptr;
    FreeMemoryBlocks->first = FreeMemoryBlocks->putBlock(initBlock);
    initialize = true;
}

