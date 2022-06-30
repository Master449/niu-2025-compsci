//----------------------------------------
//  book_store.cpp
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "book_store.h"

using namespace std;

book_store::book_store() {
	// Init the obj and clears the elements amount in the array
	elements = 0;
}

void book_store::read_book_data(const string& s) {
	ifstream file;
	file.open(s);

	// File error check
	if (!file) {
		cout << "Error: read_book_data file object";
		return;
	}

	// If it gets here then it starts reading into the book_store
	file.read((char*) this, sizeof(book_store));

	// Once thats done, closes the file and sorts
	file.close();
	sort_by_isbn();
}

void book_store::sort_by_isbn(){
	int i,j;
	book k;

	for (i = 1; i < elements; i++) {
		k = bookBlock[i];
		j = i - 1;

		while (j >= 0 && bookBlock[j].compare(k)>0){
			bookBlock[j + 1] = bookBlock[j];
			j = j - 1;
		}

		bookBlock[j + 1] = k;
	}
}

void book_store::process_orders(const string& s) {
	ifstream file(s);
	char isbn[11];
	int qty;
	char orderNo[10];

	// Error check to make sure file opened
	if (!file) {
		cout << "Error: process_orders file object" << endl;
		return;
	}

	// Just the header for this section
	cout << "Order Listing" << endl << endl;

	// Loops through and prints order number
	while (file >> orderNo) {
		file >> isbn;
		file >> qty;

		int i=binarySearch(isbn);
		int q;
		if (i == -1)
			cout << "Order #" << orderNo << ":"
			 << " error - ISBN " << isbn << " does not exist" << endl;
		else{
			q=bookBlock[i].fulfill_order(qty);
	    	if (q == 0)
		    	cout <<"Book with ISBN " << isbn << " quantity not available!"<<endl;
	    	else{
		    	cout <<"Order #"<< orderNo << ":";
			cout <<" ISBN "<< isbn << ", ";
			cout << q << " of " << qty << " shipped, ";
			cout << "order total $" << q*bookBlock[i].get_price() << endl;

			}
		}
	}

	file.close();
}


void book_store::print() const {

	// Prints the title and then the column headers
	cout << "Book Inventory Listing" << endl << endl;

	cout << setw(14) << left << "ISBN";
	cout << setw(44) << left << "Title";
	cout << setw(5) << right << "Price";
	cout << setw(8) << right << "Qty." << endl << endl;

	// Loops through and prints each book object
	for (int i=0; i < elements; i++){
		bookBlock[i].print();
	}
}


int book_store::binarySearch(const char *isbn) const {
	int l=0;
	int r = elements - 1;

	// I think you would clasify this as a binary insertion sort
	while(l <= r){
		int mid = (l + r) / 2;
		if (strcmp(isbn, bookBlock[mid].get_isbn()) == 0)
			return mid;
		if (strcmp(isbn, bookBlock[mid].get_isbn()) < 0)
			r=mid-1;
		else
			l=mid+1;
	}
	return -1;
}
