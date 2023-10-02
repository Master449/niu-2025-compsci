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
 * Due Date: 09/29/23 by 11:59p                                         *
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
        if (red >= 0 && red <= 255)
            this.redValue = red;

        if (green >= 0 && green <= 255)
            this.greenValue = green;

        if (blue >= 0 && blue <= 255)
            this.blueValue = blue;
    }
}
