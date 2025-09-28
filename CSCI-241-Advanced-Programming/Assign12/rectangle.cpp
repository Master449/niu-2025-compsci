//*******************************************************************
//
//  rectangle.cpp
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include "rectangle.h"
#include "shape.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;

rectangle::rectangle(const string& color, int height, int width) : shape(color) {
    this->height = height;
    this->width = width;
}

const void rectangle::print() {
    shape::print();
    cout << " rectangle, height " << height << ", width " << width << ", area " << get_area() << "\n";
}

double rectangle::get_area(){
    double area = 0;
    area = height * width;

    return area;
}