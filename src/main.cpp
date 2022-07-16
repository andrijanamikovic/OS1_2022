//
// Created by os on 6/18/22.
//

#include "../h/print.hpp"
#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"
#include "../lib/console.h"
int main() {
//    printInteger(MemoryAllocator::getFirst());
//    printString("\n");
//    MemoryAllocator::mem_alloc(50);
//    void* p = MemoryAllocator::mem_alloc(100);
//    MemoryAllocator::mem_alloc(150);
//    MemoryAllocator::FreeMemoryBlocks->printList();
//    printString("\n Zauzeti: \n");
//    MemoryAllocator::AllocatedMemoryBlocks->printList();
//    printString("After deleting \n");
//    MemoryAllocator::mem_free(p);
//    MemoryAllocator::FreeMemoryBlocks->printList();
//    printString("\n Zauzeti: \n");
//    MemoryAllocator::AllocatedMemoryBlocks->printList();
    int n = 10;
    char* niz = (char*)MemoryAllocator::mem_alloc(10*sizeof(char));
    if(niz == nullptr) {
        __putc('?');
    }

    for(int i = 0; i < n; i++) {
        niz[i] = 'k';
    }

    for(int i = 0; i < n; i++) {
        __putc(niz[i]);
        __putc(' ');
    }

    int status = MemoryAllocator::mem_free(niz);
    if(status != 0) {
        __putc('?');
    }

    return 0;

    return  0;
}