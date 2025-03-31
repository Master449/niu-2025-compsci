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
#include <vector>
#include <string>
#include <semaphore.h>
#include <unistd.h>
#include <numeric>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::stoi;
using std::vector;

string shared_data = "All work and no play makes Jack a dull boy.";

int read_counti, reader_count, writer_count;

sem_t rw_sem; // Semaphore for both readers and writers
sem_t cs_sem; // Semaphore for only readers critical section


void *writer(void *param) {
    // Local variables
    long tid = (long)param;

    // loop until string is empty
    while(!shared_data.empty()) {
        // enter critical section
        sem_wait(&rw_sem);

        // double check its not empty
        if (!shared_data.empty()) {
            printf("writer %ld is writing ...\n", tid);
            fflush(stdout);
            shared_data.pop_back();
        }

        // exit critical section
        sem_post(&cs_sem);

        // sleep
        sleep(1);
    }

    // When done, let stdout know and exit
    printf("writer %ld is exiting ...\n", tid);
    fflush(stdout);

    pthread_exit(NULL);
}

void *reader(void *param) {
    // Local variables
    long tid = (long)param;

    // loop until string is empty
    while(!shared_data.empty()) {
        // enter readers only critical section
        sem_wait(&cs_sem);

        // print out the read
        printf("reader %ld is reading ... content : %s\n", tid, shared_data.c_str());
        fflush(stdout);

        // exit critical section
        sem_post(&rw_sem);
        
        sleep(1);
    }
    
    int remaining = (writer_count - reader_count);

    // When done, let stdout know and exit
    printf("reader %ld is exiting ...\n", tid);

    // print out the remainders
    printf("There are still %i writers waiting on the semaphore...\n", remaining);
    fflush(stdout);

    // signal to let them exit
    for (int i = 0; i < remaining; i++) {
        sem_post(&rw_sem);
    }    

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {


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
        std::cerr << "Invalid Argument " <<  e.what() << endl;
        exit(2);
    }
    
    // verify that the input is positive
    if (reader_count <= 0 || writer_count <= 0) {
        std::cerr << "Args must be positive integers." << endl;
        exit(3);
    }
    
    // create pthread_t arrays holding the readers and writers
    pthread_t reader_threads[reader_count];
    pthread_t writer_threads[writer_count];

    cout << "*** Reader-Writer Problem Simulation ***" << endl
         << "Number of reader threads: " << reader_count << endl
         << "Number of writer threads: " << writer_count << endl;

    // Initialization of semaphores
    if (sem_init(&rw_sem, 0, 1) != 0) {
        cerr << "Read/Write semaphore init failed" << endl;
        exit(4);
    }

    if (sem_init(&cs_sem, 0, 1) != 0) {
        cerr << "Reader Only semaphore init failed" << endl;
        exit(4);
    }

    // Initialize reader threads
    for(long i = 0; i < reader_count; i++) {
       if (pthread_create(&reader_threads[i], NULL, reader, (void *)i) != 0) {
          cerr << "Failed to init. reader thread" << endl;
          exit(5);
       }
    }

    // Initialize writer threads
    for(long j = 0; j < writer_count; j++) {
       if (pthread_create(&writer_threads[j], NULL, writer, (void *)j) != 0) {
          cerr << "Failed to init. writer thread" << endl;
          exit(6);
       }
    }

    // Wait for reader threads to finish.
    for (long i = 0; i < reader_count; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Wait for writer threads to finish.
    for (long j = 0; j < writer_count; j++) {
        pthread_join(writer_threads[j], NULL);
    }
    
    // print out done message
    cout << "All threads are done." << endl;

    // destroy semaphores
    sem_destroy(&rw_sem);
    sem_destroy(&cs_sem);

    // indicate that all resources are cleaned up
    cout << "Resources cleaned up." << endl;

    return 0;
}
