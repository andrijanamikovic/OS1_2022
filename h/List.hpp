//
// Created by os on 6/17/22.
//

#ifndef OS1_2022_LIST_H
#define OS1_2022_LIST_H

struct Node {
    void *data;
    Node* next;
    Node(void *data, Node* next = nullptr):data(data),next(next){};
    ~Node(){data= nullptr; next = nullptr;}
};

class List {
public:
    List();
    ~List();
    void pushList(void* data);
    void* popList();
    void* getList();
    int removeList(void* current);
private:
    Node *first, *last;
};


#endif //OS1_2022_LIST_H
