#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>

class car {
    public:
        car(int id, const std::string &license) : id(id), license(license) {}

        /// Call this to increment the number of times the car has been moved.
        void move();

        /// @return the number of times that the car has been moved.
        int get_num_moves() const;
        
        /// @return A reference to the license for this car.
        const std::string &get_license() const;

        /**
        * Overload the << so this can print itself as:
        *    Car X with license plate "Y"
        ******************************************************************/
        friend std::ostream& operator<<(std::ostream& lhs, const car& rhs);

    private:
        int id;                 ///< The ID number for this car (assigned by the garage)
        std::string license;    ///< license plate of this car.
        int num_moves = {0};    ///< how many times the car was moved within the garage.
};

/**
 * @brief function to be called when a car is moved. Increases
 * num_moves by 1.
 * 
 */
void car::move() {
    num_moves++;
}

/**
 * @brief function to return the number of times a car has been moved.
 * 
 * @return int number of times the car has moved
 */
int car::get_num_moves() const {
    return num_moves;
}

/**
 * @brief function to return the license plate of a car.
 * 
 * @return string license plate of the car
 */
const std::string &car::get_license() const {
    return license;
}

/**
 * @brief Overload the << so this can print itself as:
 *    Car X with license plate "Y"
 * 
 * @param lhs left hand side (cout)
 * @param rhs right hand side (car object)
 */
std::ostream& operator<<(std::ostream& lhs, const car& rhs) {
    lhs << "Car " << rhs.id << " with license plate \"" << rhs.license << "\"";
    return lhs;
}

#endif