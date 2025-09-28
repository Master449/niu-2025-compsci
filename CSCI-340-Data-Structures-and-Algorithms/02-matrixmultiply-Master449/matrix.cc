//*************************************************************************
//
//	David Flowers II
//	Z1942130
//	CSCI 340 - 0004
//
//	I certify that this is my own work and where appropriate an extension 
//	of the starter code provided for the assignment.
//
//*************************************************************************

#include <iostream>
#include <iomanip>
#include <assert.h>
#include "matrix.h"

/**
 * @brief matrix Constructor
 *
 * Initializes the matrix class as needed and uses the
 * resize member function.
 *
 * @param rows the num of rows in the matrix
 * @param cols the num of columns in the matrix
 */
matrix::matrix(unsigned int rows, unsigned int cols) {
    // All it does is call the resize function to establish the matrix
    matrix::resize(rows, cols);
}

/**
 * @brief Resizes the matrix vector class
 *
 * Resizes the mat vector to have rows elements,
 * and then resizes each of those to have col elements
 *
 * @param rows the number of rows to be resized to
 * @param cols the number of columns to be resized to
 */
void matrix::resize(unsigned int rows, unsigned int cols) {

    // First resizes the first vector
    mat.resize(rows);

    // Then loops through each of those vectors resizing each of them and then iterates
    for(unsigned int i = 0; i < getRows(); i++){
        mat[i].resize(cols);
    }
}

/**
 * @brief Loads the matrix from a file
 *
 * Starts at the beginning of the file and takes in
 * the number of rows and columns. Then loops through
 * and intakes each number one by one.
 *
 * @param is the file to be loaded into the matrix class
 */
void matrix::load(std::istream &is) {
    int rows;   // Rows from file
    int cols;   // Columns from file

    // First takes in the rows and columns needed from the first two numbers
    is >> rows;
    is >> cols;

    // resizes the matrix as needed
    matrix::resize(rows, cols);

    // Iterates through the rows
    for (int i = 0; i < rows; i++){

        // Iterates through each row vector and inputs the numbers one by one
        for (int j = 0; j < cols; j++){
            is >> matrix::at(i, j);
        }
    }
}

/**
 * @brief Prints the matrix
 *
 * Loops through the matrix one by one, with specified column
 * width. Fancy looking with nice boxes using pipe symbols.
 *
 * @param colWidth the column width the numbers need in setw
 */
void matrix::print(int colWidth) const {
    std::cout << getRows() << " x " << getCols() << "\n";

    /* This snippet prints a hyphen equal to the colWidth passed
       Then adds 2 hyphens because further down it adds " |"  
       Then adds 1 hyphens because further down it adds "|"   */
    std::cout << std::string(getCols()*(colWidth + 2) + 1, '-') << "\n";

    /* The loop starts by printing a pipe symbol for each
       new row that it outputs */
    for (unsigned int i = 0; i < getRows(); i++) {
        std::cout << "|";

        /* Then prints the number with a width of colWidth.
           Followed by a space and then another pipe.       */
        for (unsigned int j = 0; j < getCols(); j++){
            std::cout << std::setw(colWidth) << matrix::at(i, j);
            std::cout << " |";
        }

        std::cout << "\n";
    }

    // This statement from above is used again for the bottom row
    std::cout << std::string(getCols()*(colWidth + 2) + 1, '-') << "\n";
}

/**
 * @brief Overloads the * operator
 *
 * Overloads the multipication operator to accept two matrix objects. This
 * allows main.cc to multiply the left hand matrix by the right hand matrix
 * using the dot method.
 *
 * @param rhs This is the right hand side operator when the * is called
 *
 * @return matrix as the result
 */
matrix matrix::operator*(const matrix &rhs) const {
    matrix x;           // Resulting Matrix
    matrix y = *this;   // operator that called the function, so that would be a
    matrix z = rhs;     // right hand operator, so in main.cc that would be b

    // Added the assert function call to make sure
    // the matrices are compatible for multiplication.
    assert((y.getRows() == z.getCols()));

    // Resizes the resulting matrix to have the number of rows
    // of the first matrix and the number of columns of the second
    x.resize(y.getRows(), z.getCols());

    unsigned int i, j, k;  // These are the iterators for the 3 loops below

    for (i = 0; i < x.getRows(); i++){
        for (j = 0; j < x.getCols(); j++){
            for (k = 0; k < y.getCols(); k++){
                x.at(i, j) += y.at(i, k) * z.at(k, j);
            }
        }
    }

    return x;
}