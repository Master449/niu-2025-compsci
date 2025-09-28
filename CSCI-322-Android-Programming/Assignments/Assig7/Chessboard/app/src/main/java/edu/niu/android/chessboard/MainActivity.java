/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 7                  Fall 2023    *
 *                                                                      *
 * App Name: chessboard                                                 *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 12/08/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: 8x8 Chessboard pattern that looks good in any orientation   *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.chessboard;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.Point;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.GridLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        buildUI();
    }

    // Detects and rebuilds the UI on change.
    // Changes were made to AndroidManifest to
    // facilitate the passing of the change
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        buildUI();
    }

    public void buildUI() {
        // Very similar code layout to the 3x3 Assignment earlier.
        final int ROWS = 8, COLS = 8;
        int squareSize;
        Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);

        GridLayout gridLayout = new GridLayout(this);
        gridLayout.setRowCount(ROWS);
        gridLayout.setColumnCount(COLS);

        // Wrap GridLayout in a RelativeLayout for centering
        // Mainly for the horizontal layout
        RelativeLayout relativeLayout = new RelativeLayout(this);
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.WRAP_CONTENT,
                RelativeLayout.LayoutParams.WRAP_CONTENT
        );

        // Change checker size depending on orientation
        if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
            squareSize = size.x / COLS;
        } else {
            squareSize = (size.y - 80) / ROWS;
            layoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
        }

        gridLayout.setLayoutParams(layoutParams);

        // 8 x 8 TextView Array
        TextView textIcons[][] = new TextView[ROWS][COLS];

        String chessLayout[][] = {
                {"R", "K", "B", "Q", "K", "B", "K", "R",},
                {"P", "P", "P", "P", "P", "P", "P", "P",},
                {" ", " ", " ", " ", " ", " ", " ", " ",},
                {" ", " ", " ", " ", " ", " ", " ", " ",},
                {" ", " ", " ", " ", " ", " ", " ", " ",},
                {" ", " ", " ", " ", " ", " ", " ", " ",},
                {"P", "P", "P", "P", "P", "P", "P", "P",},
                {"R", "K", "B", "K", "Q", "B", "K", "R",}};

        // Loop through the 8x8 adding the correct String from the array above
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                textIcons[row][col] = new TextView(this);

                textIcons[row][col].setGravity(Gravity.CENTER);
                textIcons[row][col].setText(chessLayout[row][col]);
                textIcons[row][col].setTextColor(Color.BLACK);
                textIcons[row][col].setTextSize(32);
                textIcons[row][col].setTypeface(null, Typeface.BOLD);

                // Alternating colors for the spaces
                if ((row + col) % 2 == 0) {
                    if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
                        textIcons[row][col].setBackgroundColor(Color.BLACK);
                        // Add some pizzaz to the text
                        textIcons[row][col].setTextColor(Color.WHITE);
                    } else {
                        textIcons[row][col].setBackgroundColor(Color.GREEN);
                    }
                }
                // After all that is done, add to the gridlayout
                gridLayout.addView(textIcons[row][col], squareSize, squareSize);
            }
        }
        // Add gridLayout to relative, and set the content
        relativeLayout.addView(gridLayout);
        setContentView(relativeLayout);
    }
}