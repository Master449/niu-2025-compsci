//*******************************************************************
//
//  triangle.h
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "triangle.h"
#include "shape.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

triangle::triangle(const string& color, int height, int base) : shape(color) {
    this->height = height;
    this->base = base;
}

double triangle::get_area(){
    double area = 0;
    area = (0.5 * base * height);

    return area;
}

const void triangle::print() {
    shape::print();
    cout << " triangle, height " << height << ", base " << base << ", area " << get_area() << "\n";
}