package com.example.farmapp;

import static com.example.farmapp.R.id.on;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class WaterActivity extends AppCompatActivity {
    private ImageView retour;
    Button on;
    Button off;
    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_water);

        on = (Button) findViewById(R.id.on);
        off = (Button) findViewById(R.id.off);
        on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("LED_STATUS");

                myRef.setValue(1);

            }
        });

        off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("LED_STATUS");

                myRef.setValue(0);

            }
        });


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