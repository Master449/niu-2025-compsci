//*******************************************************************
//
//  assign12.cpp
//  CSCI 241 Assignment 12
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************
#include"circle.h"
#include"rectangle.h"
#include"triangle.h"
#include<vector>
#include <iostream>

using std::vector;
using std::cout;

int main() {
    vector<shape*> shape_vector;
    shape_vector.push_back(new circle("green", 10));
    shape_vector.push_back(new rectangle("red", 8,6));
    shape_vector.push_back(new triangle("yellow", 8,4));
    shape_vector.push_back(new triangle("black", 4,10));
    shape_vector.push_back(new circle("orange", 5));
    shape_vector.push_back(new rectangle("blue", 3,7));


    cout << "Printing all shapes...\n\n";
    vector<shape*>::iterator shapeit;
    for (shapeit = shape_vector.begin();shapeit < shape_vector.end();shapeit++) {
        (*shapeit)->print();
    }

    cout << "\n";

    cout << "\nPrinting only circles...\n\n";
    for (shapeit = shape_vector.begin();shapeit < shape_vector.end();shapeit++) {
        if (typeid(*(*shapeit)) == typeid(circle)) 
        {
            (*shapeit)->print();
        }
    }

    for (shapeit = shape_vector.begin();shapeit < shape_vector.end();shapeit++) {
        delete(*shapeit);
    }

    return 0;
}