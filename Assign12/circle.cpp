//*******************************************************************
//
//  circle.cpp
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "circle.h"
#include "shape.h"
#include <iostream>
#include <cmath>
#include <string>

using std::cout;
using std::endl;
using std::pow;
using std::string;

const static double pizza_pi = 3.14159;

circle::circle(const string& color, int radius) : shape(color) {
    this->radius = radius;
}

double circle::get_area() {
    double area = 0;
    area = (pizza_pi * pow(radius, 2));

    return area;
}

const void circle::print() {
    shape::print();
    cout << " circle, radius " << radius << ", area " << circle::get_area() << endl;
}