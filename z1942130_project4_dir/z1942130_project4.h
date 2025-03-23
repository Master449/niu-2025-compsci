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
        end_time = 0;
        wait_time = 0;
    }

    /* terminate
    *    Prints out the summary of a processes runtime
    *    after its completed its entire task.
    *
    * Takes no args and returns nothing, prints to stdout
    *****************************************************/
    void print_terminate() {
        std::cout << "Process " << id << " has ended." << std::endl
                  << "Name              " << name << std::endl
                  << "Started at time   " << arrival_time << " and ended at time " << end_time << std::endl
                  << "Total CPU time    " << cpu_total << " in " << cpu_burst_count << " bursts" << std::endl
                  << "Total Input Time  " << i_total << " in " << i_burst_count << " bursts" << std::endl
                  << "Total Output Time " << o_total << " in " << o_burst_count << " bursts" << std::endl
                  << "Time waiting      " << wait_time << std::endl << std::endl;
    }
};

/* dump_queue
 *    takes a reference to a queue and prints all the process
 *    IDs that are inside. Mainly for the summaries.
 *
 * Args
 *   q    - reference to a queue
 *   name - name of the queue to print
 ****************************************************************/
void dump_queue(deque<Process*>& q, string name);

/* dump_all_queues
 *    Just prints out every queue sequentially
 *
 *    No args and no return
 * ****************************************/
void dump_all_queues();

/* update_work_status
 *    checks if a process is at the end of its history, and terminates if so.
 *    if its not, updates the timers for the work to be done, puts it in
 *    the correct queue for processing, and prints out the change.
 *
 * Args
 *   proc - reference to process
 * ******************************************************************************/
void update_work_status(Process* &proc);

/* check_num_process
 *    checks to see if there is room to add any processes
 *    from the entryq to the readyq
 * ***************************************************************/
void check_num_process();

/* load_process
 *    loads a new process, from either
 *      readyq -> cpu
 *      inputq -> i_active
 *      outputq -> o_active
 *
 * Args
 *   type - char to specify where we came from
 * ***************************************************************/
void load_process(char type);

/* process_active
 *    processes the CPUs bursts. If the burst reaches 0
 *    sends it to update_work_status to see if it
 *    stops or moves onto bigger and better things
 *
 *    if nothing is here it adds idle time to the total
 * ***************************************************************/
void process_active();

/* process_iactive
 *    processes the input burst. If the burst reaches 0
 *    sends it to update_work_status to see if it
 *    stops or moves onto bigger and better things
 *
 * ***************************************************************/
void process_iactive();

/* process_oactive
 *    processes the output burst. If the burst reaches 0
 *    sends it to update_work_status to see if it
 *    stops or moves onto bigger and better things
 *
 * ***************************************************************/

#endif // Z1942130_PROJECT4_H
