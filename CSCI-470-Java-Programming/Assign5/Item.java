/**
 * Item Class
 * 
 * Assignment 5
 * David Flowers II
 * Z1942130
 * 
 * Due 11/17/23
 */
 
public class Item {
  private String name;
  private int quantity;
  private double price;
  private String upc;
  
  // Private so it cannot be used without params
  private Item() {}

  Item(String NAME, int QUANTITY, double PRICE, String UPC) {
    name = new String(NAME);
    quantity = QUANTITY;
    price = PRICE;
    upc = new String(UPC);
  }
  
  // Getters
  public String getName() { return name; }
  public int getQuantity() { return quantity; }
  public double getPrice() { return price; }
  public String getUPC() { return upc; }
}
