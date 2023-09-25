
/*******************************************************
 *   CSCI 470        Assignment 2        Fall 2023
 *   
 *   Author: David Flowers II
 *   Due: 9/29/23
*******************************************************/

import java.util.Scanner;

public class FBMICalc {
    public static void main(String[] args) {
        double circumferenceRigcage, legLength, BMI;
        String catName, result;
        Scanner userInput = new Scanner(System.in);

        // Print a welcome message
        System.out.println("Welcome to the Feline Body Mass Index Calulator. Just need a few questions from you: ");
        
        // Ask for the cats name
        System.out.print("\tWhat is your cats name?: ");
        catName = userInput.nextLine();

        // Get the circumference of their ribcage
        System.out.print("\tWhat is the circumference of " + catName + " ribcage?: ");
        circumferenceRigcage = userInput.nextDouble();

        // Get the length of their leg
        System.out.print("\tWhat is the length of " + catName + " leg?: ");
        legLength = userInput.nextDouble();

        // Calculate BMI
        BMI = ((circumferenceRigcage / 0.7062) - legLength) / 0.9156 - legLength;

        // Switch statements don't have conditionals
        if (BMI < 10) {
            result = "Very Underweight";
        } else if (BMI < 15) {
            result = "Underweight";
        } else if (BMI < 30) {
            result = "Normal";
        } else if (BMI < 35) {
            result = "Overweight";
        } else if (BMI < 30) {
            result = "Obese";
        } else {
            result = "Very Obese";
        }

        // Output the cats BMI, and the catergory they fall under
        System.out.format("%ss BMI is %.2f", catName, BMI);
        System.out.println("\nThis puts them into the " + result + " catergory.");
    }
}