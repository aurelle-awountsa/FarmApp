package com.example.farmapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class WaterActivity extends AppCompatActivity {
    private ImageView retour;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_water);

        this.retour = (ImageView) findViewById(R.id.rtr1);
        retour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent returnActivity = new Intent(getApplicationContext(), MenuActivity.class);
                startActivity(returnActivity);
                finish();
            }

        });
    }
}