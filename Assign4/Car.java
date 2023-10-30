/**
 * Car Class
 * 
 * Assignment 4 - Part 1
 * David Flowers II
 * Z1942130
 * 
 * Due 10/27/23
 */

import java.time.Year;

public class Car {
    private String modelName;
    private String brand;
    private int year;
    private double mpg;

    // Constructors
    Car(String b, String mn, int y, double d) {
        brand = new String(b);
        modelName = new String(mn);
        year = y;
        mpg = d;
    }

    Car(String b, int y, double d) {
        brand = new String(b);
        modelName = new String("NA");
        year = y;
        mpg = d;
    }

    // Getter Methods
    public String getModelName() { return modelName; }
    public String getBrand() { return brand; }
    public int getYear() { return year; }
    public double getMPG() { return mpg; }

    // Method to determine practicality
    //
    // MPG must be greater than 25
    // Must be made within the last 15 years
    // Model must be anything but NA
    public boolean isPractical() {
        int currentYear = Year.now().getValue();

        if (mpg > 25 && (currentYear - year) < 15 && !(brand.equals("NA")))
            return true;

        return false;
    }
}