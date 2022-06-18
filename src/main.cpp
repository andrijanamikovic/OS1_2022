//
// Created by os on 6/18/22.
//
#include "../h/List.hpp"
#include "../h/print.hpp"
#include "../lib/hw.h"
int main() {

    List* l = new List();
    l->pushList((void *) 15);
    l->pushList((void *) 10);
    l->pushList((void *) 11);
    l->removeList((void*)10);
    printInteger((uint64)l->popList());
    printString("\n");
    printInteger((uint64)l->getList());
    printString("\n");
    printInteger((uint64)l->popList());
    return  0;
}