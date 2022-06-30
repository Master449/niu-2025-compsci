//-----------------------------------------
//  book.cpp
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "book.h"

using namespace std;

book::book() {
	strcpy(isbn, "None");
	strcpy(title, "None");
	price = 0;
	quantity = 0;
}

//All these functions do is return values from the object
const char* book::get_isbn() const { return isbn; }
double book::get_price() const { return price; }


int book::fulfill_order(int oqty) { // oqty stands for order quantity.
    int shipped;

	if (oqty < 0) {
		shipped = 0;
	} else if (oqty <= quantity) {
		quantity = quantity - oqty;
		shipped = oqty;
	} else {
		shipped = quantity;
        quantity = 0;
	}
	return shipped;
}

void book::print() const {
	cout << setw(14) << left << isbn;
	cout << setw(44) << left << title;
	cout << setw(5) << right << fixed << setprecision(2) << price;
	cout << setw(6) << right << quantity << endl;
}

int book::compare(book b){
	return strcmp(isbn, b.get_isbn());
}
