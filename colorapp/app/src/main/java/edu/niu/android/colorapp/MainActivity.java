/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 3                  Fall 2023    *
 *                                                                      *
 * App Name: ConstraintLayout Exercise                                  *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 09/29/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Creating an app that lets the user create a color           *
 *          using rgb values in some fields                             *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.colorapp;

import android.graphics.Color;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.TextView;
import java.text.NumberFormat;

public class MainActivity extends AppCompatActivity {

    private ColorPicker colorPick;
    private EditText redEditText;
    private EditText greenEditText;
    private EditText blueEditText;
    private TextView labelText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        colorPick = new ColorPicker(255, 255, 255);
        setContentView(R.layout.activity_main);

        // Input Text Fields
        redEditText = (EditText) findViewById(R.id.editTextNumberRed);
        greenEditText = (EditText) findViewById(R.id.editTextNumberGreen);
        blueEditText = (EditText) findViewById(R.id.editTextNumberBlue);

        // Label TextView
        labelText = (TextView) findViewById(R.id.largeLabel);

        TextChangeHandler tch = new TextChangeHandler();

        // Add listeners to Text edit views
        redEditText.addTextChangedListener(tch);
        greenEditText.addTextChangedListener(tch);
        blueEditText.addTextChangedListener(tch);

    }

    private void ChangeColor() {
        String redString = redEditText.getText().toString();
        String greenString = greenEditText.getText().toString();
        String blueString = blueEditText.getText().toString();

        int realRed = 0;
        int realGreen = 0;
        int realBlue = 0;

        // Validate Red
        if (redString.isEmpty() || Integer.parseInt(redString) < 0) {
            // If empty or less than 0, set it to 0
            realRed = 0;
            redEditText.setText("0");
        } else if ( Integer.parseInt(redString) > 255 ) {
            // if greater than 255, set it to 255
            realRed = 255;
            redEditText.setText("255");
        } else {
            realRed = Integer.parseInt(redString);
        }

        // Validate Green
        if (greenString.isEmpty() || Integer.parseInt(greenString) < 0) {
            // If empty or less than 0, set it to 0
            realGreen = 0;
            greenEditText.setText("0");
        } else if (Integer.parseInt(greenString) > 255) {
            // if greater than 255, set it to 255
            realGreen = 255;
            greenEditText.setText("255");
        } else {
            realGreen = Integer.parseInt(greenString);
        }

        // Validate Blue
        if (blueString.isEmpty() || Integer.parseInt(blueString) < 0) {
            // If empty or less than 0, set it to 0
            realBlue = 0;
            blueEditText.setText("0");
        } else if ( Integer.parseInt(blueString) > 255) {
            // if greater than 255, set it to 255
            realBlue = 255;
            blueEditText.setText("255");
        } else {
            realBlue = Integer.parseInt(blueString);
        }

        // Send the colors off to the ColorPicker class
        this.colorPick.setColors(realRed, realGreen, realBlue);

        // Update the label text color with the Colors package
        labelText.setBackgroundColor(Color.rgb(colorPick.getRed(), colorPick.getGreen(), colorPick.getBlue()));
    }

    // Borrowed this from TipCalculator
    private class TextChangeHandler implements TextWatcher {
        public void afterTextChanged(Editable e) {
            ChangeColor();
        }

        public void beforeTextChanged(CharSequence s, int start, int count, int after) {
        }

        public void onTextChanged(CharSequence s, int start, int before, int after) {
        }
    }
}