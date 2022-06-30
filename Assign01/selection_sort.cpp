// - - - - - - - - - - - - - - - - - - - - - -
//
//  selection_sort.cpp
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
    int i, j, min_index;

    /* This single while loop counts each element that 
       it took in to get the max number of elements */
    while (cin >> numbers[count]) { count++; }
  
    /* This sorting method looks for the smallest value
       in the array first, keeps note of it, and then a
       second loop iterates through and swaps them */
    while (i < count - 1){
        min_index = i;
        j = i + 1;
        while(j < count){
            if (numbers[j] < numbers[min_index]){
                min_index = j;
            }
            j++;
        }
        swap(numbers[i], numbers[min_index]);
        i++;
    }

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
