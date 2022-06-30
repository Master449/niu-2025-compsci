//*******************************************************************
//
//  eval.cpp
//  CSCI 241 Assignment 8
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "mystack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::stoi;

int evaluate(const string& postfix) {
    string tok;
    stringstream ss(postfix);
    mystack s;

    while (ss >> tok) {
        char t0 = tok.at(0);
        
        if (isdigit(t0)) {
            s.push(stoi(tok));
        } else if (islower(t0)) {
            s.push(t0-'a');
        } else if (t0 == '~') {
            int i = s.top();
            s.pop();
            s.push(-i);
        } else {
            int right = s.top();
            s.pop();

            int left = s.top();
            s.pop();

            switch(t0) {
                case '+':
                    s.push(left + right);
                    break;
                    
                case '-':
                    s.push(left - right);
                    break;

                case '*':
                    s.push(left * right);
                    break;

                case '/':
                    if (right == 0) {
                        s.push(0);
                        cout << "*** Division by 0 ***" << endl;
                    } else {
                        s.push(left / right);
                    }
                    break;

                case '^':
                    s.push(pow(left, right));
                    break;

                default:
                    cout << "Error " << t0 << endl;
            }
        }
    }
    return s.top(); 
} 