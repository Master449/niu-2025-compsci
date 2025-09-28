//-------------------------------------------
//
//	queens.cpp
//	CSCI 241 Assignment 2
//
//	Created by David Flowers II (z1942130)
//
//--------------------------------------------

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

const int SIZE = 8;

/**
 * void solve(param 1, param 2)
 * 
 * This is the recursive function. It utilizes the function below to check
 * placement of the queen before calling itself once again.
 *
 * @param 1 Int. The board to be passed to the function.
 * @param 2 Int. Just an index variable.
 * 
 ********************************************************************************/
bool place_queen(int board[][SIZE], int);

/**
 * void check(param 1, param 2, param 3)
 * 
 *  This function is used by the solve function to check the spaces, next to
 *  and diagonally, for other queens.
 *
 * @param 1 Int. The board to be passed to the function.
 * @param 2 Int. Row currently on.
 * @param 3 Int. Column currently on.
 * 
 ********************************************************************************/
bool check(int board[][SIZE], int, int);

int main(){
    int chessboard[SIZE][SIZE];

    // This function sets all values to 0, using the sizeof function to get the array size
    memset(chessboard, 0, sizeof(chessboard));

    place_queen(chessboard, 0);

    /* Two loops together to print the 2D Array
       Could put this in another function, but I 
       didnt want to add another func documentation */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << chessboard[i][j] << " ";

            // After 8 numbers are printed, it adds a newline
            if ( (j + 1) % 8 == 0){
                cout << endl;
            }
        }
    }
}

// - - - - - - - - Functions - - - - - - - - -
// Check the prototypes for the documentation
bool place_queen(int board[SIZE][SIZE], int index){
    if (index >= SIZE) { return true; }

    for (int i = 0; i < SIZE; i++){
        if (check(board, i, index)) { 
            board[i][index] = 1; 
            if (place_queen(board, index + 1)) { return true; }
        }
        board[i][index] = 0;
    }

    return false;
}

bool check(int board[][SIZE], int row, int column){
    for (int i = 0; i < SIZE; i++){ if(board[row][i]) { 
        return false; 
        }
    }

    for (int i = row, j = column; i >= 0 && j >= 0; i--, j--){ 
        if(board[i][j]) { 
            return false; 
        }
    }

    for (int i = row, j = column; j >= 0 && i < SIZE; i++, j--){ 
        if(board[i][j]) { 
            return false; 
        }
    }
    
    return true;
}
