#include "car.h"
#include "garage.h"
#include <stack>
#include <iostream>
#include <string>
#include <deque>

// Prototypes - Documentation is below where the function is implemented
void get_input_vals(const std::string &line, char &xact_type, std::string &license);

/**
 * @brief Reads the transaction records from stdin, parses them by calling 
 * get_input_vals(), and process an arrival or departure based on the value 
 * of the transaction code.
 * 
 * @return int because its main
 */
int main () {
    garage g(10);

    // I used these variable names so they match with the helper function
    std::string line, license;
    char xact_type;

    while (std::getline(std::cin, line)) {
        get_input_vals(line, xact_type, license);
        if (xact_type == 'A') {
            g.arrival(license);
            std::cout << std::endl;
        } else if (xact_type == 'D') {
            g.departure(license);
            std::cout << std::endl;
        } else {
            std::cout << "\'"<< xact_type <<"\'" << ": invalid action!" << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}

/**
 * @brief This is a helper function that extracts the individual components 
 * from the input line by line
 *
 * @param line line number to be read in
 * @param xact_type transaction type
 * @param license license plate number
 */
 void get_input_vals(const std::string &line, char &xact_type, std::string &license) {
    xact_type = line[0];
    license = line.substr(2, line.length() - 3);
 }