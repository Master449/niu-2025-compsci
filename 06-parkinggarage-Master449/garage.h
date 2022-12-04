#ifndef GARAGE_H
#define GARAGE_H

#include <stack>
#include <string>
#include <deque>
#include <iostream>
#include "car.h"

class garage {
    public:
        garage(size_t limit = 10) : parking_lot_limit(limit) {}

        /// @param license The license of the car that has arrived.                                                           
        void arrival(const std::string &license);

        /// @param license The license of the car that has departed.                                                          
        void departure(const std::string &license);

    private:
        int next_car_id = { 1 };
        std::deque<car> parking_lot;
        size_t parking_lot_limit;
};

/**
 * @brief Creates a car object and use it to print itself as part 
 * of a message announcing its arrival. 
 *
 * If the garage is already full of cars then prints a message so 
 * indicating that fact (see the reference output.) 
 * 
 * @param license to insert and print
 */
void garage::arrival(const std::string &license) {
    car new_car(next_car_id, license);
    std::cout << new_car << " has arrived." << std::endl;

    if (parking_lot.size() >= parking_lot_limit) {
        std::cout << "    But the garage is full!" << std::endl;
    } else {
        parking_lot.push_back(new_car);
    }

    next_car_id++;

    //std::cout << "\n parkinglotsize = " << parking_lot.size() << "\n parkinglotlimit = " << parking_lot_limit << "\n";
    // I used this for debugging
}

/**
 * @brief Check each of the car elements in the parking_lot d
 * 
 * @param license to find, depart, and print
 */
void garage::departure(const std::string &license) {
    std::stack<car> temp_stack;
    bool found = false;

    for (auto it = parking_lot.begin(); it != parking_lot.end(); it++) {
        if (it->get_license() == license) {

            std::cout << *it << " has departed," << std::endl;
            found = true;
            
            if (it->get_num_moves() == 0) {
                std::cout << "    car was moved " << it->get_num_moves() + 1 << " time in the garage." << std::endl;
            } else {
                std::cout << "    car was moved " << it->get_num_moves() + 1 << " times in the garage." << std::endl;
            }

            parking_lot.pop_front();
            break;

        } else {
            it->move();
            temp_stack.push(*it);
            parking_lot.pop_front();
        }
    }

    if (!found) {
        std::cout << "No car with license plate \"" << license << "\" is in the garage." << std::endl;
    }

    while (!temp_stack.empty()) {
        parking_lot.push_front(temp_stack.top());
        temp_stack.pop();
    }
}
#endif
