/********************************************************************
CSCI 490 - Assignment s - Semester Spring 2025

Programmer: David Flowers II
   Section: 1
        TA: Keerthi Kalyan Botu
  Date Due: 02/17/2025

   Purpose: Practice using fork() and other systems calls such as 
            pipe() and wait()

*********************************************************************/
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
#include <tuple>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::to_string;
using std::vector;
using std::strcpy;

// Definitions and constants
#define BUFFER_SIZE 256
#define READ_END    0
#define WRITE_END   1

const int SPACESHIP_CAPACITY = 4;
const int WIN_DISTANCE = 1000;
const int STARTING_DISTANCE = 0;
const int STARTING_FUEL = 300;
const int DELAY = 1;

struct spaceship {
    int pid;
    int distance;
    int fuel;
};

/*
 * clear_screen
 *
 * I really hope this one is self-explanitory
 *************************************************/
void clear_screen() {
    cout << "\033[2J\033[1;1H";
}

/*
 * close_unused_pipes
 *
 * Closes all pipes, except the one that corresponds
 * to the child process writing index
 *
 * Args:
 *    pipe_holder - 2D array, holding the read and write ends of the pipes
 *    skip_index - The only pipe end that the child process needs
 *
 *****************************************************************************/
void close_unused_pipes(int (*pipe_holder)[2], int skip_index) {
    for (int j = 0; j < SPACESHIP_CAPACITY; j++) {
        if (j != skip_index) {
            close(pipe_holder[j][READ_END]);
            close(pipe_holder[j][WRITE_END]);
        }
        else {
            close(pipe_holder[j][READ_END]);
        }
    }
}
/*
 * ship_racing
 *
 * Starts the main loop race for the child process
 *
 * Args:
 *    coms_channel - write end of the childs respective pipe
 *
 *********************************************************************************************/
void ship_racing(int& coms_channel) {
    int distance = STARTING_DISTANCE;
    int fuel = STARTING_FUEL;
    char report[BUFFER_SIZE];
    srand(time(NULL) * getpid());
            

    while (distance < WIN_DISTANCE) {
        // Randomly generate distance moved and fuel used
        int movement = rand() % 51;
        int consumption = rand() % 20 + 1;

        // Can't move if you need to refuel
        // Otherwise, calculate new stats
        if (consumption >= fuel) {
            fuel = 300;
        } else {
            fuel -= consumption;
            distance += movement;
        }
        // Ship writes its report on their position, and sends the data back
        strcpy(report, (to_string(distance) + "," + to_string(fuel)).c_str());
        write(coms_channel, report, strlen(report)+1);
        sleep(DELAY);
    }
}

/*
 * receive_data
 *
 * Reads in the messages from the child process, and processes the data
 *
 * Args:
 *    coms_channel - pipe read end to list on
 *
 * Returns:
 *    <int, int> tuple - containing distance and fuel to report back
************************************************************************************/
std::tuple<int, int> receive_data(int& coms_channel) {
    char report[BUFFER_SIZE];

    // Read report, and convert it to C++ string
    read(coms_channel, report, BUFFER_SIZE);
    string msg(report);
    
    // So we can split the data sent back
    size_t comma = msg.find(',');
    
    // Return both distance and fuel as integers
    return std::make_tuple(std::stoi(msg.substr(0, comma)), std::stoi(msg.substr(comma + 1)));
}

int main() {
    int pipe_holder[SPACESHIP_CAPACITY][2];
    vector<spaceship> fleet(SPACESHIP_CAPACITY);
    bool finished = false;
    int winner_index = 0;

    // Create array of pipes
    for (int i = 0; i < SPACESHIP_CAPACITY; i++) {
        if (pipe(pipe_holder[i]) < 0) {
            cerr << "Error creating pipe";
            return 1;
        }
    }

    // Startup spaceships
    for (int num_process = 0; num_process < SPACESHIP_CAPACITY; num_process++) {
        // Start child process, and exit if we encounter issues
        int pid = fork();
        
        if(pid < 0) {
            cerr << "Fork failure";
            return 2;
        }

        if (pid == 0) {
            // Child process

            // Close the pipes this process doesn't need
            close_unused_pipes(pipe_holder, num_process);

            // Start racing
            ship_racing(pipe_holder[num_process][WRITE_END]);

            // Close their communication line and then exit
            close(pipe_holder[num_process][WRITE_END]);
            return 0;
        } else {
            // Parent process will get here, keeping track of ships
            fleet[num_process].pid = pid;
            fleet[num_process].distance = 0;
            fleet[num_process].fuel = 300;
        }
        
    }

    // Main control center
    while(true) {
        clear_screen();
        cout << "🚀 Intergalactic Space Race Leaderboard 🚀" << endl;
        cout << string(75, '-') << endl;
        
        for (int i = 0; i < SPACESHIP_CAPACITY; i++) {
            int distance, fuel;

            // Receive response
            std::tie(distance, fuel) = receive_data(pipe_holder[i][READ_END]); 

            // Update recording keeping
            fleet[i].distance = distance;
            fleet[i].fuel = fuel; 
            
            // Print out how that ship is doing
            cout << "Spaceship " << (i + 1) << " (🚀" << fleet[i].pid << "): ";
            cout << string(fleet[i].distance / 50, '=');
            cout << " " << fleet[i].distance << " light-years, Fuel: " << fleet[i].fuel << endl;

            // If someones passed the finish line, make note
            if (fleet[i].distance >= WIN_DISTANCE) {
                finished = true;
                winner_index = i + 1;
            }
        }

        // Print footer
        cout << string(75, '-') << endl;
        
        // Check to see if we have a winner
        if (finished) {
            cout << "🎉🚀Spaceship " << winner_index << " won the space race!🚀🎉" << endl;
       
            // In the end, is there really a winner?
            // terminate all child processes
            for (int i = 0; i < SPACESHIP_CAPACITY; i++) {
                //kill(fleet[i].pid, SIGKILL);
                // Arbitrary value to ensure all pipes are closed
                // check logic on this one to see how this works
                close_unused_pipes(pipe_holder, time(NULL));
            }

            return 0;
        }

        sleep(DELAY);
    }
}
