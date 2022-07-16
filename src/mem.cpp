//
// Created by os on 7/15/22.
//

#include "../lib/mem.h"
#include "../h/MemoryAllocator.hpp"

void* __mem_alloc(size_t size){
    return MemoryAllocator::mem_alloc(size);
}

int __mem_free(void* ptr){
    return MemoryAllocator::mem_free(ptr);
}
