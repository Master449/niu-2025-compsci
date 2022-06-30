#ifndef ACCOUNT_H
#define ACCOUNT_H

//----------------------------------------
//  account.h
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

class account {
	private:
		char account_num[11];
		char name[21];
		double balance;

	public:

		// Default Constructor
		account();

		// The first 3 are self explanitory, but they return
		// the variable thats in the name of the func.
		const char* get_account_number() const;
		const char* get_name() const;
		double get_balance() const;

		/**
		* void process_deposit(double)
		*
		* This member function takes a double deposit amount and adds it to the balance for the account.
		*
		* @param 1 The amount to be deposited by the account.
		*
		* @return returns true if succeeded, false if failed
		*
		********************************************************************************/
		void process_deposit(double);

		/**
		* bool process_withdrawal(double)
		*
		* This member function takes a double withdrawal amount and checks to make sure not
		* to overdraft the account. It then returns true if it succeeded and false if not.
		*
		* @param 1 The amount to be withdrawan by the account.
		*
		********************************************************************************/
		bool process_withdrawal(double);

		/**
		* void print()
		*
		* This member function has no parameters and returns nothing.
		* It prints the values of the data members for the account.
		*
		********************************************************************************/
		void print() const;

		/**
		* int compare(account)
		*
		* Compares two account numbers (used for sorting the accounts)
		*
		* @param 1 The account to be compared with the current (uses this keyword).
		*
		********************************************************************************/
		int compare(account);
};

#endif
