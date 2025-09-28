/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 3                  Fall 2023    *
 *                                                                      *
 * App Name: ConstraintLayout Exercise                                  *
 *                                                                      *
 * Class Name: ColorPicker.java                                         *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 10/06/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Helper class to hold the RGB values                         *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.colorapp;

public class ColorPicker {
    private int redValue;
    private int greenValue;
    private int blueValue;

    public ColorPicker(int red, int green, int blue) {
        setColors(red, green, blue);
    }

    public ColorPicker() {
        setColors(0,0,0);
    }

    public int getRed() { return redValue; }
    public int getGreen() { return greenValue; }
    public int getBlue() { return blueValue; }

    public void setColors(int red, int green, int blue) {
        // Error checking is done in MainActivity
        // before being sent here
        this.redValue = red;
        this.greenValue = green;
        this.blueValue = blue;
    }
}
