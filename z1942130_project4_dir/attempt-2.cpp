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
int timer = 0, total_process = 0;
char current_work;

/* dump_queue
 *    takes a reference to a queue and prints all the process
 *    IDs that are inside.
 *
 * Args
 *   q    - reference to a queue
 *   name - name of the queue to print
 ****************************************************************/
void dump_queue(deque<Process*>& q, string name) {
    cout << name << " Queue Contents: ";
    if (!q.empty()) {
        for (auto it : q) {
            cout << it->id << " ";
        }
    } else {
        cout << "(Empty)";
    }
    cout << endl;
}

/* dump_all_queues
 *    Just prints out every queue sequentally
 *
 *    No args and no return
 * ****************************************/
void dump_all_queues() {
    dump_queue(entryq, "Entry");
    dump_queue(readyq, "Ready"); 
    dump_queue(inputq, "Input");
    dump_queue(outputq, "Output");
}

/* update_work_status
 *    updates the current work flag
 *
 * Args
 *
 * Returns
 * ****************************************/
void update_work_status(Process* &proc) {
    if (proc->history_index == (int)(proc->history.size() - 1)) {
        proc->end_time = timer;
        proc->print_terminate();
        proc = nullptr;
        total_process--;
    } else {
        proc->history_index++;
        if (proc->history[proc->history_index].first == 'C') {
            current_work = 'C';
        } else if (proc->history[proc->history_index].first == 'I') {
            cout << "Process " << proc->id << " has moved from the Ready Queue to the Input Queue at time " << timer << endl << endl;
            current_work = 'I';
        } else if (proc->history[proc->history_index].first == 'O') {
            cout << "Process " << proc->id << " has moved from the Ready Queue to the Output Queue at time " << timer << endl << endl;
            current_work = 'O';
        }
        readyq.push_back(proc);
    }
}

/* d
 *    t
 *
 * Args
 *
 * Returns
 * ****************************************/
void handle_io(Process* &proc, string type) {
    auto& io_time_remaining = (type == "Input") ? proc->i_timer : proc->o_timer;
    auto& total = (type == "Input") ? proc->i_total : proc->o_total;
    auto& burst_count = (type == "Input") ? proc->i_burst_count : proc->o_burst_count;

    io_time_remaining--;
    total++;

    if (io_time_remaining == 0) {
        burst_count++;
        update_work_status(proc);
    }
}

/* d
 *    t
 *
 * Args
 *
 * Returns
 * ****************************************/
void check_num_process(Process* &proc) {
    int slots = IN_USE - total_process;
    
    if (slots > 0 && !entryq.empty()) {
        int to_add = std::min(slots, static_cast<int>(entryq.size()));
        
        // Add that many processes from entryq to readyq
        for (int i = 0; i < to_add; i++) {
            readyq.push_back(entryq.front());
            entryq.pop_front();
            total_process++;
            cout << "Process " << readyq.back()->id << " has moved from the Entry Queue into the Ready Queue at time " << timer << endl << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    // Need some sort of input, if none provided, exit
    if (argc != 2) {
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
    int cpu_idle_time = 0;
    Process* active_process = nullptr;

    cout << "Simulation of CPU Scheduling" << endl << endl;

    
    while (timer <= MAX_TIME) {
        if (timer % HOW_OFTEN == 0 && timer != 0) {

            cout << endl << "Status at time " << timer << endl;

            // Check if active process
            if (active_process) {
                cout << "Active is " << active_process->id <<  endl; 
            } else {
                cout << "Active is 0" << endl;
            }

            // Dump queues
            dump_all_queues();
        }

        if (active_process == nullptr) {
            check_num_process(active_process);
            active_process = readyq.front();
            readyq.pop_front();
            
            if (active_process->history[active_process->history_index].first == 'C') {
                active_process->cpu_timer = active_process->history[active_process->history_index].second;
                current_work = 'C';
            } else if (active_process->history[active_process->history_index].first == 'I') {
                active_process->i_timer = active_process->history[active_process->history_index].second;
                current_work = 'I';
            } else if (active_process->history[active_process->history_index].first == 'O') {
                active_process->o_timer = active_process->history[active_process->history_index].second;
                current_work = 'O';
            }
            
        } else {
            switch(current_work) {
                case 'C':
                    active_process->cpu_total++;
                    active_process->cpu_timer--;
                
                    if (active_process->cpu_timer == 0) {
                        //active_process->history_index++;
                        active_process->cpu_burst_count++;
                        //update_work_status(active_process);
                        update_work_status(active_process);
                        active_process = nullptr;
                    }
                    break;

                case 'I':
                    handle_io(active_process, "Input");
                    if (active_process->i_timer == 0) {
                        active_process = nullptr;
                    }
                    break;

                case 'O':
                    handle_io(active_process, "Output");
                    if (active_process->o_timer == 0) {
                        active_process = nullptr;
                    }
                    break;
                default:
                    continue;
            }
        }


        // Check to see if the run is done
        if (entryq.empty() && readyq.empty() && inputq.empty() && outputq.empty() && total_process == 0) {
            cout << "The run has ended." << endl
                 << "The final value of the timer was: " << timer << endl
                 << "The amount of time spent idle was: " << cpu_idle_time << endl
                 << "Number of terminated processes: " /*<< term_process_count*/ << endl
                 << "The average waiting time for all terminated processes was: " /*<< average_term_around_time */<< endl;
            dump_all_queues();
            return 0;
        }
        //if (active_process)
        //    active_process->debug_info();
        timer++;
    }

    return 0;
}
