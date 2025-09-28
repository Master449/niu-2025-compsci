/********************************************************************
CSCI 490 - Assignment 1 - Semester Spring 2025

Programmer: David Flowers II
   Section: 1
        TA: Keerthi Kalyan Botu
  Date Due: 01/28/2025

   Purpose: To process strings from a variety of system files
            located on turing and hopper.
*********************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>

// STL utilities we need
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::stoi;
using std::stod;
using std::setprecision;
using std::set;

/* 
 * Helper struct for processing /proc/cpuinfo
 *********************************************/
struct cpu_info {
    string vendor;
    string model;
    string address_size;
    string virt_address_size;
    int processors;
    int chips;
};

/* Helper struct for processing seconds into
 * days hours minutes and seconds
 * This is named "not_ctime" because I can't use time 
 * ("do you mean ctime?" compiler warning) 
 ****************************************************/
struct not_ctime {
    int days;
    int hours;
    int minutes;
    int seconds;
};

/* read_system_file
 *
 * Args: 
 *    path - Path to a file as a string
 *
 * Returns:
 *    String of files output
 **************************************/
string read_system_file(string path) {
    ifstream input_file(path);
    string line;
    string output;

    // Read in the input file
    while (getline(input_file, line)) {
        output += line;
        
        // If this line is not the end of the file, add newline
        if (input_file.peek() != EOF) {
            output += "\n";
        }
    }

    input_file.close();
    return output;
}

/* read_cpu
 *
 * Args: none
 *
 * Returns:
 *    cpu_info struct object, containing:
 *        - vendor
 *        - model
 *        - address_size
 *        - virt_address_size
 *        - processors
 *        - chips
 *****************************************/
cpu_info read_cpu() {
    stringstream cpuinfo(read_system_file("/proc/cpuinfo"));
    string line;

    // Helper struct (also in the header)
    cpu_info info;

    // Set to we can track unique IDs
    set<int> phys_ids;

    // For each "processor" line we have, add 1 
    while(getline(cpuinfo, line)) {
        size_t colon = line.find(":");
        
        // Make sure the colon exists
        if (colon != string::npos) {
            // Count "processors"
            if (line.find("processor") == 0) {
                info.processors += 1;
            // Get vendor_id if its empty
            } else if (line.find("vendor_id") == 0 && info.vendor.empty()) {
                info.vendor = line.substr(colon + 2);
            // Get model name if its empty
            } else if (line.find("model name") == 0 && info.model.empty()) {
                info.model = line.substr(colon + 2);
            // Track physical IDs in the set above
            } else if (line.find("physical id") == 0) {
                string id_str = line.substr(colon + 2);
                phys_ids.insert(stoi(id_str));
            // Get address sizes
            } else if (line.find("address sizes") == 0 && info.address_size.empty() && info.virt_address_size.empty()) {
                string address = line.substr(colon + 2);
                info.address_size = address.substr(0, address.find(" physical"));
                info.virt_address_size = address.substr(address.find(",") + 2, address.find(" virtual"));
            }
        }   
    }
    // Get the number of physical chips
    info.chips = phys_ids.size();
    return info; 
}

/*
 * convert_time
 *
 * Args:
 *    t - time in seconds
 *
 * Returns
 *    not_ctime struct containing:
 *        - days 
 *        - hours 
 *        - minutes
 *        - seconds
 ***********************************/
not_ctime convert_time(double t) {
    not_ctime time;
    int seconds, minutes, hours, days;

    seconds = t;

    minutes = seconds / 60;
    seconds %= 60;

    hours = minutes / 60;
    minutes %= 60;

    days = hours / 24;
    hours %= 24; 

    time.days = days;
    time.hours = hours;
    time.minutes = minutes;
    time.seconds = seconds;
    return time;
}

/*
 * handle_columns
 *
 * Args:
 *    text - string to handle
 *    len - length of what I am seeking
 *    array - pointer to array to place strings
 *
 * Returns: none (but array passed in is changed)
 ***************************************************/
void handle_columns(string text, int len, string *array) {
    stringstream input(text);
    string cpu_time_array[len];
    int i = 0;

    while (input.good() && i < len) {
        input >> array[i];
        i++;
    }
}

// Entrypoint
int main() {
    //
    // Question A
    //
    // Get the string format from these files
    string ostype = read_system_file("/proc/sys/kernel/ostype");
    string hostname = read_system_file("/proc/sys/kernel/hostname");
    string osrelease = read_system_file("/proc/sys/kernel/osrelease");
    string version = read_system_file("/proc/sys/kernel/version");
    
    // Cleanup version string
    string clean_version = version.substr(version.find("n ") + 2, version.back() - 1);

    cout << "A. Questions about " << hostname << "'s OS: " << endl;
    cout << "1. " << hostname << "s os type is " << ostype << endl;
    cout << "2. " << hostname << "s hostname is " << hostname << endl;
    cout << "3. " << hostname << "s OS release is " << osrelease << endl;
    cout << "4. " << hostname << "s kernel version is " << clean_version << endl << endl;;
    
    //
    // Question B
    //

    // Read in the uptime file, and get the data needed from /proc/cpuinfo
    string uptime = read_system_file("/proc/uptime");
    cpu_info info = read_cpu();

    // Process the uptime string
    double clean_uptime = stod(uptime.substr(0, uptime.find(" ")));

    // Also convert it to days, hours, minutes, and seconds
    not_ctime up = convert_time(clean_uptime);    

    cout << "B. Questions about " << hostname << "'s processes" << endl;
    cout << "1. " << hostname << " has " << info.processors << " processors" << endl;
    cout << "2. " << hostname << " has " << info.chips << " physical chips" << endl;
    cout << "3. " << hostname << " has been up " << setprecision(10) << clean_uptime << " seconds" << endl;
    cout << "4. or " << up.days << " days, " << up.hours << " hours, " << up.minutes << " minutes and " << up.seconds << " seconds" << endl << endl;

    //
    // Question C
    //
    
    // These fields were added into the cpu_info struct and function from above
    cout << "C. For processor 0:" << endl;
    cout << "1. The CPU vendor is " << info.vendor << endl;
    cout << "2. The CPU model name is " << info.model << endl;
    cout << "3. The physical address size is " << info.address_size << endl;
    cout << "4. The virtual address size is " << info.virt_address_size << endl << endl;

    //
    // Question D
    //

    // Read file
    string stat = read_system_file("/proc/stat");

    // Trim front and back of the input from the file 
    string trim_front = stat.substr(stat.find("cpu5"));
    string cpu5 = trim_front.substr(0, trim_front.find("\n"));

    // Call handle columns to pack it nicely into an array 
    string cpu_time_array[10];
    handle_columns(cpu5, 10, cpu_time_array); 

    // Get the idle time in human-readable format
    // 1x jiffy = 0.01 seconds, so we need to convert these values
    not_ctime idle = convert_time(stod(cpu_time_array[4]) / 100); 
    
    cout << "D. For processor 5:" << endl;
    cout << "1. It has spend " << stoi(cpu_time_array[1]) / 100  << " seconds in user mode" << endl;
    cout << "2. It has spent " << stoi(cpu_time_array[3]) / 100 << " seconds in system mode" << endl;
    cout << "3. It has been idle for " << stoi(cpu_time_array[4]) / 100 << " seconds" << endl;
    cout << "4. Which is " << idle.days << " days, " << idle.hours << " hours, " << idle.minutes << " minutes" << endl << endl;;

    //
    // Question E
    //

    // Read the file and start a stringstream
    string swaps = read_system_file("/proc/swaps");

    // Output may have more swap devices, but we are only going to look at the first (place #8, or 7 if 0-index)
    //    1                                       2               3               4               5
    //    Filename                                Type            Size            Used            Priority
    //    /dev/md2                                partition       19514236
    //    6                                       7               8 
    string swap_array[8];
    handle_columns(swaps, 8, swap_array); 

    cout << "E. The size of " << hostname << "'s swap device is " << stoi(swap_array[7]) / 1024  << "MB." << endl;

    return 0;
}
