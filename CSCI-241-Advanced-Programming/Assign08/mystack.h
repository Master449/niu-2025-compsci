//*******************************************************************
//
//  mystack.h
//  CSCI 241 Assignment 8
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstddef>
#include <cstdlib>

struct node {
    int value;
    node *next;

    node(int value, node *next = nullptr) {
        this->value = value;
        this->next = next;
    }
};

class mystack {
    private:
        node *stkTop;
        size_t stkSize;

    public:
        // Default Constructor
        mystack();

        // Copy Constructor
        // initializes a new mystack object to the same string as the existing mystack object
        mystack(const mystack &);

        // Destructor
        ~mystack();

        /**
         * @brief  This overloads the = function so that it can
         *         can assign one mystack object to another 
         * @param  mystack pointer to stack to be =
         *******************************************************/
        mystack &operator=(const mystack &);

        /**
         * @brief  returns the stack size of mystack
         * @returns a size_t variable of the size of the stack
         *******************************************************/
        size_t size() const;

        /**
         * @brief  checks if the stack is empty
         * @return true if it is empty (0) and false if not
         ******************************************************/
        bool empty() const;

        /**
         * @brief  Deletes all of the nodes in the stack's linked list
         *         and sets the stack size back to 0
         ******************************************************/
        void clear();

        /**
         * @brief  returns the value at the top node of the 
         *         stack.
         * @return const int value at the top of the stack
         *****************************************************/
        const int &top() const;

        /**
         * @brief  This pushes a value to the top of the stack
         * @param  int  value to be pushed
         *****************************************************/
        void push(int);

        /**
         * @brief  This pops the top item off of the stack
         *****************************************************/
        void pop();

        /**
         * @brief  This just copies the stack object to another stack
         * @param  mystack to be copied
         *****************************************************/
        void clone(const mystack &);
};

#endif // MYSTACK_H