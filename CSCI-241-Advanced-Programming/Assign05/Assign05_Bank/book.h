#ifndef BOOK_H
#define BOOK_H

//----------------------------------------
//  book.h
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

class book {
	private:
		char isbn[11];
		char title[41];
		double price;
		int quantity;

	public:
		book();
		const char* get_isbn() const;
		double get_price() const;
		int fulfill_order(int);
		void print() const;
		int compare(book);
};

#endif
