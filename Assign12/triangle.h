#ifndef TRIANGLE_H
#define TRIANGLE_H

//*******************************************************************
//
//  triangle.h
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <string>
#include "shape.h"

using std::string;

class triangle : public shape{
    private:
        int height;
        int base;

    public:
        triangle(const string&, int, int);
        double get_area();
        const void print();
    
};
#endif