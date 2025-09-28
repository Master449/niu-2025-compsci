//-----------------------------------------
//  main.cpp
//
//  CSCI 241 Assignment 5
//  Created by David Flowers II (z1942130)
//-----------------------------------------

#include <iostream>
#include "bank.h"

using namespace std;

int main() {

	// Creates the big object, of objects
	bank bonk;

	// Reads the data and then prints
	bonk.read_accounts("accounts");
	bonk.print();

	// Takes in the orders from transactions.txt and prints once again
	bonk.process_transactions("transactions.txt");
	bonk.print();
	return 0;
}
