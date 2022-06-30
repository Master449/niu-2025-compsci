//*******************************************************************
//
//  inpost.h
//  CSCI 241 Assignment 9
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#ifndef INPOST_H
#define INPOST_H

#include <iostream>
using namespace std;

string convert(const string& infix);
int precedence(char x);

#endif // INPOST_H