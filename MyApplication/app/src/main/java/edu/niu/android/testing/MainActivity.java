package edu.niu.android.testing;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
// Import the logging functionality
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.w("MainActivity", "Inside onCreate");
        setContentView(R.layout.activity_main);
    }
}