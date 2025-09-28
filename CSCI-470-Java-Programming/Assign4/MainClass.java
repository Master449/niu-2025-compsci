/**
 * MainClass Class
 * 
 * Assignment 4 - Part 2
 * David Flowers II
 * Z1942130
 * 
 * Due 10/27/23
 */

public class MainClass {
    public static void main(String[] args) {
        RunningTotal yeehaw = new RunningTotal();

        // Call user input method
        yeehaw.getNumbersFromUser();

        // Print out their stats
        System.out.println("Sum:            " + yeehaw.getSum());
        System.out.println("Product:        " + yeehaw.getProduct());
        System.out.println("Average:        " + yeehaw.getAverage());
        System.out.println("Largest Number: " + yeehaw.getLargestNumber());
    }
}
