/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 1                  Fall 2023    *
 *                                                                      *
 * App Name: ilikeandroid                                               *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 09/15/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Part 1 of Assignment 1. Familiarizing with                  *
 *          Android Studio. Displays "I like Android".                  *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.ilikeandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}