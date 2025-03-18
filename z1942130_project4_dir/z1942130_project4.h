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
        pair<int, int> io_timer;
        pair<int, int> io_total;
        pair<int, int> io_burst_count;
        int idle_time;

    // Constructor, just so we don't get garbage values we don't want
    Process() {
        name = "";
        id = 0;
        arrival_time = 0;
        history_index = 0;
        cpu_timer = 0;
        cpu_total = 0;
        cpu_burst_count = 0;
        idle_time = 0;
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
                  << "I/O Timer:   " << "(" << io_timer.first << "," << io_timer.second << ")" << std::endl
                  << "I/O Total:   " << "(" << io_total.first << "," << io_total.second << ")" << std::endl
                  << "I/O Bursts:  " << "(" << io_burst_count.first << "," << io_burst_count.second << ")" << std::endl;
    }
    
    /* terminate
    *    Prints out the summary of a processes runtime
    *    after its completed its entire task.
    *
    * Takes no args and returns nothing, prints to stdout
    *****************************************************/
    void terminate() {
        std::cout << "Process " << name << " (#" << id << ") has terminated, goodbye" << std::endl
                  << "CPU Bursts:  " << cpu_burst_count << std::endl
                  << "I/O Bursts:  " << "(" << io_burst_count.first << "ms input, " << io_burst_count.second << "ms output)" << std::endl
                  << "CPU Total:   " << cpu_total << std::endl
                  << "I/O Total:   " << "(" << io_total.first << "ms input, " << io_total.second << "ms output)" << std::endl
                  << "Total Idle:  " << idle_time << "ms" << std::endl;
    }
};

#endif // Z1942130_PROJECT4_H
