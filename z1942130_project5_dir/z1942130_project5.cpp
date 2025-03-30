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

sem_t rw_semaphore; // Semaphore for both readers and writers
sem_t ro_semaphore; // Semaphore for only readers critical section

int read_count;

void *writer(void *param) {
    // Local variables
    long tid;
    tid = (long)param;

    // loop until string is empty
    while(!shared_data.empty()) {
        // enter critical section
        sem_wait(&rw_semaphore);


        if (!shared_data.empty()) {
            printf("writer %ld is writing ...\n", tid);
            fflush(stdout);
            shared_data.pop_back();
        }

        // exit critical section
        sem_post(&rw_semaphore);

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
        sem_wait(&ro_semaphore);

        // increment reader total
        read_count++;

        // printout the new total
        printf("read_count increments to: %d.\n", read_count);
        fflush(stdout);
        
        // attempt to lockout writers
        if (read_count == 1) {
            sem_wait(&rw_semaphore);
        }
        
        // exit reader only critical section
        sem_post(&ro_semaphore);

        printf("reader %ld is reading ... content : %s\n", tid, shared_data.c_str());
        fflush(stdout);

        // enter reader only critical section
        sem_wait(&ro_semaphore);

        // decrement reader total
        read_count--;

        printf("read_count decrements to: %d.\n", read_count);
        fflush(stdout);
        
        // last reader unblocks the writers
        if (read_count == 0) {
            sem_post(&rw_semaphore);
        }

        // exit critical section
        sem_post(&ro_semaphore);
        
        sleep(1);
    }
    printf("reader %ld is exiting ...\n", tid);
    fflush(stdout);
    
    pthread_exit(NULL);
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
    if (sem_init(&rw_semaphore, 0, 1) != 0) {
        cerr << "Read/Write semaphore init failed" << endl;
        exit(4);
    }
    
    if (sem_init(&ro_semaphore, 0, 1) != 0) {
        cerr << "Reader Only semaphore init failed" << endl;
        exit(4);
    }

    pthread_t reader_threads[reader_count];
    pthread_t writer_threads[writer_count];
    
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

    sem_destroy(&rw_semaphore);
    sem_destroy(&ro_semaphore);

    cout << "All threads are done." << endl;
    cout << "Resources cleaned up." << endl;

    // Cleanup and exit.
    return 0;
}
