//-----------------------------------------
//  account.cpp
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "account.h"

using namespace std;

account::account() {
	strcpy(account_num, "None");
	strcpy(name, "None");
	balance = 0;
}

//All these functions do is return values from the object
const char* account::get_account_number() const { return account_num; }
const char* account::get_name() const { return name; } 
double account::get_balance() const { return balance; }

void account::process_deposit(double depo) {
	balance += depo;
}

bool account::process_withdrawal(double with) {
	if (balance >= with){
		balance = balance - with;
		return true;
	} else {
		return false;
	}
}

void account::print() const {
	cout << "Account Number: " << account_num << endl;
	cout << "Name: " << name << endl;
	cout << "Balance: $" << fixed << setprecision(2) << balance << "\n\n";
}

int account::compare(account b){
	return strcmp(account_num, b.get_account_number());
}
