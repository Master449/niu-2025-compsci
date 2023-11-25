/**
 * InventoryTrackerInterface Class
 * 
 * Assignment 5
 * David Flowers II
 * Z1942130
 * 
 * Due 11/17/23
 */

import java.util.Scanner;

public class InventoryTrackerInterface {
  public static void main(String[] args) {
    int choice = 0;
    Inventory inv = new Inventory();
    Scanner input = new Scanner(System.in);

    while (choice != 5) {
      // Print out the options menu
      System.out.println("1. Add an item to the inventory"); 
      System.out.println("2. Get an items info"); 
      System.out.println("3. Save Inventory to File"); 
      System.out.println("4. Load Inventory from file"); 
      System.out.println("5. Exit");
      
      // Using nextLine instead of nextInt, because
      // nextInt is annoying with leaving the newline
      choice = Integer.parseInt(input.nextLine());
      
      switch(choice) {
        
        // ADD ITEM CASE
        case 1:
          // Get all the info from user
          System.out.println("Enter the new items name");
          String name = input.nextLine();
        
          System.out.println("Enter the new items quantity");
          int quan = Integer.parseInt(input.nextLine());

          System.out.println("Enter the new items price");
          double price = Double.parseDouble(input.nextLine());
          
          System.out.println("Enter the new items upc");
          String upc = input.nextLine();
          
          // Create a new item with it and add it to inventory
          Item it = new Item(name, quan, price, upc);
          inv.addItem(it);
          break;
        
        // GET ITEM INFO CASE
        case 2:
          // If theres 0 items, theres no info to give
          if (inv.getTotalNumberOfItems() == 0) {
            System.out.println("No items in inventory.");
            break;
          }
          
          // but if there is more items, we can give info
          System.out.println("Which item would like info for? [0 - " + (inv.getTotalNumberOfItems() - 1) + "]");
          int infoID = Integer.parseInt(input.nextLine());
          
          // Minor error handling
          if (infoID > inv.getTotalNumberOfItems() - 1 || infoID < 0) {
            System.out.println("Choice must be between 0 and " + (inv.getTotalNumberOfItems() - 1));
          } else {
            System.out.println("Name:     " + inv.getItem(infoID).getName());
            System.out.println("Quantity: " + inv.getItem(infoID).getQuantity());
            System.out.println("Price:    " + inv.getItem(infoID).getPrice());
            System.out.println("UPC:      " + inv.getItem(infoID).getUPC());
          }

          break;

        // SAVE INVENTORY CASE
        case 3:
          inv.saveInventoryToFile("inventory");
          System.out.println("Inventory saved");
          break;
        
        // LOAD INVENTORY CASE
        case 4:
          // Error is handled from Inventory.class
          inv.loadInventoryFromFile("inventory");
          break;
        
        // EXIT CASE
        case 5:
          System.out.println("Goodbye!");
          break;
      }

    }
  }
}
