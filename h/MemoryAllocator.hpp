//
// Created by os on 6/17/22.
//

#ifndef OS1_2022_MEMORYALLOCATOR_H
#define OS1_2022_MEMORYALLOCATOR_H

#include "./BlockHeader.hpp"
#include "../lib/hw.h"
//#ifdef __cplusplus
//extern "C" {
//#endif
class MemoryAllocator{
public:
    MemoryAllocator(MemoryAllocator&) = delete;
    void operator=(const MemoryAllocator &) = delete;
    static uint64 getFirst();
//    static void* __mem_alloc(size_t size);
    static BlockHeader* FreeMemoryBlocks;
    static BlockHeader* AllocatedMemoryBlocks;
    static void* mem_alloc(size_t size); //ovde treba da stoji prebacila sam u public da bi mogla da testiram samo u mainu
    static int mem_free(void* ptr);
private:
    static void init();
    static bool initialize;
//    static BlockHeader* FreeMemoryBlocks; //ovde treba da stoji....
//    static BlockHeader* AllocatedMemoryBlocks;
};

//#ifdef __cplusplus
//}
//#endif

#endif //OS1_2022_MEMORYALLOCATOR_H
