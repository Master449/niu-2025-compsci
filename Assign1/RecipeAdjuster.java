/*******************************************************
 *   CSCI 470        Assignment 1        Fall 2023
 *   
 *   Author: David Flowers II
 *   Due: 9/15/23
*******************************************************/

import java.util.Scanner;

public class RecipeAdjuster {
    public static void main(String[] args) {
        // These are all doubles, because the calculation
        // might result in a decimal and I don't want to
        // deal with Javas funkiness.
        double cupsSugar = 2;
        double cupsButter = 1;
        double cupsFlour = 3;
        double input;

        Scanner userInput = new Scanner(System.in);

        System.out.print("How mant cookies did you want to make? ");
        input = userInput.nextDouble();

        System.out.println("You will need the following to bake " + input + " cookies.");
        System.out.println("\t" + ((input / 48) * cupsSugar) + " cups of sugar");
        System.out.println("\t" + ((input / 48) * cupsButter) + " cups of butter");
        System.out.println("\t" + ((input / 48) * cupsFlour) + " cups of flour");
    }
}
