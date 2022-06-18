//
// Created by os on 6/17/22.
//

#include "../h/List.hpp"

List::List() {
    //ove sve stvari su bile lock prosle godine???//
    first=last=0;
}
List::~List() {
    Node* temp;
    while (first){
        temp = first;
        first = first->next;
        if (temp)
            delete temp;
    }
    last = first;
}

void *List::popList() {
    if (!first) return nullptr;
    void * data = first->data;
    first = first->next;
    if (!first) last = first;
    return data;
}

void List::pushList(void *data) {
    if (!data) return;
    Node* temp = new Node(data);
    if (!first) {
        first = temp;
    }
    else if (last) last->next = temp;
    last = temp;
}

void *List::getList() {
    if (!first) return nullptr;
    return first->data;
}
int List::removeList(void* current){
    if (!first) return -1;
    Node* prev = first;
    if (first->data == current){
        first = first->next;
        if(!first) last = nullptr;
        delete prev;
    }
    Node* temp = first->next;
    while (temp){
        if (temp->data==current){
            prev->next = temp->next;
            if (!temp->next) last = prev;
            return 1;
        }
        prev = temp;
        temp = temp ->next;
    }
    return  -1;
}