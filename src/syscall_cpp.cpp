//
// Created by os on 6/17/22.
//

#include "../h/syscall_cpp.hpp"
#include "../lib/mem.h"
#include "../lib/hw.h"

void *operator new(size_t size)
{
    return __mem_alloc(size);
}

void *operator new[](size_t size)
{
    return __mem_alloc(size);
}

void operator delete(void *p) noexcept
{
__mem_free(p);
}

void operator delete[](void *p) noexcept
{
__mem_free(p);
}