#ifndef RECTANGLE_H
#define RECTANGLE_H

//*******************************************************************
//
//  rectangle.h
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <string>
#include "shape.h"

using std::string;

class rectangle : public shape{
    private:
        int height;
        int width;

    public:
        rectangle(const string&, int, int);
        const void print();
        double get_area();
    
};
#endif