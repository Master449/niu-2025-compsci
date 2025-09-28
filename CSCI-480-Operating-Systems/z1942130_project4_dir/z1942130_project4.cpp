/********************************************************************
CSCI 490 - Assignment 4 - Semester Spring 2025

Programmer: David Flowers II
   Section: 1
        TA: Keerthi Kalyan Botu
  Date Due: 03/25/2025

   Purpose: To create a program that simulates CPU scheduling in
            an Operating System. FCFS is required, but RR can
            be done for extra credit.

*********************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <fstream>
#include <utility>
#include "z1942130_project4.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::deque;
using std::pair;
using std::stoi;

// Constants
const int MAX_TIME = 500;
const int IN_USE = 5;
const int HOW_OFTEN = 25;

// Globals
deque<Process*> entryq, readyq, inputq, outputq;
Process* active = nullptr;
Process* i_active = nullptr;
Process* o_active = nullptr;
bool idle_print_out = true;
int timer = 0,
    total_process = 0,
    term_process_count = 0,
    average_wait_time_total = 0,
    cpu_idle_time = 0,
    old_active_id = 0;

/* dump_queue
 *    Takes a reference to a queue and prints all the process
 *    IDs that are inside. Mainly for the summaries.
 *
 * Args
 *   q    - reference to a queue
 *   name - name of the queue to print
 ****************************************************************/
void dump_queue(deque<Process*>& q, string name) {
    cout << name << " Queue Contents: ";

    // If were not empty, print contens
    if (!q.empty()) {
        for (auto it : q) {
            cout << it->id << " ";
        }
    // Otherwise, print empty
    } else {
        cout << "(Empty)";
    }
    cout << endl;
}

/* dump_all_queues
 *    Just prints out every queue sequentially
 *
 *    No args and no return
 * ****************************************/
void dump_all_queues() {
    dump_queue(entryq, "Entry");
    dump_queue(readyq, "Ready"); 
    dump_queue(inputq, "Input");
    dump_queue(outputq, "Output");
    cout << endl;
}

/* update_work_status
 *    Checks if a process is at the end of its history, and terminates if so.
 *    If its not, updates the timers for the work to be done, puts it in
 *    The correct queue for processing, and prints out the change.
 *
 * Args
 *   proc - reference to process
 * ******************************************************************************/
void update_work_status(Process* &proc) {
    // Check if we are at the end of the processes history
    if (proc->history_index == (int)(proc->history.size() - 1)) {
        // If so, update the end time and processor counts, print out 
        // start wait and end times, and print the terminate summary
        // then make the process nullptr again, so another can be loaded
        proc->end_time = timer + 1;
        proc->wait_time = (proc->end_time - proc->start_time) - proc->cpu_total - proc->i_total - proc->o_total;
        average_wait_time_total += proc->wait_time;
        proc->print_terminate();
        proc = nullptr;

        total_process--;
        term_process_count++;
    } else {
        // If we are not the end of the history, increment the index
        proc->history_index++;

        // get processes new task
        char new_task = proc->history[proc->history_index].first;

        /* ----------- General Process ---------
            update proc's I/O/CPU timer to new workload
            push_back proc to I/O/Ready Queue
            Print change if applicable
            remove proc                              */

        // Input task
        if (new_task == 'I') {
            proc->i_timer = proc->history[proc->history_index].second;
            inputq.push_back(proc);
            proc = nullptr;
        // Output task
        } else if (new_task == 'O') {
            proc->o_timer = proc->history[proc->history_index].second;
            outputq.push_back(proc);
            proc = nullptr;
        // CPU task
        } else if (new_task == 'C') {
            proc->cpu_timer = proc->history[proc->history_index].second;
            readyq.push_back(proc);
            proc = nullptr;
        }
    }
}

/* check_num_process
 *    Checks to see if there is room to add any processes
 *    From the entryq to the readyq
 * ***************************************************************/
void check_num_process() {
    // Calculate total processes, and open slots
    total_process = readyq.size() + inputq.size() + outputq.size() + (active ? 1 : 0) + (i_active ? 1 : 0) + (o_active ? 1: 0);
    int slots = IN_USE - total_process;
    
    // If no slots, or entry is empty, don't do anything
    if (slots > 0 && !entryq.empty()) {
        // Add eligible processes to ready queue
        int added = 0;
        while (added < slots && !entryq.empty()) {
            // Check if process has arrived
            if (entryq.front()->arrival_time <= timer) {
                // If it arrived, update start time
                // push it to ready queue
                entryq.front()->start_time = timer;
                readyq.push_back(entryq.front());
                entryq.pop_front();
                   // This is only here because of tiny.txt
                   total_process++;
                   // No im serious, remove it and try tiny.txt again
                added++;
                cout << "Process " << readyq.back()->id << " has moved from the Entry Queue into the Ready Queue at time " << timer << endl << endl;
            } else {
                // If the process hasnt arrived yet, dont do anything
                break;
            }
        }
    }
}

/* process_active
 *    Processes the CPUs bursts. If the burst reaches 0
 *    Sends it to update_work_status to see if it
 *    Stops or moves onto bigger and better things
 *
 *    If nothing is here it adds idle time to the total
 * ***************************************************************/
void process_active() {
    // If no process, see if we can load one
    if (active == nullptr) {
        if (readyq.empty())
            check_num_process();
        // Double check queue is not empty
        if (!readyq.empty()) {
            active = readyq.front();
            readyq.pop_front();
            active->cpu_timer = active->history[active->history_index].second;
        } else if (!entryq.empty() && (total_process < IN_USE)) {
            active = entryq.front();
            entryq.pop_front();
            active->cpu_timer = active->history[active->history_index].second;
            check_num_process();
        }
    }
    
    // Double check we have a process
    if (active != nullptr) {
        // If we've done some work, idle flag gets reset
        idle_print_out = true;

        // Increment cpu total, and decrement work timer
        active->cpu_total++;
        active->cpu_timer--;
        
        // If we are at the end of this burst
        // add it to total, and see where next
        if (active->cpu_timer == 0) {
            active->cpu_burst_count++;
            old_active_id = active->id;
            update_work_status(active);
        }
    } else {
        // If no process, add idle time
        cpu_idle_time++;

        // Flag is so we only print once when we start idling
        if (idle_print_out) {
            cout << "At time " << timer << " Active is 0, so we idle for a while" << endl << endl;
            idle_print_out = false;
        }
    }
}

/* process_iactive
 *    Processes the input burst. If the burst reaches 0
 *    Sends it to update_work_status to see if it
 *    Stops or moves onto bigger and better things
 *
 * ***************************************************************/
void process_iactive() {
    // If no process, see if we can load one
    if (i_active == nullptr) {

        if (!inputq.empty()) {
            // load the process, pop the queue, and update the work to do
            i_active = inputq.front();
            inputq.pop_front();
            i_active->i_timer = i_active->history[i_active->history_index].second;
        } else {
            return;
        }
    }
    
    // Double check we have a process
    if (i_active != nullptr) {
        // Double check we arent double dipping work
        // during 1 tick
        if (old_active_id == i_active->id)
            return;

        // Increment input total, and decrement work timer
        i_active->i_total++;
        i_active->i_timer--;

        // If we are at the end of this burst
        // add it to total, and see where next
        if (i_active->i_timer == 0) {
            i_active->i_burst_count++;
            update_work_status(i_active);
        }
    }
}

/* process_oactive
 *    Processes the output burst. If the burst reaches 0
 *    Sends it to update_work_status to see if it
 *    Stops or moves onto bigger and better things
 *
 * ***************************************************************/
void process_oactive() {
    // If no process, see if we can load one
    if (o_active == nullptr) {
        //load_process('O');
        if (!outputq.empty()) {
            // load the process, pop the queue, and update the work to do
            o_active = outputq.front();
            outputq.pop_front();
            o_active->o_timer = o_active->history[o_active->history_index].second;
        } else {
            return;
        }
    }

    // Double check we have a process
    if (o_active != nullptr) {
        // Double check we arent double dipping
        // work during 1 cycle
        if (old_active_id == o_active->id)
            return;

        // Increment output total, and decrement work timer
        o_active->o_total++;
        o_active->o_timer--;

        // If we are at the end of this burst
        // add it to total, and see where next
        if (o_active->o_timer == 0) {
            o_active->o_burst_count++;
            update_work_status(o_active);
        }
    }
}

int main(int argc, char *argv[]) {
    // Need some sort of input, if none provided, exit
    if (argc < 1) {
        cout << "Need an input file" << endl;
        return 1;
    }

    // Create our process state queues
    string process_name_line, process_stat_line;
    string entire_file;
    string input_path = argv[1];
    int process_id = 100;
    std::ifstream input_file(input_path);
    vector<string> temp_process;

    // Read in the input file
    while (getline(input_file, process_name_line)) {
        // Check for input delimiter
        if (process_name_line.find("STOPHERE") != string::npos) 
            break;

        // Spin up some temporary variables, and a new Process class
        string temp, type, burst;
        Process* tmp_process = new Process();
        stringstream fl(process_name_line);
        vector<pair<char, int>> temp_history;

        // Process the name and arrival time, assigning it
        // to the newly created class
        fl >> temp;
        tmp_process->name = temp;
        fl >> temp;
        
        process_id++;
        
        tmp_process->arrival_time = stoi(temp);
        tmp_process->id = process_id;

        // Grab the next line, which will be the history of the process
        getline(input_file, process_stat_line);
        stringstream sl(process_stat_line);

        // Get two at a time from the string stream
        while (sl >> type >> burst) {
            // Check if we are at the end
            if (type == "N" && burst == "0") 
                break;
            // Push them onto the history
            tmp_process->history.push_back(std::make_pair(type[0], stoi(burst)));
        }
        
        // Put process onto the entry queue, and increment the process id
        entryq.push_back(tmp_process);
    }

    // Done reading and processing
    input_file.close();

    //
    // Main Scheduling Loop
    //
    
    cout << "Simulation of CPU Scheduling" << endl << endl;

    // Load readyq for the first time
    check_num_process();

    while (timer <= MAX_TIME) {

        // If its status time print it
        if (timer % HOW_OFTEN == 0) {

            cout << "Status at time " << timer << endl;

            // Check and print if active process
            if (active) cout << "Active is " << active->id <<  endl; 
            else cout << "Active is 0" << endl;

            // Check and print if iactive process
            if (i_active) cout << "IActive is " << i_active->id <<  endl; 
            else cout << "IActive is 0" << endl;
            
            // Check and print oactive process
            if (o_active) cout << "OActive is " << o_active->id <<  endl; 
            else cout << "OActive is 0" << endl;

            // Dump queues
            dump_all_queues();
        }

        // Process the different queues
        process_active();
        process_iactive();
        process_oactive();

        // If we are all done, print the summary of all processes
        if (entryq.empty() && readyq.empty() && inputq.empty() && outputq.empty() && total_process == 0) {
            cout << "The run has ended." << endl
                 << "The final value of the timer was: " << timer << endl
                 << "The amount of time spent idle was: " << cpu_idle_time << endl
                 << "Number of terminated processes: " << term_process_count << endl
                 << "The average waiting time for all terminated processes was: " << average_wait_time_total / term_process_count << endl;
            dump_all_queues();
            exit(0);
        }
        // Update double-dip safety flag
        old_active_id = 0;

        // Increment timer
        timer++;
    }
    return 0;
}
