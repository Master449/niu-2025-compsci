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
using std::cerr;
using std::endl;
using std::stoi;

string shared_data = "All work and no play makes Jack a dull boy.";

sem_t rw_semaphore; // Semaphore for both readers and writers
sem_t ro_semaphore; // Semaphore for only readers critical section

void *writer(void *param) {
    long tid;
    tid = (long)param;
    cout<< "Hello World! It's me, thread " << tid << endl;
    pthread_exit(NULL);
}

void *reader(void *param) {
    long tid;
    tid = (long)param;
    cout<< "Hello World! It's me, thread " << tid << endl;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    int reader_count, writer_count, rt, wt;
    long total_threads;

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

    cout << "*** Reader-Writer Problem Simulation ***" << endl
         << "Number of reader threads: " << reader_count << endl
         << "Number of writer threads: " << writer_count << endl;

    // Initialization of semaphores
    if(sem_init(&rw_semaphore, 0, 1) != 0 || sem_init(&ro_semaphore, 0, 1) != 0) {
        cerr << "Semaphore init failed" << endl;
        exit(4);
    }
    
    pthread_t reader_threads[reader_count];
    pthread_t writer_threads[writer_count];
    
    // Initialize reader threads
    for(int i=0; i<reader_count; i++) {
       rt = pthread_create(&reader_threads[i], NULL, reader, (void *)i);
       if (rt){
          cerr << "Failed to init. reader thread" << endl;
          exit(5);
       }
    }

    // Initialize writer threads
    for(int i=0; i<writer_count; i++) {
       wt = pthread_create(&writer_threads[i], NULL, writer, (void *)i);
       if (wt){
          cerr << "Failed to init. writer thread" << endl;
          exit(6);
       }
    }
    // Create reader and writer threads.
    // Wait for reader threads to finish.
    // Wait for writer threads to finish.
    // Cleanup and exit.
    return 0;
}
