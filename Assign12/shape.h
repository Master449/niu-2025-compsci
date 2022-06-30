#ifndef SHAPE_H
#define SHAPE_H

//*******************************************************************
//
//  shape.h
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <string>
#include <iostream>

using std::string;

class shape {
    private:
        string color;

    public:
        shape(const string& color);
        virtual ~shape() {}
        virtual double get_area() = 0;
        virtual const void print();
};

#endif