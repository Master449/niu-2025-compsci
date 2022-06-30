//*******************************************************************
//
//  mystack.h
//  CSCI 241 Assignment 7
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#ifndef MYSTACK_H
#define MYSTACK_H

#include<cstdlib>

class mystack{
	private:
		char *stk;
		size_t stackCapacity;
		size_t stackSize;
	
	public:
	
		// Constructors
		mystack();
		mystack(const mystack& x);
		~mystack();
		mystack& operator=(const mystack& x);
		
		// Member Functions
		/**
		 * This member function should return the stack capacity.
		 *
		 * @return capacity of the stack
		 ********************************************************************************/
		size_t capacity() const;
		
		/**
		 * This member function should return the stack size.
		 *
		 * @return stack size
		 ********************************************************************************/
		size_t size() const;
		
		/**
		 * This member function should return true if the stack size is 0. Otherwise, it should return false.
		 *
		 * @returns true if stack size = 0, otherwise false
		 ********************************************************************************/
		bool empty() const;
		
		/**
		 * This member function should set the stack size back to 0.
		 *
		 * @returns nothing
		 ********************************************************************************/
		void clear();
		
		/**
		 * This member function modifies an object's stack capacity without 
		 * changing the stack size or the contents of the stack array.
		 *
		 * @param n
		 *
		 * @returns nothing
		 ********************************************************************************/
		void reserve(size_t n);
		
		/**
		 * This member function should return the top item in the stack. You may assume 
		 * this function will not be called if the stack is empty.
		 *
		 * @return top item in the stack
		 ********************************************************************************/
		const char& top() const;
		
		/**
		 * This member function should push the character value onto the top of the stack.
		 *
		 * @param value - new character to be put on top of the stack
		 *
		 * @return nothing
		 ********************************************************************************/
		void push(char value);
		
		/**
		 * This member function should pop the top item off of the stack 
		 * by decreasing the stack size by 1.
		 *
		 * @return nothing
		 ********************************************************************************/
		void pop();
};

#endif