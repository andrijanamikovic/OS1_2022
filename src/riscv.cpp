//
// Created by os on 7/15/22.
//

#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/_thread.hpp"
#include "../h/AbiCodes.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/_sem.hpp"
#include "../lib/console.h"


void Riscv::popSppSpie()
{
    __asm__ volatile ("csrw sepc, ra");
    ms_sstatus(SSTATUS_SPP);
    __asm__ volatile ("sret");
}

uint64 Riscv::handleSupervisorTrap()
{
    uint64 code = 0;
    __asm__ volatile ("mv %0, a0":"=r" (code));
    uint64 arrg1, arrg2, arrg3, arrg4;
    __asm__ volatile ("mv %0, a1":"=r" (arrg1));
    __asm__ volatile ("mv %0, a2":"=r" (arrg2));
    __asm__ volatile ("mv %0, a3":"=r" (arrg3));
    __asm__ volatile ("mv %0, a4":"=r" (arrg4));

    uint64 scause = r_scause();


    uint64 retval = 0;
    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {
        // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
        uint64 sepc = r_sepc() + 4; //sepc get value of ecall so i need to move it back
        uint64 sstatus = r_sstatus();

        switch (code) {
            case MEM_ALLOC: {
                uint64 blocks = arrg1 * MEM_BLOCK_SIZE;
                retval = (uint64) MemoryAllocator::mem_alloc(blocks);
                __asm__ volatile("sd a0, 10*8(fp)");
                break;
            }
            case MEM_FREE: {
                void *ptr = (void *)arrg1;
                retval = (uint64)MemoryAllocator::mem_free(ptr);
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case THREAD_CREATE:{
                _thread *handle = (_thread*)arrg1;
                _thread::Body body = (_thread::Body)arrg2;
                void* arg = (void*)arrg3;
                uint64* stack = (uint64*)arrg4;
                handle = _thread::threadInit(body, arg, stack);
                handle->start();
                if (handle== nullptr) retval = -1;
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case THREAD_EXIT:{
                _thread *handle = (_thread*)arrg1;
                handle->exit();
                break;
            }
            case THREAD_DISPATCH: {
                _thread::dispatch();
                break;
            }
            case THREAD_START: {
                _thread *handle = (_thread*)arrg1;
                handle->start();
                break;
            }
            case SEM_OPEN:{
                sem_t *handle = (sem_t*)arrg1;
                unsigned int init = (unsigned int)arrg2;
                *handle = _sem::sem_open(init);
                if (handle== nullptr) retval = -1;
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case SEM_CLOSE:{
                sem_t *handle = (sem_t*)arrg1;
                _sem::sem_close((_sem *)handle);
                if (handle== nullptr) retval = -1;
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case SEM_WAIT: {
                sem_t *handle = (sem_t*)arrg1;
                _sem::sem_wait((_sem *)handle);
                if (handle== nullptr) retval = -1;
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case SEM_SIGNAL:{
                sem_t *handle = (sem_t*)arrg1;
                _sem::sem_signal((_sem *)handle);
                if (handle== nullptr) retval = -1;
                __asm__ volatile("mv a0, %0" : :"r"(retval));
                break;
            }
            case GET_C:{
                char c = __getc();
                __asm__ volatile("sd a0, 10*8(fp)");
                __asm__ volatile("mv a0, %0" : : "r"(c));
                break;
            }
            case PUT_C:{
                char c = (char)arrg1;
                __putc(c);
                break;
            }

        }
        w_sstatus(sstatus);
        w_sepc(sepc);
    } else if (scause == 0x8000000000000001UL)
    {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
//        _thread::timeSliceCounter++;
//        if (_thread::timeSliceCounter >= _thread::running->getTimeSliceCounter())
//        {
//            uint64 sepc = r_sepc(); //ovo i liniju ispod mozda moram i ovamo svaki put da radim
//            uint64 sstatus = r_sstatus();
//            _thread::timeSliceCounter = 0;
//            _thread::dispatch();
//            w_sstatus(sstatus);
//            w_sepc(sepc);
//        }
        mc_sip(SIP_SSIP);
    } else if (scause == 0x8000000000000009UL)
    {
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        console_handler();
    } else
    {
        printString("Else grana u prekidnoj rutini \n");
        printString("\n Scause: ");
        printInt(r_scause());
        printString("\n Sepc: ");
        printInt(r_sepc());
        printString("\n Stval: ");
        printInt(r_stval());
        printString("\n\n\n");
    }
    return retval;
}