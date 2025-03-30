/********************************************************************
CSCI 490 - Assignment 5  - Semester Spring 2025

Programmer: David Flowers II
   Section: 1
        TA: Keerthi Kalyan Botu
  Date Due: 04/12/2025

   Purpose: This program simulates the reader-writer problem using
            the pthreads library and semaphores

*********************************************************************/
#include <pthread.h>
#include <iostream>
#include <string>
#include <semaphore.h>

using std::string;
using std::cout;
using std::endl;
using std::stoi;

void *writer(void *param) {
    return;
}

void *reader(void *param) {
    return;
}

int main(int argc, char *argv[]) {
    
    int reader_count, writer_count;

    // Check command line args
    if (argc != 3) {
        std::cerr << "Invalid number of arguments passed in." << endl;
        exit(1);
    }

    // Verify they are what we expect
    try {
        reader_count = stoi(argv[1]);
        writer_count = stoi(argv[2]);
    } catch(const std::invalid_argument &e) {
        std::cerr << "Invalid Argument " <<  e.what() << endl;;
        exit(2);
    }

    if (reader_count <= 0 || writer_count <= 0) {
        std::cerr << "Args must be positive integers." << endl;;
        exit(3);
    }

    // Initialization of semaphores.
    // Create reader and writer threads.
    // Wait for reader threads to finish.
    // Wait for writer threads to finish.
    // Cleanup and exit.
    return 0;
}
