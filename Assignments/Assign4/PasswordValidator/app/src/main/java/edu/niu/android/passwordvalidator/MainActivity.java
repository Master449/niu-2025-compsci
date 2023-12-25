/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 4                  Fall 2023    *
 *                                                                      *
 * App Name: Password Validator                                         *
 *                                                                      *
 * Class Name: MainActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 10/20/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Main View activity                                          *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.passwordvalidator;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Create object from the model
        passwordvalidator pass_valid = new passwordvalidator();

        // creating the layout
        LinearLayout layout = new LinearLayout(this);

        layout.setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.MATCH_PARENT)
        );

        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setGravity(1);

        LinearLayout.LayoutParams layoutorder = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT
        );

        layoutorder.setMargins(0, 16, 0, 16);

        // create the object for assignment
        EditText inputText = new EditText(this);
        TextView validText = new TextView(this);

        // Give the edit text some default stuff
        inputText.setLayoutParams(layoutorder);
        inputText.setText("Abc123!");
        inputText.setTextColor(Color.BLACK);
        inputText.setTextSize(20);

        validText.setLayoutParams(layoutorder);
        validText.setText("STRONG OR WEAK?");
        validText.setTextColor(Color.BLACK);
        validText.setTextSize(36);
        validText.setPadding(0, 300, 0, 100);


        // Go to screen
        layout.addView(validText);
        layout.addView(inputText);

        // This is a listener for the input text
        inputText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2)
            {

            }

            // This will run everytime the text box is changed
            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2)
            {
                if (pass_valid.check_password(inputText.getText().toString()))
                    {
                        validText.setText("STRONG");
                        validText.setTextColor(Color.GREEN);
                    }
                else
                    {
                        validText.setText("WEAK");
                        validText.setTextColor(Color.RED);
                    }

            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });



        setContentView(layout);

    }
}