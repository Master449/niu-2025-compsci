/**
 * RunningTotal Class
 * 
 * Assignment 4 - Part 2
 * David Flowers II
 * Z1942130
 * 
 * Due 10/27/23
 */

import java.util.Scanner;

public class RunningTotal {
    // Product is set to 1 because
    // 0 * anything = 0
    private int product = 1;
    private int sum;
    private int largestNumber;
    private int totalNumbersEntered;

    public void getNumbersFromUser() {
        Scanner sc = new Scanner(System.in);
        int input;

        // User input loop
        do {
            input = sc.nextInt();

            // If it is negative, we don't count it
            if (input >= 0 ) {
                // Add to sum and multiply to product
                sum += input;
                product *= input;
                
                // Check if new number is larger
                if (input > largestNumber)
                    largestNumber = input;

                // Iterate
                totalNumbersEntered++;
            }
        // Loop ends if its negative
        } while(input >= 0);

        // Close Scanner
        sc.close();
    }

    // Getter Methods
    public int getAverage() { return (sum / totalNumbersEntered); }
    public int getProduct() { return product; }
    public int getSum() { return sum; }
    public int getLargestNumber() { return largestNumber; }
}
