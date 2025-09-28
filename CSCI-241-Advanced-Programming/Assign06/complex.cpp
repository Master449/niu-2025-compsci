//***************************************************************************
//
//  complex.cpp
//  CSCI 241 Assignment 6
//
//  Created by David Flowers II (z1942130)
//
//***************************************************************************
#include <iostream>
#include <vector>
#include <sstream>
#include "complex.h"

using namespace std;

// ------------------------------------ Constructors
complex::complex(){
    set_complex(0, 0);
}

complex::complex(double r, double i){
    set_complex(r, i);
}


// ------------------------------------ Setters
void complex::set_complex(double r, double i) {
    real = r;
    imaginary = i;
}

void complex::set_real(double r){
    real = r;
}

void complex::set_imaginary(double i){
    imaginary = i;
}


// ------------------------------------ Getters
double complex::get_real() const {
    return real;
}

double complex::get_imaginary()const {
    return imaginary;
}

tuple<double, double> complex::get_complex() const {
    return make_tuple(this->real, this->imaginary);
}

// ------------------------------------ Overloaders
complex operator+(const complex& ihs, const complex& rhs){
    double r = ihs.get_real() + rhs.get_real();
    double i = ihs.get_imaginary() + rhs.get_imaginary();

    complex result(r, i);
    return result;
}

complex operator*(const complex& ihs, const complex& rhs){
    double r = ihs.get_real() * rhs.get_real() - ihs.get_imaginary() * rhs.get_imaginary();
    double i = ihs.get_real() * rhs.get_imaginary() + ihs.get_imaginary() * rhs.get_real();

    complex result(r, i);
    return result;
}

bool operator==(const complex& ihs, const complex& rhs){
    if(ihs.get_real() != rhs.get_real()){ 
        return false;
    } else {
        return true;
    }
}

ostream& operator<<(ostream& os, const complex& rhs){
    os << rhs.toString()+"";
    return os;
}

istream& operator>>(istream& is, complex& rhs){
    char temp;

    is >> temp;
    is >> rhs.real;
    is >> temp;
    is >> rhs.imaginary;
    is >> temp;

    return is;
}

// ------------------------------------ Other
string complex::toString() const {
    ostringstream strs;

    strs << this->get_real();
    string output = "(" + strs.str() + ", ";
    
    strs.str("");
    strs << this->get_imaginary();

    output = output + strs.str() + ")";

    return output;
}
