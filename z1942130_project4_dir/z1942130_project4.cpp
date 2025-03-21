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
int cpu_idle_time = 0;
bool work_done = false;
Process* active = nullptr;
Process* i_active = nullptr;
Process* o_active = nullptr;

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
        if (proc->history[proc->history_index].first == 'I') {
            i_active = proc;
            proc = nullptr;
            i_active->i_timer = i_active->history[i_active->history_index].second;
        } else if (proc->history[proc->history_index].first == 'O') {
            o_active = proc;
            proc = nullptr;
            o_active->o_timer = o_active->history[o_active->history_index].second;
        } else if (proc->history[proc->history_index].first == 'C') {
            active = proc;
            proc = nullptr;
            active->cpu_timer = active->history[active->history_index].second;
        }
    }
}

/* d
 *    t
 *
 * Args
 *
 * Returns
 * ****************************************/
void check_num_process() {
    total_process = readyq.size() + inputq.size() + outputq.size() + (active ? 1 : 0) + (i_active ? 1 : 0) + (o_active ? 1: 0);
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

void load_process(char type) {
    if (!(i_active) && !(o_active) && type == 'C') {
        active = readyq.front();
        readyq.pop_front();
        active->cpu_timer = active->history[active->history_index].second;
        return;
    }
    if (!(active) && !(o_active) && type == 'I') {
        i_active = readyq.front();
        readyq.pop_front();
        i_active->i_timer = i_active->history[i_active->history_index].second;
        return;
    }
    if (!active && !i_active && type == 'O') {
        o_active = readyq.front();
        readyq.pop_front();
        o_active->o_timer = o_active->history[o_active->history_index].second;
        return;
    } 
    //cout << "load_process doesnt work" << endl;
    //exit(0);
}

void processActive() {
    if (active == nullptr) {
        load_process('C');
    }
        
    if (active != nullptr) {
        active->cpu_total++;
        active->cpu_timer--;
                
        if (active->cpu_timer == 0) {
            //active_process->history_index++;
            active->cpu_burst_count++;
            //update_work_status(active_process);
            update_work_status(active);
            //active = nullptr;
        }
        //work_done = true;
        //run it (increase the counters).
        //check if it is the end of CPU burst; if yes, increase counter, decide where to put the process next.
    } else if (active == nullptr) {
        cpu_idle_time++;
    }
}

void processIActive() {
    //if (i_active == nullptr) {
    //    load_process('I');
    //}
    
    if (i_active != nullptr) {
        i_active->i_total++;
        i_active->i_timer--;
                
        if (i_active->i_timer == 0) {
            //active_process->history_index++;
            i_active->i_burst_count++;
            //update_work_status(active_process);
                update_work_status(i_active);
            //active = nullptr;
        }
        //work_done = true;
    } else if (i_active == nullptr) {
        cpu_idle_time++;
        // TODO: THIS MIGHT NEED TO BE REMOVED FOR BOTH I/O
    }
}

void processOActive() {
    //if (o_active == nullptr) {
    //    load_process('O');
    //} // try to load the active process. (active may still be NULL after this.)
        
    if (o_active != nullptr) {
        o_active->o_total++;
        o_active->o_timer--;
                
        if (o_active->o_timer == 0) {
            //active_process->history_index++;
            o_active->o_burst_count++;
            //update_work_status(active_process);
                update_work_status(o_active);
            //active = nullptr;
        }
        //work_done = true;
    } else if (o_active == nullptr) {
        cpu_idle_time++;
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

    cout << "Simulation of CPU Scheduling" << endl << endl;
    
    while (timer <= MAX_TIME) {
        //work_done = false;
        if (timer % HOW_OFTEN == 0 && timer != 0) {

            cout << endl << "Status at time " << timer << endl;

            // Check if active process
            if (active)
                cout << "Active is " << active->id <<  endl; 
            else 
                cout << "Active is 0" << endl;

            // Check if iactive process
            if (i_active)
                cout << "IActive is " << i_active->id <<  endl; 
            else 
                cout << "IActive is 0" << endl;
            
            // Check if oactive process
            if (o_active)
                cout << "OActive is " << o_active->id <<  endl; 
            else 
                cout << "OActive is 0" << endl;

            // Dump queues
            dump_all_queues();
        }

        //if (timer % 5 == 0) {
            //if (active)
                //active->debug_info();
            //if (i_active)
                //i_active->debug_info();
            //if (o_active)
                //o_active->debug_info();
        //}
        
        //if (active == nullptr && i_active && nullptr && o_active == nullptr) {
            if (total_process < IN_USE)
                check_num_process();
        //}
        //if (!work_done)
            processIActive();
        //if (!work_done)
            processOActive();
        //if (!work_done)
            processActive();
        
        if (entryq.empty() && readyq.empty() && inputq.empty() && outputq.empty() && total_process == 0) {
            cout << "The run has ended." << endl
                 << "The final value of the timer was: " << timer << endl
                 << "The amount of time spent idle was: " << cpu_idle_time << endl
                 << "Number of terminated processes: " /*<< term_process_count*/ << endl
                 << "The average waiting time for all terminated processes was: " /*<< average_term_around_time */<< endl;
            dump_all_queues();
            exit(0);
        }

        // Check to see if the run is done
        timer++;

    }

    return 0;
}
