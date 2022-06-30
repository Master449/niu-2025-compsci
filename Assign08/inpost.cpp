//*******************************************************************
//
//  inpost.cpp
//  CSCI 241 Assignment 8
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "inpost.h"
#include "mystack.h"
#include <iostream>
#include <cctype>
#include <string>

using std::cout;
using std::string;

// These functions both do the same thing but for different 
// Operands, they take a char and return the int version of
// operand to be used in math and Assigns a score to each 
// operand to nab the correct one.
int getOperand(char);
int getOperand2(char);

string convert(const string &infix){
	mystack opstack;
	string postfix;
	int length = infix.length();
	int opscore;

	for (int i = 0; i < length; i++){
		if (isspace(infix[i]) != 0){
			//Skip spaces, so nothing here
		} else if (isdigit(infix[i])) {
			postfix += infix[i];
			if (!isdigit(infix[i + 1])){
				postfix += " ";
			}
		} else if (islower(infix[i])){
			postfix += infix[i];
			postfix += " ";
		} else if (infix[i] == ')') {
			while (opstack.top() != '(') {
				postfix += opstack.top();
				postfix += " ";
				opstack.pop();
			}
			opstack.pop();
		} else {
			opscore = getOperand(infix[i]);

			if (opstack.empty() || opscore > getOperand2(opstack.top())){
				opstack.push(infix[i]);
			} else {
				while (!opstack.empty() && opscore < getOperand2(opstack.top()))  {
					postfix += opstack.top();
					postfix += " ";
					opstack.pop(); 
				}
				opstack.push(infix[i]);
			}
		}
	}

	while (opstack.empty() == false){
		postfix += opstack.top();
		postfix += " ";
		opstack.pop();
	}

	return postfix;
} 

int getOperand(char op)
{
	int opscore;
	switch (op) {
		case '~':
			opscore = 6;
			break;

		case '^':
			opscore = 6;
			break;

		case '*':
			opscore = 3;
			break;

		case '/':
			opscore = 3;
			break;

		case '+':
			opscore = 1;
			break;

		case '-':
			opscore = 1;
			break;

		case '(':
			opscore = 100;
			break;

		default:
			cout << "Invalid Operator: " << op << endl;
			opscore = -1;
	}
	return opscore;
}

int getOperand2(char op)
{
	int opscore;
	switch (op) {
		case '~':
			opscore = 5;
			break;

		case '^':
			opscore = 5;
			break;

		case '*':
			opscore = 4;
			break;

		case '/':
			opscore = 4;
			break;

		case '+':
			opscore = 2;
			break;

		case '-':
			opscore = 2;
			break;

		case '(':
			opscore = 0;
			break;
			
		default:
			cout << "Invalid Operator: " << op << endl;
			opscore = -1;
	}
	return opscore;
}