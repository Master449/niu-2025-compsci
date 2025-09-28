// - - - - - - - - - - - - - - - - - - - - - -
//
//  bubble_sort.cpp
//  CSCI 241 Assignment 1
//
//  Created by David Flowers II (z1942130)
//
// - - - - - - - - - - - - - - - - - - - - - -

#include <iostream>
#include <iomanip>
#include <utility>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::swap;
using std::array;

int main(){
    int numbers[1000];
    int count = 0;
    int i;
    bool swapped;

    /* This single while loop counts each element that 
       it took in to get the max number of elements */
    while (cin >> numbers[count]) { count++; }

    /* This do loop starts the bubble sort, comparing
       first checking, if they are already swapped, 
       then moving onto the next pair, this loop starts
       and continues as long as swapped = true */
    do {
        swapped = false;
        i = 1;
        while(i < count){
            if (numbers[i - 1] > numbers[i]){

                // std swap function so I won't have to write it out
                swap(numbers[i - 1], numbers[i]);
                swapped = true;
            }
            i++;
        }
    } while (swapped);

    /* After it gets out of the loop and then down here
       it prints all values inside of the array */
    for(int i = 0; i < count; i++){
        cout << setw(8) << numbers[i];

        /* This if statement sees element the loop is on
           if you modulo it with 8 and gets 0 it is time
           for a new line */
        if ( (i + 1) % 8 == 0) { cout << endl; }
    }
    cout << endl;
}

