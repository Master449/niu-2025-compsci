#ifndef BANK_H
#define BANK_H

//----------------------------------------
//  bank.h
//  CSCI 241 Assignment 5
//
//  Created by David Flowers II (z1942130)
//----------------------------------------

#include <fstream>
#include <string>
#include "account.h"

#define SIZE 20

class bank {
	private:
		char bankName[31];
		account accountBlock[SIZE];
		int elements;

	    void sort_by_account();

	public:

		// Default class constructor
		bank();

		/**
		* void read_accounts(const std::string&)
		*
		* This member function takes one parameter, a string that contains the name of a file.
		* This function reads accounts into the program from a file.
		*
		* @param 1 The account
		*
		********************************************************************************/
		void read_accounts(const std::string&);

		/**
		* void process_transactions(const std::string&)
		*
		* This member function checks the file records for deposit or withdrawals and 
		* applies them to the corresponding account. It then prints a report.
		*
		* @param 1 A string that contains the file name to be opened.
		*
		********************************************************************************/
		void process_transactions(const std::string&);

		/**
		* void prrint() const
		*
		* This member function prints all the accounts in the bank.
		* It takes no parameters and returns nothing.
		*
		********************************************************************************/
		void print() const;

		/**
		* void binarySearch(const char*)
		*
		* This member function searches through the input from the file to find the
		* corresponding account number to then apply a deposit or withdrawal.
		*
		* @param 1 the file name to be opened.
		*
		* @return returns an error message if the transaction process failed.
		*
		********************************************************************************/
		int binarySearch(const char*) const;
};

#endif
