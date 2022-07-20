//
// Created by os on 7/15/22.
//
#include "../h/syscall_c.hpp"
#include "../h/MemoryAllocator.hpp" //neki trapHandler koji nmp sta treba da radi pogledaj upustvo na drivu

enum ABI_Codes {MEM_ALLOC = 0x01, MEM_FREE = 0x02, THREAD_CREATE = 0x11, THREAD_EXIT = 0x12, THREAD_DISPATCH = 0x13, THREAD_START = 0x14};

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

int thread_create(thread_t *handle,  void(*start_routine)(void*), void* arg){
    if (!handle) return -1;
    __asm__ volatile ("mv a4, a3");
    __asm__ volatile ("mv a3, a2");
    __asm__ volatile ("mv a2, a1");
    __asm__ volatile ("mv a1, a0");
    invoker(THREAD_CREATE);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (ret == 0 ? 0 : -2);
}

int thread_start(thread_t *handle){
    if (!handle) return -1;
    __asm__ volatile ("mv a4, a3");
    __asm__ volatile ("mv a3, a2");
    __asm__ volatile ("mv a2, a1");
    __asm__ volatile ("mv a1, a0");
    invoker(THREAD_START);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (ret == 0 ? 0 : -2);
}
int thread_exit(){
    invoker(THREAD_EXIT);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (ret == 0 ? 0 : -1);
}
void thread_dispatch(){
    invoker(THREAD_DISPATCH);
}