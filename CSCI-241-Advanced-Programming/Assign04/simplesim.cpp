//-----------------------------------------------
// simplesim.cpp
// CSCI 241 Assignment 4
//
// Created by David Flowers II (z1942130).
//------------------------------------------------

#include <iostream>
#include <iomanip>

#include "sml.h"
#include "simplesim.h"

using namespace std;

// Sets all memory spots to uninitialized
simplesim::simplesim(){
	for (int i = 0; i < 100; i++)
		memory[i] = 7777;
}

// Reads a program and loads into memory. Return True = Success
bool simplesim::load_program(){
	int count = 0;      // Count of words read
	int instruction;    // Word being read

	while (cin >> instruction && instruction != -99999){
		if (invalid_word(instruction)){
			cout << "*** ABEND: pgm load: invalid word ***\n";
			return false;
		}

		if (count >= 100){
			cout << "*** ABEND: pgm load: pgm too large ***\n";
			return false;
		}

		memory[count] = instruction;
		count++;

	}

	return true;
}

// Executes program
void simplesim::execute_program(){
	bool done = false;

	while (!done){
	// instruction fetch
		if (instruction_counter >= 0 && instruction_counter <= 99){ 
			instruction_register = memory[instruction_counter];

			operation_code = instruction_register / 100;
			operand = instruction_register % 100;

		} else {
			cout << "*** ABEND: addressability error ***\n";
			return;
		}

	        // instruction execute
		// I hope the names for the cases are pretty self explanitory on what they do
		switch (operation_code) {
			case READ:

				// Shoutout to Professor McMahon for the assistance with the read one
				int word;

				cin >> word;

				if (word >= -9999 && word <= 9999){
					memory[operand] = word;
					cout << "READ: " << showpos << internal << setfill('0')
				         << setw(5) << word << endl;
				} else {
					cout << "*** ABEND: illegal input ***\n";
					return;
				}
				break;

			case WRITE:
				cout << showpos << internal << setfill('0') << setw(5)
				     << memory[operand] << endl;
				break;

			case HALT:
				cout << "*** Simplesim execution terminated ***\n";
				done = true;
				break;

			case LOAD:
				accumulator = memory[operand];
				break;

			case STORE:
				memory[operand] = accumulator;
				break;

			case ADD:
				if (accumulator + memory[operand] > 9999){
					cout << "*** ABEND: overflow ***\n";
					return;
				} else if (accumulator + memory[operand] < -9999){
					cout << "*** ABEND: underflow ***\n";
					return;
				} else {
					accumulator = accumulator + memory[operand];
				}
				break;

			case SUBTRACT:
				if (accumulator - memory[operand] > 9999){
					cout << "*** ABEND: overflow ***\n";
					return;
				} else if (accumulator - memory[operand] < -9999){
					cout << "*** ABEND: underflow ***\n";
					return;
				} else {
					accumulator = accumulator - memory[operand];
				}
				break;

			case MULTIPLY:
				if (accumulator * memory[operand] > 9999){ 
					cout << "*** ABEND: overflow ***\n";
					return;
				} else if (accumulator * memory[operand] < -9999){
					cout << "*** ABEND: underflow ***\n";
					return;
				} else {
					accumulator = accumulator * memory[operand];
				}
				break;

			case DIVIDE:
				if (memory[operand] == 0) {
					cout << "*** ABEND: attempted division by 0 ***\n";
					return;
				} else {
					accumulator = accumulator / memory[operand];
				}
				break;

			case BRANCH:
				instruction_counter = operand;
				break;

			case BRANCHNEG:
				if (accumulator < 0) {
					instruction_counter = operand;
				} else {
				    instruction_counter++;
                }
				break;

			case BRANCHZERO:
				if (accumulator == 0) {
					instruction_counter = operand;
				} else {
				    instruction_counter++;
                }
				break;

			default:
				cout << "*** ABEND: invalid opcode ***\n";
				return;
		}

		// When (or if) the program gets here, it interates 1 instruction forward
		if ((operation_code < BRANCH || operation_code > BRANCHNEG) 
            && !done) { 
            instruction_counter++; 
        }

	}
}

//Dumps register and memory.
void simplesim::dump() const {

	// Print the registers
	cout << "\nREGISTERS:\n";

	cout << setw(24) << left << setfill(' ') << "accumulator: ";
	cout << setw(5) << internal << setfill('0') << showpos << accumulator << endl;

	cout << setw(24) << left << setfill(' ') << "instruction_counter: ";
	cout << setw(2) << internal << setfill('0') << noshowpos 
         << instruction_counter << endl;

	cout << setw(24) << left << setfill(' ') << "instruction_register: ";
	cout << setw(5) << internal << setfill('0') << showpos << instruction_register 
         << endl;

	cout << setw(24) << left << setfill(' ') << "operation_code: ";
	cout << setw(2) << internal << setfill('0') << noshowpos << operation_code 
         << endl;

	cout << setw(24) << left << setfill(' ') << "operand: ";
	cout << setw(2) << internal << setfill('0') << noshowpos << operand << endl;

	// Print memory
	cout << "\nMEMORY:\n";

	cout << "  ";

	// Prints the headers for the columns
	for (int i = 0; i < 10; i++) { cout << setw(6) << right << setfill(' ') << noshowpos << i; }

	// Interates through the memory spots, if the spot in memory, modulos = 0 it goes to a new line
	for (int i = 0; i < 100; i++) {
		if ((i % 10) == 0){ cout << endl << setw(2) << right << setfill(' ') << noshowpos << i; }
		cout << " " << setw(5) << internal << setfill('0') << showpos << memory[i];
	}

	// Finally at the end, just prints a newline
	cout << endl;
}

// This was prewritten from the skeleton code, but it just checks to see if the word sent was valid
bool simplesim::invalid_word(int word) const{
	if (word < -9999 || word > 9999)
		return true;
	else
		return false;
}
