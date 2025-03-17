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
    deque<Process> entryq, readyq, inputq, outputq;
    vector<string> temp_process;

    // Read in the input file
    while (getline(input_file, process_name_line)) {
        // Check for input delimiter
        if (process_name_line.find("STOPHERE") != string::npos) 
            break;

        // Spin up some temporary variables, and a new Process class
        string temp, type, burst;
        Process tmp_process;
        stringstream fl(process_name_line);
        vector<pair<char, int>> temp_history;

        // Process the name and arrival time, assigning it
        // to the newly created class
        fl >> temp;
        tmp_process.name = temp;
        fl >> temp;
        
        tmp_process.arrival_time = stoi(temp);
        tmp_process.id = process_id;

        // Grab the next line, which will be the history of the process
        getline(input_file, process_stat_line);

        stringstream sl(process_stat_line);

        while (sl >> type >> burst) {
            if (type == "N" && burst == "0") 
                break;
            char t = type[0];
            int b = stoi(burst);
            tmp_process.history.push_back(std::make_pair(t, b));
        }

        entryq.push_back(tmp_process);
        process_id++;
    }

    for (long unsigned int i = 0; i < entryq.size(); i++) { entryq[i].debug_info(); }

    input_file.close();
    return 0;
}
