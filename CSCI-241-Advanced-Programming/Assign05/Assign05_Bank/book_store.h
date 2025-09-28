#ifndef BOOK_STORE_H
#define BOOK_STORE_H

//----------------------------------------
//  book_store.h
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

#include <fstream>
#include <string>
#include "book.h"

#define SIZE 30

class book_store {
	private:
		book bookBlock[SIZE];
		int elements;

		/**
		* sort_by_isbn()
		*
		* Sorts the book objects by the isbn.
		* void function does not return anything.
		*
		********************************************************************************/
	    void sort_by_isbn();

		/**
		* binarySearch(const char) const
		*
		* Splits the array into two temp arrays, specified by params 2, 3 and 4.
		*
		* @param 1 The array to be passed.
		*
		********************************************************************************/
		int binarySearch(const char*) const;

	public:
		book_store();
		void read_book_data(const std::string&);
		void process_orders(const std::string&);
		void print() const;
};

#endif
