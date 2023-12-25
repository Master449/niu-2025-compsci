/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 5                  Fall 2023    *
 *                                                                      *
 * App Name: stalker                                                    *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 11/03/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: 3x3 Grid of icons; assignment is testing persistence        *
 *                                                                      *
 *   If you're curious what a lot of this means, the S.T.A.L.K.E.R.     *
 *   series is a first-person-shooter survival horror video game.       *
 *                                                                      *
 *   Takes place in alternate universe Chernobyl, and many factions     *
 *   fight over stuff and artifacts they find in the "Exclusion Zone"   *
 *                                                                      *
 ************************************************************************/
package edu.niu.android.stalker;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.ImageButton;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
        buildUI();
    }

    public void buildUI() {
        final int ROWS = 3;
        final int COLS = 3;

        // Java class Factions to create the 9 items needed for the assignment
        // These constructors were way too long with the information, so I
        // put that into Strings.xml and pulled it from there.
        Faction loners = new Faction("Loners", getString(R.string.lonDesc), R.mipmap.loners_foreground);
        Faction monolith = new Faction("Monolith", getString(R.string.monDesc), R.mipmap.monolith_foreground);
        Faction military = new Faction("Military", getString(R.string.milDesc), R.mipmap.military_foreground);
        Faction mercs = new Faction("Mercs", getString(R.string.merDesc), R.mipmap.mercs_foreground);
        Faction freedom = new Faction("Freedom", getString(R.string.freDesc), R.mipmap.freedom_foreground);
        Faction ecologists = new Faction("Ecologists", getString(R.string.ecoDesc), R.mipmap.ecologists_foreground);
        Faction duty = new Faction("Duty", getString(R.string.dutDesc), R.mipmap.duty_foreground);
        Faction clearsky = new Faction("Clear Sky", getString(R.string.cleDesc), R.mipmap.clearsky_foreground);
        Faction bandits = new Faction("Bandits", getString(R.string.banDesc), R.mipmap.bandits_foreground);

        // Put the objects into an array, to iterate over later on
        Faction[][] factionsArray = {
                {loners, monolith, military},
                {mercs, freedom, ecologists},
                {duty, clearsky, bandits}
        };

        // Most of this was taken from TicTacToe we did in class
        // and then refitted for the needs of this assignment
        Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);
        int w = size.x / 3;

        GridLayout gridLayout = new GridLayout(this);

        // This is to let the title label to take up 3 columns
        GridLayout.LayoutParams textLayout = new GridLayout.LayoutParams();
        textLayout.columnSpec = GridLayout.spec(0,3);

        gridLayout.setRowCount(ROWS);
        gridLayout.setColumnCount(COLS);

        ImageButton[][] buttons = new ImageButton[3][3];

        // Add Label at top
        TextView topLabel = new TextView(this);
        gridLayout.addView(topLabel);

        // Change the label attributes
        topLabel.setLayoutParams(textLayout);
        topLabel.setTextSize(22);
        topLabel.setTextColor(Color.BLACK);
        topLabel.setText("Choose a Faction to learn more.");

        // Iterate over our 3x3
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                // Create new button and add the appropriate faction image
                buttons[row][col] = new ImageButton(this);
                buttons[row][col].setBackground(getResources().getDrawable((factionsArray[row][col].getFactionImageID())));

                // Inner class needs final for some reason
                final int finalRow = row;
                final int finalCol = col;

                // Add OnClickListener for each button
                buttons[row][col].setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        // Create a new intent to pass to activity_info
                        Intent intent = new Intent(MainActivity.this, InfoActivity.class);

                        // Parameters needed for proper display
                        // Includes image, name and info
                        intent.putExtra("image", factionsArray[finalRow][finalCol].getFactionImageID());
                        intent.putExtra("title", factionsArray[finalRow][finalCol].getFactionName());
                        intent.putExtra("info", factionsArray[finalRow][finalCol].getFactionInformation());

                        // Start the activity, while passing the intent we created.
                        startActivity(intent);
                    }
                });

                // Adds each row of buttons
                gridLayout.addView(buttons[row][col], w, w);
            }
        }

        // Set the content view
        setContentView(gridLayout);
    }
}