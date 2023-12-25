/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 5                  Fall 2023    *
 *                                                                      *
 * App Name: stalker                                                    *
 *                                                                      *
 * Class Name: InfoActivity.java                                        *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 11/03/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: This class is used by the activity "activity_info" with     *
 *          and image, title, and information passed to it, to be       *
 *          displayed. This is a reusable view.                         *
 *                                                                      *
 ************************************************************************/
package edu.niu.android.stalker;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class InfoActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_info);

        // Retrieve the data passed in the Intent
        // This includes image, faction title, and info blurb
        Intent intent = getIntent();
        int factionImage = intent.getIntExtra("image", 0);
        String factionTitle = intent.getStringExtra("title");
        String factionInfo = intent.getStringExtra("info");

        // Set the image to a drawable so it get be set on the image
        Drawable realImage = InfoActivity.this.getResources().getDrawable(factionImage);

        // Get the elements IDs
        ImageView imageView = findViewById(R.id.imageView);
        TextView title = findViewById(R.id.titleView);
        TextView infoTextView = findViewById(R.id.infoText);

        // Update the elements with the passed in information
        imageView.setImageDrawable(realImage);
        title.setText(factionTitle);
        infoTextView.setText(factionInfo);
    }
}
