
#include "josephus.h"

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>


void print_underlined_string(const std::string &message);
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols);


/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of people with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line

    unsigned elims = 0; // The number of eliminations so far
    std::list<std::string> people;
    std::generate_n (std::back_inserter(people), num_people, SEQ(num_people));

    print_list(people, elims, num_cols);
    std::cout << std::endl;
    std::list<std::string>::iterator it = people.begin();
    
    // Loop will continue until there is only 1 person remaining
    while (people.size() > 1) {

        // This will loop through modulus (starting at 1)
        for (unsigned i = 1; i < modulus; i++) {
            ++it;
            // If we are at the end of the list, loop back around
            if (it == people.end())
                it = people.begin();
        }

        // Once the loop exits, you're on your man that needs to be eliminated
        it = people.erase(it);
        elims++;

        // Checks if it is time to print again
        if (elims % print_frequency == 0) {
            print_list(people, elims, num_cols);
            std::cout << std::endl;
        }

        // Checks again, incase we erased the last person
        if (it == people.end())
            it = people.begin();
    }

    std::cout << "Eliminations Completed" << std::endl;

    print_list(people, elims, num_cols);
    
    return 0;
}

/**
 * @brief Prints the given message with an underline that
 *        matches the length of the message text.
 * 
 * @param message to be printed
 */
void print_underlined_string(const std::string &message) {
    std::cout << message << std::endl;
    std::cout << std::string(message.length(), '-') << std::endl;
}

/**
 * @brief Prints a heading including the number of eliminations and 
 *        the contents of collection with num_cols elements on each line. 
 *        When eliminations are zero, prints the Initial group of people as 
 *        the table heading. Otherwise, print After eliminating N people where 
 *        N is the number of eliminations.
 * 
 * @param collection to be printed
 * @param eliminations # of elims
 * @param num_cols columns to be printed
 */
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols) {
    std::string heading;

    // If eliminations is zero, print the Initial group of people as the table heading.
    if (eliminations == 0) {
        heading = "Initial group of people";
    } else {
    // Otherwise, print After eliminating N people where N is the number of eliminations.
        heading = "After eliminating " + std::to_string(eliminations) + " people";
    }

    // Print the heading
    print_underlined_string(heading);

    // Keeps track of the number of elements printed on the current line
    int k = 0;

    for (auto it = collection.begin(); it != collection.end(); ++it) {
        // If this is the end of a line OR the last element print the value and a newline
        if (k % num_cols == num_cols - 1 || k == int(collection.size()) - 1) {
            std::cout << *it << std::endl;
        // Else print the value with a comma after it
        } else {
            std::cout << *it << ", ";
        }
        k++;
    }
}
