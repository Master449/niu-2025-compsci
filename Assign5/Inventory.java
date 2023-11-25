/**
 * Inventory Class
 * 
 * Assignment 5
 * David Flowers II
 * Z1942130
 * 
 * Due 11/17/23
 */

import java.io.*;
import java.util.Scanner;

public class Inventory {
  private Item[] itemArray = new Item[100];
  private int totalItems = 0;

  public int getTotalNumberOfItems() { return totalItems; }
  public Item getItem(int index) { 
    if (index < 0 || index > totalItems)
      return null;

    return itemArray[index];
  }

  public void addItem(Item newItem) {
    if (newItem == null) {
      System.out.println("Item not added");
    } else {
      itemArray[totalItems] = newItem;
      totalItems++;
    }
  }

  public void saveInventoryToFile(String filename) {
    // Create file object
    File file = new File(filename);
    
    // Test to see if it exists
    if (!file.exists()) {
      try {
        // If not, create it
        file.createNewFile();
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    
    // try-catch for PrintWriter
    try {
      // Open the file for printing
      PrintWriter fileBuffer = new PrintWriter(new FileWriter(filename));
      
      // Loop through and add the items into the file
      for (int i = 0; i < totalItems; i++) {
        fileBuffer.print(itemArray[i].getName() + " ");
        fileBuffer.print(itemArray[i].getQuantity() + " ");
        fileBuffer.print(itemArray[i].getPrice() + " ");
        fileBuffer.println(itemArray[i].getUPC());
        fileBuffer.flush();
      }
      
      fileBuffer.close();

    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  
  public void loadInventoryFromFile(String filename) {
    try {
      File file = new File(filename);
      Scanner input = new Scanner(file);
      
      while (input.hasNextLine()) {
        String entireLine = input.nextLine();
        String[] currentItem = entireLine.split(" ");
        
        Item obj = new Item(currentItem[0], Integer.parseInt(currentItem[1]), Double.parseDouble(currentItem[2]), currentItem[3]);

        addItem(obj);
      }

      input.close();
      System.out.println("Inventory loaded");
    } catch (Exception e) {
      System.out.println("No inventory file found.");
    } 
  }
}
