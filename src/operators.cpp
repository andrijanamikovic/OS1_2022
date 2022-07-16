//
// Created by os on 7/15/22.
//
#include "../lib/hw.h"
#include "../h/syscall_c.hpp"

void *operator new(size_t size)
{
    return mem_alloc(size);
}

void *operator new[](size_t size)
{
    return mem_alloc(size);
}

void operator delete(void *p) noexcept
{
    mem_free(p);
}

void operator delete[](void *p) noexcept
{
    mem_free(p);
}
