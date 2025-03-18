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
    int timer, total_process, cpu_idle_time;
    Process* active_process;
    bool active_flag, input_flag, output_flag;

    timer = 0;
    total_process = 0;
    cpu_idle_time = 0;

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
                if (timer > eqit->arrival_time) {
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
                if (active_process->history_index == (active_process->history.size() - 1))
                // it could end CPU burst to I or O
                // it could end a CPU burst to terminate
            }
        } else if(readyq.empty() && entryq.empty() && total_process < IN_USE) {
            // no active process
            //cpu_idle_time++;
        } else {
            // obtain from readyq
            // if readyq empty && total processes < IN_USE
                // if entryq not empty
                    // obtain a process from the entryq
                    // store tmp burst
                    // update active-flag
                    // print if moved to queue
        // }

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
        // if timer % HOW_OFTEN == 0
            // print ID of active
            // print ID of input
            // print ID of output
            // contents of entryq
            // contents of inputq
            // contents of outputq
        timer++;
    } while (timer <= MAX_TIME);

    
    return 0;
}
