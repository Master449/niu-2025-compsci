//*******************************************************************
//
//  mystack.cpp
//  CSCI 241 Assignment 8
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "mystack.h"
#include <cstddef>
#include <cstdlib>

mystack::mystack(){
    stkSize = 0;
    stkTop = nullptr; 
}

mystack::mystack(const mystack &x){
    stkSize = x.stkSize;

    if (stkSize == 0){
        stkTop = nullptr;
    } else {
        stkSize = x.stkSize;
        clone(x);
    }
}

mystack::~mystack() {
    clear();
}

mystack &mystack::operator=(const mystack &x){
    if (this != &x){
        clear();
        this->stkSize = x.stkSize;
        clone(x);
    }

    return *this;
}

size_t mystack::size() const {
    return stkSize;
}

bool mystack::empty() const{
    if (stkSize == 0){
        return true;
    } else {
        return false;
    }
}

void mystack::clear(){
    while (empty() == false){
        pop();
    }
}

const int &mystack::top() const {
    return stkTop->value;
}

void mystack::push(int value){
    node *new_node = nullptr;
    new_node = new node(value, new_node);
    new_node->value = value;
    new_node->next = stkTop;
    stkTop = new_node;
    stkSize = stkSize + 1;
}

void mystack::pop(){
    node *delete_node = stkTop;
    stkTop = stkTop->next;
    delete delete_node;
    stkSize = stkSize - 1;
}

void mystack::clone(const mystack &x){
    node *last = nullptr;
    node *ptr = x.stkTop;
    int ptrValue = ptr->value;

    while (ptr != nullptr){
        node *new_node = nullptr;
        new_node = new node(ptrValue, new_node);

        if (last == nullptr){
            stkTop = new_node;
        } else {
            last->next = new_node;
        }

        last = new_node;
        ptr = ptr->next;
    }
}