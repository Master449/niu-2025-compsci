/********************************************************************
CSCI 490 - Assignment 4 - Semester Spring 2025

Programmer: David Flowers II
   Section: 1
        TA: Keerthi Kalyan Botu
  Date Due: 03/25/2025

   Purpose: Header file for the program that simulates CPU 
            scheduling in an Operating System.

*********************************************************************/
#ifndef Z1942130_PROJECT4_H
#define Z1942130_PROJECT4_H

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <utility>

using std::string;
using std::deque;
using std::pair;
using std::vector;

/* process class
 *    holds all the information related to a process
 *    including name, id, history, all cpu burst info
 *    and all I/O burst information.
 *
 *    Note: I/O pairs are <in, out> just like
 *          saying the words Input/Output
 *    Note: Originally started out as a struct, so
 *          if everything is still public, I did not
 *          get a chance to refactor it.
 *************************************************/
class Process {
    public:
        string name;
        int id;
        int arrival_time;
        vector<pair<char, int>> history;
        int history_index;
        int cpu_timer;
        int cpu_total;
        int cpu_burst_count;
        int i_timer;
        int i_total;
        int o_timer;
        int o_total;
        int i_burst_count;
        int o_burst_count;
        int idle_time;
        int end_time;
        int wait_time;

    // Constructor, just so we don't get garbage values we don't want
    Process() {
        name = "";
        id = 0;
        arrival_time = 0;
        history_index = 0;
        cpu_timer = 0;
        cpu_total = 0;
        cpu_burst_count = 0;
        i_timer = 0;
        i_total = 0;
        i_burst_count = 0;
        o_timer = 0;
        o_total = 0;
        o_burst_count = 0;
        idle_time = 0;
        end_time = 0;
        wait_time = 0;
    }

    /* debug_info
    *    For debugging purposes. When called it will
    *    spit out all information about the process
    *    that called this function.
    *
    * Takes no args and returns nothing, prints to stdout
    *****************************************************/
    void debug_info() {
        std::cout << string(30, '-') << std::endl
                  << "Name:        " << name << std::endl
                  << "ID:          " << id << std::endl
                  << "Arrival:     " << arrival_time << std::endl
                  << "History:     ";

        for (const auto& it : history) {
            std::cout << "(" << it.first << "," << it.second << ")  ";
        }

        std::cout << std::endl;

        std::cout << "Hist. Index: " << history_index << std::endl
                  << "CPU Timer:   " << cpu_timer << std::endl
                  << "CPU Total:   " << cpu_total << std::endl
                  << "CPU Bursts:  " << cpu_burst_count << std::endl
                  << "I/O Timer:   " << "(" << i_timer << "," << o_timer << ")" << std::endl
                  << "I/O Total:   " << "(" << i_total << "," << o_total << ")" << std::endl
                  << "I/O Bursts:  " << "(" << i_burst_count << "," << o_burst_count << ")" << std::endl;
    }
    
    /* terminate
    *    Prints out the summary of a processes runtime
    *    after its completed its entire task.
    *
    * Takes no args and returns nothing, prints to stdout
    *****************************************************/
    int print_terminate() {
        std::cout << "Process " << id << " has ended." << std::endl
                  << "Name              " << name << std::endl
                  << "Started at time   " << arrival_time << " and ended at time " << end_time << std::endl
                  << "Total CPU time    " << cpu_total << " in " << cpu_burst_count << " bursts" << std::endl
                  << "Total Input Time  " << i_total << " in " << i_burst_count << " bursts" << std::endl
                  << "Total Output Time " << o_total << " in " << o_burst_count << " bursts" << std::endl
                  << "Time waiting      " << idle_time << std::endl;
        return wait_time;
    }
};

/* dump_queue
 *    takes a reference to a queue and prints all the process
 *    IDs that are inside.
 ****************************************************************/
void dump_queue(deque<Process*>& q, string name);

#endif // Z1942130_PROJECT4_H
