#ifndef MYLIST_H
#define MYLIST_H

//*******************************************************************
// 
//  mylist.h
//  CSCI 241 Assignment 10
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <iostream>
#include <stdexcept>

// Forward declaration of the mylist template class
template <class T>
class mylist;
        
// Forward declaration of the operator<< template function
// Function documentation is on line 159
template <class T>
std::ostream& operator<<(std::ostream&, const mylist<T>&);

template <class T>
struct node
{
    T value;
	node<T>* next, * prev;

	node(const T& value = T(), node<T>* prev = nullptr, node<T>* next = nullptr){
		this->value = value;
		this->prev = prev;
		this->next = next;

	}
};

template <class T>
class mylist {
	private:
		node<T>* listfront;
		node<T>* listback;
		size_t listSize;
		int count;

	public:
		/**
		 * This is the constructor for the mylist template class
		 *
		 * It sets listfront, and listback to nullptr and the listSize to 0.
		 ********************************************************************************/
		mylist();

		/**
		 * This is the destructor for the mylistclass.
		 *
		 * Calls the clear method to clear the object.
		 ********************************************************************************/
		~mylist();

		/**
		 * This first line is a brief description.
		 *
		 * This is the copy constructor for the mylistclass.
		 *
		 * It traverses the existing mylist object and loops through to add each value
		 * to the new object.
		 * 
		 * @param x the object to be copied to a new one.
		 * 
		 ********************************************************************************/
		mylist(const mylist<T>& x);

		/**
		 * The clear function call.
		 * 
		 * It sets the list back to an empty state and deletes the nodes
		 * within the object.
		 ********************************************************************************/
		void clear();

		/**
		 * This function returns the size of the list in the object.
		 *
		 * @return the size of the list
		 ********************************************************************************/
		size_t size() const;

		/**
		 * Function to check is the list is empty
		 *
		 *
		 * @return true if the list is empty
		 * 		   false if the list is not empty
		 ********************************************************************************/
		bool empty() const;

		/**
		 * (const version) Function to return the value of the front node
		 *
		 * @return the value in front node in the list
		 * 		   throws an underflow_error if the list is empty
		 ********************************************************************************/
		const T& front() const;

		/**
		 * (const version) Function to return the value of the back node
		 *
		 * @return the value in back node in the list
		 * 		   throws an underflow_error if the list is empty
		 ********************************************************************************/
		const T& back() const;

		/**
		 *Function to return the value of the front node
		 *
		 * @return the value in front node in the list
		 * 		   throws an underflow_error if the list is empty
		 ********************************************************************************/
		T& front();

		/**
		 * Function to return the value of the back node
		 *
		 * @return the value in back node in the list
		 * 		   throws an underflow_error if the list is empty
		 ********************************************************************************/
		T& back();

		/**
		 * Function to insert an item at the front of the list
		 *
		 * @param value to be pushed to the front node
		 ********************************************************************************/
		void push_front(const T& value);

		/**
		 * Function to insert an item at the back of the list
		 *
		 * @param value to be pushed to the back node
		 ********************************************************************************/
		void push_back(const T& value);

		/**
		 * Function to remove an item at the front of the list
		 *
		 * @return nothing but will throw an error if the list is empty
		 ********************************************************************************/
		void pop_front();

		/**
		 * TFunction to remove an item at the back of the list
		 *
		 * @return nothing but will throw an error is the list is empty
		 ********************************************************************************/
		void pop_back();

		/**
		 * Overloaded stream insertion operator
		 *
		 * This is so an entire mylist object can be sent to std output
		 ********************************************************************************/
    	friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);

		/**
		 * Overloaded assignment operator function
		 *
		 * This function calls the clear member function to first clear the list. Then it
		 * calls the objects copy function to copy the data of the function to then 
		 * assign it to the object that needs to be assigned.
		 *
		 * @param x object to be copied
		 *  
		 * @return The object is then reasssigned
		 ********************************************************************************/
		mylist<T>& operator=(const mylist<T>& x);

		/**
		 * Overloaded equality operator
		 *
		 * This member function returns true if 1) the two lists contain the same number 
		 * of nodes, and 2) if each element stored in the left-hand-side list is equal 
		 * to the corresponding element of the right-hand-side list. Otherwise, the 
		 * method returns false.
		 *
		 * @param x object to be compared
		 * 
		 * @return true if they are equal
		 * 		   false if they are not equal
		 ********************************************************************************/
		bool operator==(const mylist<T>& rhs) const;

		/**
		 * Overloaded less than operator
		 *
		 * list1 is less than list2 if the first value of list1 is less than the 
		 * first value of list2, and greater if the first value of list1 is greater 
		 * than the first value of list2. If the two first value elements are
		 * equivalent then the member function compares the two second value elements
		 *
		 * @param x object to be compared
		 * 
		 * @return true
		 * 		   false
		 ********************************************************************************/
		bool operator<(const mylist<T>& rhs) const;

};
        
// Function definitions
template <class T>
mylist<T>::mylist() {
	listfront = nullptr;
	listback = nullptr;
	listSize = 0;
}

template <class T>
mylist<T>::~mylist() {
	clear();
}

template <class T>
mylist<T>::mylist(const mylist<T>& x){
	listfront = nullptr;
	listback = nullptr;
	listSize = 0;
	if (x.listfront != nullptr) {
		node<T>* current = x.listfront;
		do {
			node<T>* newNode = new node<T>(*current);
			push_back(newNode->value);
		} while((current = current->next) != nullptr);
	}
}

template <class T>
void mylist<T>::clear(){
	while (!empty()){
		pop_front();
	}

	listfront = nullptr;
	listback = nullptr;
}

template <class T>
size_t mylist<T>::size() const {
	return listSize;
}

template <class T>
bool mylist<T>::empty() const {
	if (listSize == 0)
		return true;
	else
		return false;
}

template <class T>
const T& mylist<T>::front() const {
	if (empty()){
		throw std::underflow_error("underflow exception on call to front()");
	} else {
		return listfront->value;
	}
}

template <class T>
const T& mylist<T>::back() const {
	if (empty()){
		throw std::underflow_error("underflow exception on call to back()");
	} else {
		return listback->value;
	}
}

template <class T>
T& mylist<T>::front() {
	if (empty()){
		throw std::underflow_error("underflow exception on call to front()");
	} else {
		return listfront->value;
	}
}

template <class T>
T& mylist<T>::back() {
	if (empty()){
		throw std::underflow_error("underflow exception on call to back()");
	} else {
		return listback->value;
	}
}

template <class T>
void mylist<T>::push_front(const T& value) {
	node<T>* new_node = new node<T>(value);

	new_node->next = listfront;
	if(empty()){
		listback = new_node;
	} else {
		listfront->prev = new_node;
	}

	listfront = new_node;
	listSize++;
}

template <class T>
void mylist<T>::push_back(const T& value) {
	node<T>* new_node = new node<T>(value);

	new_node->prev = listback;
	if(empty()){
		listfront = new_node;
	} else {
		listback->next = new_node;
	}

	listback = new_node;
	listSize++;
}

template <class T>
void mylist<T>::pop_front() {
	if (empty())
		throw std::underflow_error("underflow exception on call to pop_front()");
	node<T>* del_node = listfront;
	listfront = del_node->next;

	if (listfront == nullptr) {
		listback = nullptr;
	} else {
		listfront->prev = nullptr;
	}

	delete del_node;
	listSize--;
}

template <class T>
void mylist<T>::pop_back() {
	if (empty())
		throw std::underflow_error("underflow exception on call to pop_back()");
	node<T>* del_node = listback;
	listback = del_node->prev;

	if (listback == nullptr) {
		listfront = nullptr;
	} else {
		listback->next = nullptr;
	}

	delete del_node;
	listSize--;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {
	node<T>* current = obj.listfront;
	while(current != nullptr){
		os << current->value << " ";
		current = current->next;
	}

	return os;
}

template <class T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x){
	if (this != &x){
		clear();
		new (this) mylist(x);
	}

	return *this;
}

template <class T>
bool mylist<T>::operator==(const mylist<T>& rhs) const {
	if (this->listSize != rhs.listSize)
		return false;

	if (this->listfront == nullptr && rhs.listfront == nullptr)
		return true;

	const node<T>* p = this->listfront;
	const node<T>* q = rhs.listfront;

	while (p != nullptr) {
		if (p->value == q->value){
			p = p->next;
			q = q->next;
		} else {
			return false;
		}
	}

	return true;
}

template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {
	const node<T>* p = this->listfront;
	const node<T>* q = rhs.listfront;

	while (p != nullptr && q != nullptr) {
	    if (p->value < q->value) {
			return true;
		} else if (p->value > q->value) {
			return false;
		}
    	p = p->next;
		q = q->next;
	}

	if (q == nullptr)
		return false;
    else
	    return true;
}

#endif
