/*******************************************************
 *   CSCI 470        Assignment 1        Fall 2023
 *   
 *   Author: David Flowers II
 *   Due: 9/15/23
*******************************************************/

import java.util.Scanner;

public class WordGame {
    public static void main(String[] args) {
        // Users input variables
        String usersName, usersCity, favoriteAnimal, petType, petName, usersAge, modifyGrammar;

        // Scanner to get input
        Scanner userInput = new Scanner(System.in);

        // Get users name
        System.out.print("What is your name? ");
        usersName = userInput.nextLine();

        // Get users age
        System.out.print("What is your age? ");
        usersAge = userInput.nextLine();

        // Get where user grew up
        System.out.print("Where did you grow up? ");
        usersCity = userInput.nextLine();

        // Get users pet
        System.out.print("What kind of animal was your first pet? ");
        petType = userInput.nextLine();

        // Get users pets name
        System.out.print("What is their name? ");
        petName = userInput.nextLine();

        // Sorry I really didn't like 'an' when theres not a vowel.
        // Just uses the matches method with regex
        if (petType.matches("(a|e|i|o|u).*") || petType.matches("(A|E|I|O|U).*")) {
          modifyGrammar = "an ";
        } else {
          modifyGrammar = "a ";
        }

        // Slap em all together and print it out
        System.out.println(usersName + " lived in " 
                        + usersCity + ". At the age of " 
                        + usersAge + " adopted "
                        + modifyGrammar
                        + petType + " named " 
                        + petName + ".");
      }
}
