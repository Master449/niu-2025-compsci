import java.io.File;
import java.util.Scanner;

public class MainClass {

    public static Winner [] listOfWinners;

    public static void loadFromFile() {
        try{
            //Create instance of Scanner and provide instance of File pointing to the txt file
            Scanner input = new Scanner(new File("WorldSeriesWinners.txt"));

            //Get the number of teams
            int years = input.nextInt();
            input.nextLine();//move to the next line

            //Create the array
            listOfWinners = new Winner[years];

            //for every year in the textfile
            for(int index = 0; index<years; index++)
            {
                //Get the year
                int year = input.nextInt();
                input.skip("	");
                //Get the team
                String team = input.nextLine();

                //Create an instance of Winner and add it to the next spot in the array
                listOfWinners[index] = new Winner(team,year);
            }
        } catch(Exception e) {
            System.out.println("Hey Meatbag, I'm Bender, and something wrong in the loadFromFile method happened!");
            System.out.println(e.toString());
            System.exit(0);
        }
    }

    // Plain old Bubble sort for these
    public static void sortByTeamName() {
        int len = listOfWinners.length;
        boolean swapped = false;

        // Nested loop through
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len - i - 1; j++) {
                // Compare the Team names string using compareTo
                if (listOfWinners[j].getTeam().compareTo(listOfWinners[j + 1].getTeam()) > 0) {
                    // If their out of order, swap them
                    Winner temp = listOfWinners[j];
                    listOfWinners[j] = listOfWinners[j + 1];
                    listOfWinners[j + 1] = temp;

                    // Set swapped flag to true
                    swapped = true;
                }
            }

            // If we got through the entire thing, and nothing was swapped
            // its most likely already sorted, and we can leave this
            if (!swapped)
                break;
        }
    }

    // This function is the same one as above, with one change
    public static void sortByYear() {
        int len = listOfWinners.length;
        boolean swapped = false;

        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len - i - 1; j++) {
                // 1 Change: Compare integers instead of strings
                if (listOfWinners[j].getYear() > listOfWinners[j + 1].getYear()) {
                    Winner temp = listOfWinners[j];
                    listOfWinners[j] = listOfWinners[j + 1];
                    listOfWinners[j + 1] = temp;
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }
    }

    public static void printArray() {
        //Print the array
        for(int index=0; index<listOfWinners.length; index++) {
            System.out.println(listOfWinners[index].getYear()+" Winners " + listOfWinners[index].getTeam());
        }
    }

    public static void searchForWinnerByYear(int year) {
        int len = listOfWinners.length;

        // Loop through the elements, and if the year matches, print it
        for (int i = 0; i < len; i++) {
            if (listOfWinners[i].getYear() == year ) {
                System.out.println(listOfWinners[i].getYear() + " " + listOfWinners[i].getTeam());
            }
        }
    }

    public static void searchForYearsATeamWon(String team) {
         int len = listOfWinners.length;

        // Loop through the elements, and if the team name matches, print it
        for (int i = 0; i < len; i++) {
            if (listOfWinners[i].getTeam().equalsIgnoreCase(team)) {
                System.out.println(listOfWinners[i].getYear() + " " + listOfWinners[i].getTeam());
            }
        }
    }

    public static void main(String[] args) {

        int choice;
        Scanner keyboard = new Scanner(System.in);
        System.out.println("World Series Program");

        //Load textfile
        loadFromFile();
        do{
            System.out.println("1.........Print out the Winner List sorted by team name");
            System.out.println("2.........Print out the Winner List sorted by years");
            System.out.println("3.........Print out the Winner of a particular year");
            System.out.println("4.........Print out the years a particular team won");
            System.out.println("5.........Exit the Program");
            System.out.println("Which Choice Would You Like?");
            choice = keyboard.nextInt();

            switch(choice) {
                case 1:
                    //Option 1, sort array by name and print out.
                    sortByTeamName();
                    printArray();
                    break;
                case 2:
                    //Option 2, sort array by year and print out.
                    sortByYear();
                    printArray();
                    break;
                case 3:
                    //Option 3 Search for winner by year
                    System.out.println("What year would you like to find the winner?");
                    int year = keyboard.nextInt();
                    searchForWinnerByYear(year);
                    break;
                case 4:
                    //Option 4 Search for years a team won
                    System.out.println("What team would you like to check for years won?");
                    keyboard.nextLine();
                    String team = keyboard.nextLine();
                    searchForYearsATeamWon(team);
                    break;
                case 5://Exit
                    break;
                default:
                    System.out.println("Invalid Choice");
            }
        } while(choice != 5);

        System.out.println("Goodbye!");
    }
}