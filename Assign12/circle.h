#ifndef CIRCLE_H
#define CIRCLE_H

//*******************************************************************
//
//  circle.h
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <string>
#include "shape.h"

using std::string;

class circle : public shape {
    private:
        int radius;
    public:
        circle(const string&, int);
        double get_area();
        const void print();

};
#endif