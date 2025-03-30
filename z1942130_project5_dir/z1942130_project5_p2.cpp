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
#include <unistd.h>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::stoi;

string shared_data = "All work and no play makes Jack a dull boy.";

sem_t semaphore1, semaphore2;

int read_count;

void *writer(void *param) {
    // Local variables
    long tid;
    tid = (long)param;

    // loop until string is empty
    while(!shared_data.empty()) {
        // enter critical section
        sem_wait(&semaphore1);

        if (!shared_data.empty()) {
            shared_data.pop_back();
            printf("writer %ld is writing ...\n", tid);
            fflush(stdout);
        }

        // exit critical section
        sem_post(&semaphore2);

        // sleep
        sleep(1);
    }
    printf("writer %ld is exiting ...\n", tid);
    fflush(stdout);
    
    pthread_exit(NULL);
}

void *reader(void *param) {
    // Local variables
    long tid;
    tid = (long)param;

    // loop until string is empty
    while(!shared_data.empty()) {
        // enter readers only critical section
        sem_wait(&semaphore2);

        if (!shared_data.empty()) {
            printf("reader %ld is reading ... content : %s\n", tid, shared_data.c_str());
            fflush(stdout);
        }

        // exit critical section
        sem_post(&semaphore1);
        
        sleep(1);
    }
    printf("reader %ld is exiting ...\n", tid);
    fflush(stdout);
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    int reader_count, writer_count, rc;

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

    if (reader_count <= 0 || writer_count <= 0) {
        std::cerr << "Args must be positive integers." << endl;
        exit(3);
    }

    cout << "*** Reader-Writer Problem Simulation ***" << endl
         << "Number of reader threads: " << reader_count << endl
         << "Number of writer threads: " << writer_count << endl;

    // Initialization of semaphores
    if(sem_init(&semaphore1, 0, 1) != 0) { 
        cerr << "Semaphore init failed" << endl;
        exit(4);
    }
    
    if (sem_init(&semaphore2, 0, 1) != 0) {
        cerr << "Semaphore init failed" << endl;
        exit(4);
    }
    
    pthread_t reader_threads[reader_count];
    pthread_t writer_threads[writer_count];
    
    // Initialize reader threads
    for(long i = 0; i < reader_count; i++) {
        rc = pthread_create(&reader_threads[i], NULL, reader, (void *)i);
        if (rc) {
           cerr << "Failed to init. reader thread" << endl;
           exit(5);
        }
    }

    // Initialize writer threads
    for(long j = 0; j < writer_count; j++) {
        rc = pthread_create(&writer_threads[j], NULL, writer, (void *)j);
        if (rc) {
            cerr << "Failed to init. writer thread" << endl;
            exit(6);
        }
    }

    // Wait for reader threads to finish.
    for (long i = 0; i < reader_count; i++) {
        rc = pthread_join(reader_threads[i], NULL);
        if (rc) {
            cerr << "Failed to init. writer thread" << endl;
            exit(6);
        }
    }

    // Wait for writer threads to finish.
    for (long j = 0; j < writer_count; j++) {
        rc = pthread_join(writer_threads[j], NULL);
        if (rc) {
            cerr << "Failed to init. writer thread" << endl;
            exit(6);
        }
    }

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    cout << "All threads are done." << endl;
    cout << "Resources cleaned up." << endl;

    // Cleanup and exit.
    return 0;
}
