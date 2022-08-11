//
// Created by os on 7/15/22.
//

#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/_thread.hpp"
#include "../h/AbiCodes.hpp"
#include "../test/printing.hpp"
#include "../h/MemoryAllocator.hpp"


void Riscv::popSppSpie()
{
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}
 uint64* Riscv::readArgs(uint64* a) {
    __asm__ volatile ("mv %0, a1":"=r" (a[0]));
    __asm__ volatile ("mv %0, a2":"=r" (a[1]));
    __asm__ volatile ("mv %0, a3":"=r" (a[2]));
    __asm__ volatile ("mv %0, a4":"=r" (a[3]));
    return a;
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
//    &arr = readArgs(arr);

    uint64 scause = r_scause();


    uint64 retval = 0;
    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {
        // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
        uint64 sepc = r_sepc() + 4; //sepc get value of ecall so i need to move it back
        uint64 sstatus = r_sstatus(); //da li meni moze prekid od korisnickog rezima??? ako da onda imam i pc ne samo sepc
//        _thread::timeSliceCounter = 0;
        //kako dobijam argumente???? da vidim koji je u pitanju

        switch (code) {
            case MEM_ALLOC: {
                uint64 blocks = arrg1 * MEM_BLOCK_SIZE;
                retval = (uint64) MemoryAllocator::mem_alloc(blocks); //on ima povratnu vrednost neku ja nemam???
//                //da li mi je potrebna povratna vrednost???
                printString("\n Allocated something");
                //treba da se zove iz MEM_ALLOCATORA ne iz C API
                break;
            }
            case MEM_FREE: {
                void *ptr = (void *)arrg1;
                retval = (uint64)MemoryAllocator::mem_free(ptr);
                break;
            }
            case THREAD_CREATE:{
                _thread *handle = (_thread*)arrg1;
                _thread::Body body = (_thread::Body)arrg2;
                void* arg = (void*)arrg3;
                uint64* stack = (uint64*)arrg4;
                handle = _thread::threadInit(body, arg, stack);
                if (handle== nullptr) retval = -1;
//                *handle->start();
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

        }
        w_sstatus(sstatus);
        w_sepc(sepc);
    } else if (scause == 0x8000000000000001UL)
    {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        _thread::timeSliceCounter++;
        if (_thread::timeSliceCounter >= _thread::running->getTimeSliceCounter())
        {
            uint64 sepc = r_sepc(); //ovo i liniju ispod mozda moram i ovamo svaki put da radim
            uint64 sstatus = r_sstatus();
            _thread::timeSliceCounter = 0;
            _thread::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }
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
        // unexpected trap cause
        //print scause
        //print sepcc
        //print steval
    }
    return retval;
}