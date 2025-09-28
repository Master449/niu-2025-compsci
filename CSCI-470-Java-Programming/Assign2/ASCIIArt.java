/*******************************************************
 *   CSCI 470        Assignment 2        Fall 2023
 *   
 *   Author: David Flowers II
 *   Due: 9/29/23
*******************************************************/

import java.util.Scanner;

public class ASCIIArt {
    public static void main(String[] args) {
        int choice = 0;
        Scanner userInput = new Scanner(System.in);

        // The absolute mess of Java ASCII Art Strings
        String trapezoid = "    *********    \n   *         *   \n  *           *  \n *************** \n";
        String heptagon = "     *      \n  *     *   \n*         * \n*         * \n*         * \n*         * \n  *     *   \n    ***     \n";
        String rectangle = "***************\n*             *\n*             *\n*             *\n***************\n";
        String rightTriangle = "*           \n*  *        \n*     *     \n*       *   \n*         * \n************\n";
        String square = "* * * * * * * *\n*             *\n*             *\n*             *\n*             *\n*             *\n* * * * * * * *\n";
        
        // Fancy list to let the user choose which shape they want
        System.out.print("Please select your choice of ASCII Shape:\n\t1. Trapezoid\n\t2. Heptagon\n\t3. Rectangle\n\t4. Right Triangle\n\t5. Square\n\nChoice: ");

        // While loop to validate user input
        // used a do while loop since I want
        // it to run at least once
        do {

            // Get users input
            choice = userInput.nextInt();

            // Switch statement to print out the list
            switch(choice) {
                case 1: System.out.println(trapezoid);
                        break;
                case 2: System.out.println(heptagon);
                        break;
                case 3: System.out.println(rectangle);
                        break;
                case 4: System.out.println(rightTriangle);
                        break;
                case 5: System.out.println(square);
                        break;
                default: System.out.print("I'm sorry, that is out of the range of 1 - 5. Please try again.\nChoice: ");
                        break;
            }
        } while (choice <= 0 || choice > 5);
    }
}
