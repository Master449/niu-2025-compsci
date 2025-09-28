/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 1                  Fall 2023    *
 *                                                                      *
 * App Name: thisisfun                                                  *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 09/15/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Part 2 of Assignment 1. Familiarizing with                  *
 *          Android Studio. Horizontal by default, with                 *
 *          the text "This is fun!" in the left corner.                 *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.thisisfun;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}