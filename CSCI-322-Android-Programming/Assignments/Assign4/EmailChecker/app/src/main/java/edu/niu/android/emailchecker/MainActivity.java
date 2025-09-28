/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 4                  Fall 2023    *
 *                                                                      *
 * App Name: Email Checker                                              *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 10/20/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Main View Activity                                          *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.emailchecker;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Create object from our model
        EmailValidation emailValid = new EmailValidation();

        // Create the layout
        LinearLayout layout = new LinearLayout(this);

        // Setup some rules so they don't go everywhere
        // I learned most of this from the docs
        // https://developer.android.com/reference/android/widget/LinearLayout
        layout.setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.MATCH_PARENT
        ));

        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setGravity(1);

        LinearLayout.LayoutParams layoutOrder = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT
        );

        layoutOrder.setMargins(0, 16, 0, 16);

        // Create the objects needed for this assignment
        EditText inputTextBox = new EditText(this);
        Button validationButton = new Button(this);
        TextView validTextView = new TextView(this);

        // Give the edit text some default stuff
        inputTextBox.setLayoutParams(layoutOrder);
        inputTextBox.setText("johnsmith@mail.com");
        inputTextBox.setTextColor(Color.BLACK);
        inputTextBox.setTextSize(20);

        // Give the button some default stuff
        validationButton.setLayoutParams(layoutOrder);
        validationButton.setText("CHECK");
        validationButton.setTextColor(Color.BLACK);
        validationButton.setTextSize(20);
        validationButton.setWidth(800);

        // Give the text some default stuff
        validTextView.setLayoutParams(layoutOrder);
        validTextView.setText("VALID?");
        validTextView.setTextColor(Color.BLACK);
        validTextView.setTextSize(36);
        validTextView.setPadding(0, 300, 0, 100);

        // Slap em on the screen
        layout.addView(validTextView);
        layout.addView(inputTextBox);
        layout.addView(validationButton);

        // Add the button event listener
        // https://developer.android.com/reference/android/widget/Button
        validationButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Set the email and cast to string
                // since a char array is returned
                emailValid.setEmail(inputTextBox.getText().toString());

                // EmailValidation class checks the email
                if (emailValid.checkValidity()) {
                    validTextView.setText("VALID");
                    validTextView.setTextColor(Color.GREEN);
                    setContentView(layout);
                } else {
                    validTextView.setText("INVALID");
                    validTextView.setTextColor(Color.RED);
                    setContentView(layout);
                }
            }
        });

        // Set the new view
        setContentView(layout);
    }
}