/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 2                  Fall 2023    *
 *                                                                      *
 * App Name: ConstraintLayout Exercise                                  *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 09/22/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Part 1 of Assignment 1. Familiarizing with                  *
 *          Android Studio constraints.                                 *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.constraintlayoutexercise;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}