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
// The queues are used in a ton of functions
// the further I got, the more it became apparent
// that they should be global, so I don't need to 
// pass all of them into functions all the time
deque<Process*> entryq, readyq, inputq, outputq;

/* print_queue_change
 *    when a process switches queues, print
 *    Process <id> moved from <from> Queue to the <to> Queue at time <time>
 *
 * Args:
 *   id   - process id that moved
 *   from - name of origin queue
 *   to   - name of destination queue
 *   time - time this occured
 ****************************************************************/
void print_queue_change(int id, string from, string to, int time) {
    cout << "Process " << id << " has moved from the " << from << " Queue to the " << to << " Queue at time " << time << endl << endl;
}

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

void dump_all_queues() {
    dump_queue(entryq, "Entry");
    dump_queue(readyq, "Ready"); 
    dump_queue(inputq, "Input");
    dump_queue(outputq, "Output");
}

void handle_io(Process* &io, string type, int timestamp) {
    auto& timer = (type == "Input") ? io->io_timer.first : io->io_timer.second;
    auto& total = (type == "Input") ? io->io_total.first : io->io_total.second;
    auto& burst_count = (type == "Input") ? io->io_burst_count.first : io->io_burst_count.second;
    auto& queue = (type == "Input") ? inputq : outputq;

    if (io) {
        timer--;
        total++;

        if (timer == 0) {
            // update history index
            io->history_index++;
            burst_count++;

            // move to ready queue
            readyq.push_back(io);

            // print if moved to queue
            print_queue_change(io->id, type, "Ready", timestamp);

            // No more active io process
            io = nullptr;
        }

    } else {
        // Look in input queue
        if (!(queue.empty())) {
            io = queue.front();
            queue.pop_front();
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
    int timer = 0, total_process = 0, cpu_idle_time = 0;
    Process* active_process = nullptr;
    Process* input_process = nullptr;
    Process* output_process = nullptr;

    cout << "Simulation of CPU Scheduling" << endl << endl;

    do {
        // -------------- Active Process -------------------
        if (active_process) {
            // If the burst has ended, we need to figure where it goes next
            if (active_process->cpu_timer == 0) {
                // It could terminate
                if (active_process->history_index == (int)(active_process->history.size() - 1)) {
                    active_process->terminate();
                    total_process--;
                } else {
                    // If its not done, figure out which queue is next up
                    active_process->history_index++;
                    char next_queue = active_process->history[active_process->history_index].first;

                    if (next_queue == 'I') {
                        active_process->io_timer.first = active_process->history[active_process->history_index].second;
                        inputq.push_back(active_process);
                        print_queue_change(active_process->id, "Active", "Input", timer);
                    } else if (next_queue == 'O') {
                        active_process->io_timer.second = active_process->history[active_process->history_index].second;
                        outputq.push_back(active_process);
                        print_queue_change(active_process->id, "Active", "Output", timer);
                    } 
                }
                active_process = nullptr;
            } else {
                active_process->cpu_timer--;
                active_process->cpu_total++;
            }
            
        } else if(readyq.empty() && entryq.empty() && total_process < IN_USE) {
            // no active process, idle time
            cpu_idle_time++;
        } else {
            // if ready is not empty and we have space for process
            if ((!(readyq.empty())) && total_process < IN_USE) {
                // grab process, update queues, and change set timer from history
                active_process = readyq.front();
                readyq.pop_front();
                active_process->cpu_timer = active_process->history[active_process->history_index].second;
            }
        }

        // -------------- Handle I/O ------------------------
        handle_io(input_process, "Input", timer);
        handle_io(output_process, "Output", timer);

        
        // only loop through entryq if theres space for more
        if (total_process < IN_USE) {
            // entry queue iterator
            for (auto eqit : entryq) {
                if (timer >= eqit->arrival_time) {
                    readyq.push_back(eqit);
                    entryq.pop_front();
                    print_queue_change(eqit->id, "Entry", "Ready", timer);
                    total_process++;
                }
            }
        }


        if (timer % HOW_OFTEN == 0) {

            cout << endl << "Status at time " << timer << endl;

            // Check if active process
            if (active_process) {
                cout << " Active is " << active_process->id <<  endl; 
            } else {
                cout << " Active is 0" << endl;
            }

            // Check if active input
            if(input_process) {
                cout << "IActive is " << inputq.front()->id << endl; 
            } else {
                cout << "IActive is 0" << endl;
            }

            // Check if active output
            if(output_process) {
                cout << "OActive is " << outputq.front()->id << endl; 
            } else {
                cout << "OActive is 0" << endl;
            }

            // Dump queues
            dump_queue(entryq, "Entry");
            dump_queue(readyq, "Ready");
            dump_queue(inputq, "Input");
            dump_queue(outputq, "Output");
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

        timer++;
    } while (timer <= MAX_TIME);

    return 0;
}
