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
 * Purpose: Use GestureListeners to change Tap behavior.                *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.tapit;

import android.graphics.Color;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private TextView tapView;
    private TextView countView;
    private GestureDetector gestureDetector;
    private int tapCount = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Get the textview IDs
        tapView = findViewById(R.id.tapView);
        countView = findViewById(R.id.countView);

        // Set initial background color for tapView
        tapView.setBackgroundColor(Color.RED);

        // Setup the gesture and tap handlers
        TapHandler detector = new TapHandler();
        gestureDetector = new GestureDetector(this, detector);

        tapView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                gestureDetector.onTouchEvent(event);
                return true;
            }
        });
    }

    private class TapHandler extends GestureDetector.SimpleOnGestureListener {
        @Override
        public boolean onSingleTapConfirmed(MotionEvent e) {
            // On single tap, change background to red and + 1
            tapView.setBackgroundColor(Color.RED);
            tapCount++;
            countView.setText(String.valueOf(tapCount));
            return true;
        }

        @Override
        public boolean onDoubleTap(MotionEvent e) {
            // On double tap, change background to blue and + 2
            tapView.setBackgroundColor(Color.BLUE);
            tapCount += 2;
            countView.setText(String.valueOf(tapCount));
            return true;
        }
    }
}
