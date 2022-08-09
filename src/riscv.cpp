//
// Created by os on 7/15/22.
//

#include "../h/riscv.hpp"
#include "../lib/console.h"
#include "../h/_thread.hpp"
#include "../h/AbiCodes.hpp"
#include "../test/printing.hpp"

void Riscv::popSppSpie()
{
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

void Riscv::handleSupervisorTrap()
{
    uint64 code;
    __asm__ volatile ("mv %0, a0":"=r" (code));
   // uint64 args[4]; // da li ovo moram na isti nacin pre ovoga ili da ga nekako skinem sa steka tamo gde mi treba

    uint64 scause = r_scause();
    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {
        // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
        uint64 sepc = r_sepc() + 4; //sepc get value of ecall so i need to move it back
        uint64 sstatus = r_sstatus(); //da li meni moze prekid od korisnickog rezima??? ako da onda imam i pc ne samo sepc
//        _thread::timeSliceCounter = 0;
        //kako dobijam argumente???? da vidim koji je u pitanju

        switch (code) {
            case MEM_ALLOC:
//                uint64  blocks;
                //treba da se zove iz MEM_ALLOCATORA ne iz C API
                break;
            case MEM_FREE:
                break;
            case THREAD_CREATE:
                break;
            case THREAD_EXIT:
                break;
            case THREAD_DISPATCH:
                _thread::dispatch();
                break;
            case THREAD_START:
                break;

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
}