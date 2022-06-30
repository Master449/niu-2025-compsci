//*******************************************************************
//
//  shape.cpp
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

shape::shape(const string& color) {
    this->color = color;
}

const void shape::print() {
    cout << color;
}