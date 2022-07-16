//
// Created by os on 7/15/22.
//
#include "../h/syscall_c.hpp"
#include "../h/MemoryAllocator.hpp" //neki trapHandler koji nmp sta treba da radi pogledaj upustvo na drivu

enum ABI_Codes {MEM_ALLOC = 0x01, MEM_FREE = 0x02};

void invoker(int serviceId){
    __asm__ volatile ("mv a0, %0" : : "r" (serviceId));
    __asm__ volatile ("ecall");
}

void* mem_alloc(size_t size){
    if(!size) return nullptr;
    size_t blocks = size / MEM_BLOCK_SIZE + (size % MEM_BLOCK_SIZE == 0 ? 0 : 1);
    __asm__ volatile ("mv a1, %0" : : "r" (blocks));
    invoker(MEM_ALLOC);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (void*)ret;
}

int mem_free(void* p){
    if(!p) return -1;
    __asm__ volatile ("mv a4, a3");
    __asm__ volatile ("mv a3, a2");
    __asm__ volatile ("mv a2, a1");
    __asm__ volatile ("mv a1, a0");
    invoker(MEM_FREE);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (ret == 0 ? 0 : -2);
}
