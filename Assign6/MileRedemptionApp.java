/**
 * MileRedemptionApp.java
 * 
 * Assignment 6
 * David Flowers II
 * Z1942130
 * 
 * Due 12/01/23
 */
import java.io.File;
import java.util.Scanner;

public class MileRedemptionApp {
    public static void main(String[] args) {
        // Early Declarations
        MileRedeemer mileRedeemer = new MileRedeemer();
        MileTicket[] infoArray = null;
        int usersMiles;
        int usersDepartureMonth;

        // If no input file was provided, exit and print help message
        if (args.length != 1) {
            System.out.println("Usage: java MainProgram <filename>");
            System.exit(1);
        }

        // Create a new MileTicket array and read the file into it
        // (array is sorted in this method as well)
        try {
            infoArray = mileRedeemer.readDestinations(new Scanner(new File(args[0])));
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.exit(2);
        }

        // Create a new Scanner object for user input
        System.out.println("---------------------------------------------------");
        System.out.println("List of destination cities you can travel to:");

        // Print out the destinations
        for (int i = 0; i < infoArray.length; i++) {
            System.out.println(infoArray[i].getDestination());
        }

        System.out.println("---------------------------------------------------");

        // Create a new Scanner object for user input
        Scanner input = new Scanner(System.in);

        // Loop until the user wants to quit

        while (true) {
            // Get the user's input
            try {
                System.out.print("Please input your total accumulated miles: ");
                usersMiles = Integer.parseInt(input.nextLine());

                System.out.print("Please input your month of departure (1-12): ");
                usersDepartureMonth = Integer.parseInt(input.nextLine());

                mileRedeemer.redeem(usersMiles, usersDepartureMonth, infoArray);
                System.out.print("Do you want to continue (y/n) ? ");
                String response = input.nextLine();
            } catch (Exception e) {
                // Print stack trace if theres an error
                e.printStackTrace();
                System.out.println(e); 
                System.out.print("Do you want to continue (y/n) ? ");
                String response = input.nextLine();
            }
        }
    }
}