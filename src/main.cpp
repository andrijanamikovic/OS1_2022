#include "../h/_thread.hpp"
#include "../h/riscv.hpp"
void userMain();

void wraperUserMain(void* ){
    userMain();
    _thread::running->setFinished(true);
    _thread::yield();

}

void main(){
    _thread::initMain();
    _thread* userMain = _thread::createThread(&wraperUserMain, nullptr);
    userMain->start();
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    while (!userMain->isFinished()){
        _thread::yield();
    }
    delete userMain;

}