/**
 * MileRedeemer.java
 * 
 * Assignment 6
 * David Flowers II
 * Z1942130
 * 
 * Due 12/01/23
 */
import java.util.ArrayList;
import java.util.Scanner;

public class MileRedeemer {
    private MileTicket[] tickets = new MileTicket[1];
    private int remainingMiles;

    MileRedeemer() {
        remainingMiles = 0;
    }

    /*
     * Reads the file and returns an array of MileTicket objects
     * 
     * @param fileScanner Scanner object to read the file
     * 
     * @return MileTicket[] Array of MileTicket objects
     */
    public MileTicket[] readDestinations(Scanner fileScanner) {
        // Keep track of the array index
        int ar = 0;

        try {
            while (fileScanner.hasNextLine()) {
                String entireLine = fileScanner.nextLine();

                // Split the line into an array by ;
                String[] currentItem = entireLine.split(";");

                // Split the months into an array by -
                String[] months = currentItem[4].split("-");

                // Resize the array if we need to
                if (ar >= tickets.length) {
                    tickets = resizeArray(tickets, tickets.length + 1);
                }

                // Create a new MileTicket object
                MileTicket obj = new MileTicket(currentItem[0], Integer.parseInt(currentItem[1]),
                        Integer.parseInt(currentItem[2]), Integer.parseInt(currentItem[3]), Integer.parseInt(months[0]),
                        Integer.parseInt(months[1]));

                // Add it to the array and increment the index
                tickets[ar] = obj;
                ar++;
            }
            fileScanner.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println(e); 
        }

        // Sort the array
        int len = tickets.length;
        boolean swapped = false;

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len - i - 1; j++) {
                // Compare the Normal Miles using overridden equals method
                if (tickets[j].equals(tickets[j + 1])) {
                    // If their out of order, swap them
                    MileTicket temp = tickets[j];
                    tickets[j] = tickets[j + 1];
                    tickets[j + 1] = temp;

                    // Set swapped flag to true
                    swapped = true;
                }
            }

            // If we got through the entire thing, and nothing was swapped
            // its most likely already sorted, and we can leave this
            if (!swapped)
                break;
        }

        return tickets;
    }

    /*
     * Redeems the miles for the user
     * 
     * @param miles The miles the user has
     * @param month The month the user is leaving
     * @param des The array of MileTicket objects
     * 
     */
    public void redeem(int miles, int month, MileTicket[] des) {
        // Since we sorted the array when we read it in, 
        // we can assume the first is the farthest distance
        int arraySize = tickets.length;
        ArrayList<Integer> classResults = new ArrayList<Integer>();

        for (int i = 0; i < arraySize; i++) {
            MileTicket currentTicket = tickets[i];

            // Check for super saver case
            if (month >= currentTicket.getStartMonth() && month <= currentTicket.getEndMonth()) {
                // If we have enough miles to use this ticket
                if (miles > currentTicket.getSuperSaverMiles()) {
                    miles -= currentTicket.getSuperSaverMiles();
                    classResults.add(1);

                    // If we used this ticket, skip the rest of the loop
                    continue;
                }
            }

            // Check for normal case
            if (miles > currentTicket.getNormalMiles()) {
                miles -= currentTicket.getNormalMiles();
                classResults.add(1);

                // If we used this ticket, skip the rest of the loop
                continue;
            }

            // If we got down here neither one was used.
            // this is mainly to keep the arrays the same size.
            classResults.add(0);
        }

        // Check for upgrades loop
        for (int i = 0; i < arraySize; i++) {
            MileTicket currentTicket = tickets[i];

            // If we didn't use this ticket, skip it
            if (classResults.get(i) == 0)
                continue;

            // If we don't have enough miles to upgrade, break
            if (miles <= 0)
                break;

            // If we have enough miles to upgrade
            if (miles > currentTicket.getAdditionalMiles()) {
                miles -= currentTicket.getAdditionalMiles();
                classResults.set(i, 2);
            }
        }

        printTickets(des, classResults, miles);
    }

    /*
     * Prints the tickets for the user
     * 
     * @param sortedDes The sorted array of MileTicket objects
     * @param results The ArrayList of results from the redeem method
     * @param remainMiles The remaining miles the user has
     * 
     */
    public void printTickets(MileTicket[] sortedDes, ArrayList<Integer> results, int remainMiles) {
        int arraySize = results.size();

        System.out.println("Your accumulated miles can be used to redeem the following tickets:");

        // Loop through the results array and print out the tickets
        for (int i = 0; i < arraySize; i++) {

            // If we didn't use this ticket, skip it
            if (results.get(i) == 0) {
                continue;
            }

            System.out.print("* A trip to " + sortedDes[i].getDestination() + ", ");
            
            // Check if we upgraded the ticket
            if (results.get(i) == 2)
                System.out.println("first class");
            // if not, economy class
            else
                System.out.println("economy class");
        }

        System.out.println("Your remaining miles: " + remainMiles);
    }

    /*
     * Resizes the array
     * 
     * @param arr The array to resize
     * @param newSize The new size of the array
     * 
     * @return MileTicket[] The resized array
     */
    private MileTicket[] resizeArray(MileTicket[] arr, int newSize) {
        MileTicket[] temp = new MileTicket[newSize];
        for (int i = 0; i < arr.length; i++) {
            temp[i] = arr[i];
        }

        return temp;
    }
}