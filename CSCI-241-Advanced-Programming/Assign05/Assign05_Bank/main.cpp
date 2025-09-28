//-----------------------------------------
//  main.cpp
//
//  CSCI 241 Assignment 5
//  Created by David Flowers II (z1942130)
//-----------------------------------------

#include <iostream>
#include "book_store.h"

using namespace std;

int main() {

	// Creates the big object, of objects
	book_store bkstore;

	// Reads the data and then prints
	bkstore.read_book_data("bookdata");
	bkstore.print();
	cout << endl;

	// Takes in the orders from orders.txt and prints once again
	bkstore.process_orders("orders.txt");
	cout << endl;
	bkstore.print();
	return 0;
}
