//----------------------------------------
//  bank.cpp
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "bank.h"

using namespace std;

bank::bank() {
	// Init the obj and clears the elements amount in the array
	elements = 0;
}

void bank::read_accounts(const string& s) {
	ifstream file;
	file.open(s);

	// File error check
	if (!file) {
		cout << "Error: read_bank_data file object";
		return;
	}

	// If it gets here then it starts reading into the bank
	file.read((char*) this, sizeof(bank));

	// Once thats done, closes the file and sorts
	file.close();
	sort_by_account();
}

void bank::sort_by_account(){
	int i,j;
	account k;

	for (i = 1; i < elements; i++) {
		k = accountBlock[i];
		j = i - 1;

		while (j >= 0 && accountBlock[j].compare(k)>0){
			accountBlock[j + 1] = accountBlock[j];
			j = j - 1;
		}

		accountBlock[j + 1] = k;
	}
}

void bank::process_transactions(const string& s) {
	ifstream file(s);
	char date[6];
	char account_num[11];
	char type;
	double amount;

	// Error check to make sure file opened
	if (!file) {
		cout << "Error: process_orders file object" << endl;
		return;
	}

	// Just the header for this section
	cout << "Transaction Report" << "\n\n";

	// Print Column Headers
	cout << setw(8) << left << "Date";
	cout << setw(13) << left << "Account";
	cout << setw(7) << left << "Type";
	cout << setw(11) << left << "Amount";
	cout << setw(13) << left << "New Balance" << "\n\n";

	// Loops through and prints transactions
	while (file >> date) {
		file >> account_num;
		file >> type;
		file >> amount;

		int i=binarySearch(account_num);

		cout << setw(8) << left << date;
		cout << setw(13) << left << account_num;
		cout << setw(7) << left << type;
		cout << setw(9) << right << amount << "  ";
		
		if (i == -1) {
			cout << "*** Invalid account number ***" << endl;
		} else {
            if (type == 'D') {
			    accountBlock[i].process_deposit(amount);
		        cout << setw(15) << left << accountBlock[i].get_balance() << endl;
		    } else {
                if (accountBlock[i].process_withdrawal(amount)) {
		            cout << setw(15) << left << accountBlock[i].get_balance() << endl;
		        } else {
			        cout << "*** Insufficient funds ***" << "\n";
		        }
            }
        }
	}

	file.close();
}

void bank::print() const {

	// Prints the title and then the column headers
	cout << "\nAccount Listing for First National Bank" << "\n\n";

	// Loops through and prints each account object
	for (int i=0; i < elements; i++){
		accountBlock[i].print();
	}
}


int bank::binarySearch(const char *account) const {
	int l=0;
	int r = elements - 1;

	while(l <= r){
		int mid = (l + r) / 2;
		if (strcmp(account, accountBlock[mid].get_account_number()) == 0)
			return mid;
		if (strcmp(account, accountBlock[mid].get_account_number()) < 0)
			r=mid-1;
		else
			l=mid+1;
	}
	return -1;
}
