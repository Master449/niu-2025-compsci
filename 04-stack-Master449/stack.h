//*************************************************************************
//
//	David Flowers II
//	Z1942130
//	CSCI 340 - 0004
//
//	I certify that this is my own work and where appropriate an extension 
//	of the starter code provided for the assignment.
//
//*************************************************************************

#ifndef STACK_H
#define STACK_H
#include <queue>

template<typename T>
class Stack
{
private:
    std::queue<T> q1;	// These queues are where the stack's elements 
    std::queue<T> q2;	// are to be saved.

public:
    bool empty() const;
    int size() const;
    const T& top();
    void push(const T &val);
    void pop();
};

/**
* @brief checks to see if the stack is empty
*
* @return true if the stack is empty
          false if it is not
******************************************************************************/
template<typename T>
bool Stack<T>::empty() const {
    if (q1.empty() == true) {
        return true;
    }
    return false;
}

/**
* @brief returns the size of the stack
*
* @return int size of stack
******************************************************************************/
template<typename T>
int Stack<T>::size() const {
    return int(q1.size());
}

/**
* @brief This method returns a reference to the top element of the stack
*
* @return T& template type
******************************************************************************/
template<typename T>
const T& Stack<T>::top(){
    return q1.front();
}

/**
* @brief Adds a new element to the top of the stack
******************************************************************************/
template<typename T>
void Stack<T>::push(const T &val) {
    q2.push(val);

        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
 
    std::swap(q1, q2);
}

/**
* @brief removes the newest element from the stack
******************************************************************************/
template<typename T>
void Stack<T>::pop() {
    if (q1.empty())
        return;

    q1.pop();
}

#endif // STACK_H
