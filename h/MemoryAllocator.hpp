//
// Created by os on 6/17/22.
//

#ifndef OS1_2022_MEMORYALLOCATOR_H
#define OS1_2022_MEMORYALLOCATOR_H

#include "./List.hpp"
#include "../lib/hw.h"
//#ifdef __cplusplus
//extern "C" {
//#endif
class MemoryAllocator{
public:
    MemoryAllocator(MemoryAllocator&) = delete;
    void operator=(const MemoryAllocator &) = delete;
    static uint64 getFirst();
protected:
    void* __mem_alloc(size_t size);
    int __mem_free(void* ptr);
    static MemoryAllocator* memoryAllocator_;
private:
    MemoryAllocator();
    static List* FreeMemoryBlocks;
    static List* AllocatedMemoryBlocks;
};

//#ifdef __cplusplus
//}
//#endif

#endif //OS1_2022_MEMORYALLOCATOR_H
