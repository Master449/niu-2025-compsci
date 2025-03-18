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
const int MAX_TIME = 50;
const int IN_USE = 5;
const int HOW_OFTEN = 25;

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
    deque<Process*> entryq, readyq, inputq, outputq;
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
        process_id++;
    }

    // Done reading and processing
    input_file.close();

    //
    // Main Scheduling Loop
    //
    int timer = 0, total_process = 0, cpu_idle_time = 0;
    Process* active_process = nullptr;
    bool active_flag = false, input_flag = false, output_flag = false;

    // quick reference
    // deque has methods
         // empty
         // front - first
         // back - last
         // size

    do {
        // only loop through entryq if theres space for more
        if (total_process < IN_USE) {
            // entry queue iterator
            for (auto eqit : entryq) {
                if (timer >= eqit->arrival_time) {
                    cout << "Process " << eqit->name
                         << " (#" << eqit->id << ")" 
                         << " has moved: Entry Queue -> Ready Queue" << endl;
                    readyq.push_back(eqit);
                    entryq.pop_front();
                    total_process++;
                }
            }
        }

        // -------------- Active Process -------------------
        if (active_flag) {
            active_process->cpu_timer--;
            active_process->cpu_total++;
            
            // If the burst has ended
            if (active_process->cpu_timer == 0) {
                // Check to see if there is more to do after this
                //if (active_process->history_index == (active_process->history.size() - 1))
                // it could end CPU burst to I or O
                // it could end a CPU burst to terminate
            }
        } else if(readyq.empty() && entryq.empty() && total_process < IN_USE) {
            // no active process, idle time
            cpu_idle_time++;
        } else {
            // if ready is not empty and we have space for process
            if (!(readyq.empty()) && total_process < IN_USE) {
                // grab process, update flag, and print the change
                active_process = readyq.front();
                readyq.pop_front();
                active_flag = true;
                cout << "Process " << active_process->name
                     << " (#" << active_process->id << ")" 
                     << " has moved: Ready Queue -> Active" << endl;
            } else if (!(entryq.empty()) && total_process < IN_USE) {
                // grab process, update flag, and print the change
                active_process = entryq.front();
                entryq.pop_front();
                active_flag = true;
                cout << "Process " << active_process->name
                     << " (#" << active_process->id << ")" 
                     << " has moved: Entry Queue -> Active" << endl;
            }
        }

        // -------------- Input ------------------------
        // If (input_flag)
            // if tmp-i-burst is 0
                // update history index
                // move to ready queue
                // print if moved to queue
        // else
            // Look for one in the input queue
            // if found
                // print its movement change
                // tmp value to hold its burst

        // -------------- Output ---------------
        // If (output_flag)
            // if tmp-o-burst is 0
                // update history index
                // move to ready queue
                // print if moved to queue
        // else
            // Look for one in the output queue
            // if found
                // print its movement change
                // tmp value to hold its burst

        
        // Timekeeping 2 electric boogaloo
        if (timer % HOW_OFTEN == 0 && timer != 0) {
            
            cout << endl << "--- Summary ---" << endl << endl;
            cout << "CPU Idle: " << cpu_idle_time << endl;

            // Check if active process
            if (active_flag) {
                cout << "Active CPU ID: " << active_process->id << endl; 
            } else {
                cout << "Active CPU ID: None" << endl;
            }

            // Check if active input
            if(input_flag) {
                cout << "Active Input ID: " << inputq.front()->id << endl; 
            } else {
                cout << "Active Input ID: None" << endl;
            }

            // Check if active output
            if(output_flag) {
                cout << "Active Output ID: " << outputq.front()->id << endl; 
            } else {
                cout << "Active Output ID: None" << endl;
            }

            // Print contents of entryq
            cout << "Entry Queue Contents: ";
            for (auto eqit : entryq) {
                cout << eqit->id << " ";
            }
            cout << endl;

            // Print contents of readyq
            cout << "Ready Queue Contents: ";
            for (auto rqit : readyq) {
                cout << rqit->id << " ";
            }
            cout << endl;

            // Print contents of inputq
            cout << "Input Queue Contents: ";
            for (auto iqit : inputq) {
                cout << iqit->id << " ";
            }
            cout << endl;

            // Print contents of outputq
            cout << "Output Queue Contents: ";
            for (auto oqit : outputq) {
                cout << oqit->id << " ";
            }
            cout << endl << endl;


        }
        timer++;
    } while (timer <= MAX_TIME);

    
    return 0;
}
