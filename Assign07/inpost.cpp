//*******************************************************************
//
//  inpost.cpp
//  CSCI 241 Assignment 7
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include"inpost.h"
#include"mystack.h"

string convert(const string& infix){
	mystack stack;
	stack.reserve(10);
	stack.push('(');

	string output = "";
	int n = infix.size();

	for(int i = 0; i < n; i++){

		char ch = infix[i];

		if(isalnum(ch)){
			output = output + ch;
		} else if(ch=='('){
			stack.push('(');
		} else if(ch==')'){

			while(stack.top() != '(' ){
				output = output + stack.top() + ' ';
				stack.pop();
			}

			stack.pop();

		} else {

			int p1=precedence(ch);
			int p2=precedence(stack.top());

			while(p1 <= p2){
				output = output + stack.top() + ' ';
				stack.pop();
				p2=precedence(stack.top());
			}

			stack.push(ch);
			}
		}

		while(stack.top() != '('){
			output = output + stack.top() + ' ';
			stack.pop();
		}

	return output;
}


int precedence(char x){

	switch(x){
		case '(':
			return 0;

		case '+':
		case '-':
			return 1;

		case '*':
		case '/':
			return 2;

		case '^':
		case '~':
			return 3;

		default : return 999;
	}
}
