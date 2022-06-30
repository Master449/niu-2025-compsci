//*******************************************************************
//
//  mystack.cpp
//  CSCI 241 Assignment 9
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include"mystack.h"

// Default Constructor
mystack::mystack(){
	stackSize = 0;
	stackCapacity = 0;
	stk = nullptr;
}

// Copy Constructor
mystack::mystack(const mystack& x){
	stackCapacity = x.stackCapacity;
	stackSize = x.stackSize;
	stk = new char[stackCapacity];
}

// Destructor
mystack::~mystack(){
	delete stk;
}

mystack& mystack::operator=(const mystack& x){
	stackCapacity = x.stackCapacity;
	stackSize = x.stackSize;
	stk = new char[stackCapacity];
	return *this;
}

size_t mystack::capacity() const {
	return stackCapacity;
}

size_t mystack::size() const {
	return stackSize;
}

bool mystack::empty() const {
	if(stackSize==0) return true;
	return false;
}

void mystack::clear() {
	stackSize = 0;
}

void mystack::reserve(size_t n){
	if(n<stackSize || n==stackCapacity)
		return;

	stackCapacity = n;
	char *tmp = new char[n];

	for(int i=0; stackSize; i++){
		tmp[i] = stk[i];
	}

	delete stk;
	stk = tmp;
}

const char& mystack::top() const {
	const char &c = stk[stackSize-1];
	return c;
}

void mystack::push(char value){
	if(stackSize==stackCapacity || stackCapacity==0) stackCapacity++;
	else stackCapacity+=2;
	stk[stackSize] = value;
	stackSize++;
}

void mystack::pop(){
	stackSize--;
}
