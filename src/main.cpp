#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
#include "../test/printing.hpp"
void userMain();

void wraperUserMain(void* ){
    userMain();
    _thread::running->setFinished(true);
    _thread::yield();

}

void main(){
//    printInt((uint64 )HEAP_START_ADDR);
    _thread::initMain();
//    _thread* userMain;


//    thread_create(&userMain, &wraperUserMain, nullptr);
    _thread* userMain = _thread::createThread(&wraperUserMain, nullptr);
    userMain->start();

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
//    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    while (!userMain->isFinished()){
        _thread::yield();
    }

    delete userMain;

}