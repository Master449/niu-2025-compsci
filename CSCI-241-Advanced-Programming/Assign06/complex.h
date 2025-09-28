//***************************************************************************
//
//  complex.h
//  CSCI 241 Assignment 6
//
//  Created by David Flowers II (z1942130)
//
//***************************************************************************
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class complex {
    private:
        double real;
        double imaginary;
        
    public:
    
    // Constructors
        complex();
        complex(double r, double i);

    // Setters
        /**
         * @brief Sets the complex object.
         * 
         * @param r is real
         * @param i is imaginary
         */
        void set_complex(double r, double i);

        /**
         * @brief Sets the real object.
         * 
         * @param r is real
         */
        void set_real(double r);

        /**
         * @brief Sets the imaginary object.
         * 
         * @param i is imaginary
         */
        void set_imaginary(double i);

    // Getters
        /**
         * @brief Get the real object
         * 
         * @return real as double
         */
        double get_real() const;

        /**
         * @brief Get the imaginary object
         * 
         * @return imaginary as double
         */
        double get_imaginary()const;

        /**
         * @brief Get the complex object
         * 
         * @return tuple<double, double> 
         */
        tuple<double, double> get_complex() const;

    // Overloaders
        /**
         * @brief adds two complex objects
         * 
         * @param ihs 
         * @param rhs 
         * @return complex 
         */
        friend complex operator+(const complex& ihs, const complex& rhs);

        /**
         * @brief multiplies two complex objects
         * 
         * @param ihs 
         * @param rhs 
         * @return complex 
         */
        friend complex operator*(const complex& ihs, const complex& rhs);

        /**
         * @brief compares two complex objects
         * 
         * @param ihs 
         * @param rhs 
         * @return true if equal
         * @return false if not equa;
         */
        friend bool operator==(const complex& ihs, const complex& rhs);

        /**
         * @brief overloads the stream insertion to print a complex object
         * 
         * @param os 
         * @param rhs 
         * @return ostream& 
         */
        friend ostream& operator<<(ostream& os, const complex& rhs);

        /**
         * @brief overloads the stream extraction operator to read a complex object.
         * 
         * @param is 
         * @param rhs 
         * @return istream& 
         */
        friend istream& operator>>(istream& is, complex& rhs);

    // Other
        /**
         * @brief converts a complex object to string.
         * 
         * @return string 
         */
        string toString() const;
};

#endif