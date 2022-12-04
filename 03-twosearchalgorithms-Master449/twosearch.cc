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

#include "twosearch.h"

#include <getopt.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


/**
* see: 
* https://en.wikipedia.org/wiki/Usage_message
* https://www.ibm.com/docs/en/aix/7.2?topic=commands-usage-statements
*
* @param a0 The value of argv[0] (the name of the command) so that it 
*   can be printed.
*
* @note This function will terminate the application via exit(1).
******************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-l rand_low] [-h rand_high] [-a a_size] [-b b_size] [-x a_seed] [-y b_seed] [-c print_cols] [-w col_width]" << std::endl;
    std::cerr << "    rand_low   = rand() low bound (default=1)" << std::endl;
    std::cerr << "    rand_high  = rand() high bound (default=1000)" << std::endl;
    std::cerr << "    a_size     = size of vector A (default=200)" << std::endl;
    std::cerr << "    b_size     = size of vector B (default=100)" << std::endl;
    std::cerr << "    a_seed     = random seed for vector A (default=1)" << std::endl;
    std::cerr << "    b_seed     = random seed for vector B (default=3)" << std::endl;
    std::cerr << "    print_cols = number of colums per line (default=16)" << std::endl;
    std::cerr << "    col_width  = printed column value width (default=4)" << std::endl;
    exit(1);
} // End of usage()

/**
* Parse the command-line args, create and sort vector A, create vector B,
* search vector A for those elements appearing in vector B using both
* a linear and binary search, and print the hit-rate (the percentage of 
* items in B that have been located in A.)
*
* If an invalid command-line arg is encountered, print a Usage statement 
* and terminte with an exit-status of 1.
*
* @return zero
******************************************************************************/
int main(int argc, char **argv)
{
    // Demonstrate the use of getopt() to override default config parameters 
    int rand_low = 1;
    int rand_high = 1000;
    int a_size = 200;
    int b_size = 100;
    int a_seed = 1;
    int b_seed = 3;
    int print_cols = 16;
    int col_width = 4;
    int hits = 0;

    int opt;
    // see: http://faculty.cs.niu.edu/~winans/CS340/2022-sp/#getopt
    while ((opt = getopt(argc, argv, "a:b:c:h:l:w:x:y:")) != -1)
    {
        switch(opt)
        {
        case 'a':
            // see https://en.cppreference.com/w/cpp/string/basic_string/stol
            a_size = std::stoi(optarg); // override the default for a_size
            break;

        case 'b':
            b_size = std::stoi(optarg);
            break;
        case 'c':
            print_cols = std::stoi(optarg);
            break;
        case 'h':
            rand_high = std::stoi(optarg);
            break;
        case 'l':
            rand_low = std::stoi(optarg);
            break;
        case 'w':
            col_width = std::stoi(optarg);
            break;
        case 'x':
            a_seed = std::stoi(optarg);
            break;
        case 'y':
            b_seed = std::stoi(optarg);
            break;
            
        default:
            // got an arg that is not recognized...
            usage(argv[0]);     // pass the name of the program so it can print it
        }
    }

    // Make sure there are not any more arguments (after the optional ones)
    if (optind < argc)
        usage(argv[0]);

    // Add application logic here...

    std::vector<int> A, B;

    A.resize(a_size);
    B.resize(b_size);

    init_vector(A, a_seed, rand_low, rand_high);
    init_vector(B, b_seed, rand_low, rand_high);

    // Prints vector A then sorts it
    std::cout << "A vector:\n";
    print_vector(A, print_cols, col_width);
    sort_vector(A);

    // Prints the sorted vector A
    std::cout << "A vector sorted:\n";
    print_vector(A, print_cols, col_width);

    // Prints vector B
    std::cout << "B vector:\n";
    print_vector(B, print_cols, col_width);
    
    // Searches for the elements in vector B in vector A wioth linear search
    // then prints the % stat of successes
    hits = search_vector(A, B, linear_search);
    std::cout << "Linear Search: ";
    print_stat(hits, b_size);

    // Sea rches for the elements in vector B in vector A with binary search
    hits = 0;
    hits = search_vector(A, B, binary_search);
    std::cout << "Binary Search: ";
    print_stat(hits, b_size);

    return 0;

} // End of main()

/**
* @brief Initializes the vector filled with random numbers.
*
* @param vec vector to be initialized
* @param seed seed to be used for the rand function
* @param lo lower bound for rand
* @param hi upper bound for rand
*
******************************************************************************/
void init_vector(std::vector<int> &vec, int seed, int lo, int hi) {
    // inserts the specified seed to be used
    srand(seed);

    // loops through the vector and fills it with random numbers from range hi to lo
    for (int i = 0; i < int(vec.size()); i++) {
        vec[i] = rand() % (hi - lo + 1) + lo;
    }
}

/**
* @brief Prints the vector passed.
*
* This function also formats the printing according to the directions in
* the assignment. So it should have pipes and spaces in the correct place
*
* @param v vector to be printed
* @param print_cols columns to be printed
* @param col_width how wide the printed columns should be
*
******************************************************************************/
void print_vector(const std::vector<int> &v, int print_cols, int col_width) {
    /* This snippet prints a hyphen equal to the colWidth passed
       Then adds 2 hyphens because further down it adds " |" */
    std::cout << std::string(print_cols*(col_width + 2), '-') << "-" << std::endl;

    /* K is used to keep track of how many columns have been printed
       so that it can print the blank cells in the outputs */
    int k = print_cols;

    for (int i = 0; i < int(v.size()); i++) {
        std::cout << "|" << std::setw(col_width) << v[i] << " ";
        k--;

        // Modulo check for end of row
        if (i % print_cols == print_cols - 1) {
            std::cout << "|" << std::endl;

            // if it is not the last row, reset k to print_cols
            if (i != int(v.size()) - 1) {
                k = print_cols;
            }
        }
    }

    // This loop prints the blank cells at the end of the row using k
    if (k > 0) {
       for (int i = 0; i < k; i++) {
          std::cout << "| " << std::setw(col_width) << " ";
       }
       std::cout << "|" << std::endl;
    }

    // This snippet is a copy paste of hyphen printing.
    std::cout << std::string(print_cols*(col_width + 2), '-') << "-" << std::endl;

}

/**
* @brief Uses the stl sort function to sort the vector passed to it.
*
* @param v vector to be sorted
*
******************************************************************************/
void sort_vector(std::vector<int> &v) {
    // Just calls the STL sort function
    std::sort(v.begin(), v.end());
}

/**
* @brief Generic search algorithm to sort the vector passed.
*
* This takes pointers to the search routine p() that must be called once
* for each element that is in v2 to be searched for in v1. It also counts
* the number of successful searches and returns that value.
*
* @param v1 vector to searched
* @param v2 vector to be searched for
* @param p pointer called for each element in v2 that is in v1
*
* @return hits = number of successes
******************************************************************************/
int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int)) {
    int hits = 0;

    // Loops through the vector and calls the pointer function p() for each element in v2
    for (int i = 0; i < int(v2.size()); i++) {
        if (p(v1, v2[i]) == true) {
            hits++; // Increments hits if the search is successful
        }
    }
    
    return hits; // Used to sent the print_stat function
}

/**
* @brief Prints the percent of successful searches.
*
* Prints the percent of successful searches with a 
* floating point number to stdout
*
* @param found total number of successful searches
* @param total the size of the test vector that was searched
*
******************************************************************************/
void print_stat(int found, int total) {
    // Cast both values to double, to then divide them and multiply by 100 to get a percentage.
    double result = (double(found) / double(total)) * 100;
    std::cout << "Percent of Successful Searches = " << std::fixed << std::setprecision(2) << result << "%\n";
}

/**
* @brief Linear search algorithm
*
* @param v vector to be searched
* @param x value to search for in the vector
*
* @return true if the search is successful
*         false if the search is unsuccessful
******************************************************************************/
bool linear_search(const std::vector<int> &v, int x) {
    // Linear Search
    // returns true if the search is successful
    // returns false if the search is unsuccessful
    for (int i = 0; i < int(v.size()); i++) {
        if (v[i] == x) {
            return true;
        }
    }

    return false;
}

/**
* @brief Binary search algorithm
*
* @param v vector to be searched
* @param x value to be searched for
*
* @return true if the search is successful
*         false if the search is unsuccessful
******************************************************************************/
bool binary_search(const std::vector<int> &v, int x) {
    // Just calls the STL binary_search function
    // returns true if the search is successful
    // returns false if the search is unsuccessful
    if (std::binary_search(v.begin(), v.end(), x) == true) {
        return true;
    }

    return false;
}
