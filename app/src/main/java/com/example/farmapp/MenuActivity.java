package com.example.farmapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MenuActivity extends AppCompatActivity {
    private ImageView retour;
    private Button water;
    private  Button food;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        this.water = (Button) findViewById(R.id.water) ;
        water.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  eauActivity = new Intent(getApplicationContext(), WaterActivity.class);
                startActivity(eauActivity);
                finish();
            }
        });

        this.food = (Button) findViewById(R.id.food) ;
        food.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  foodActivity = new Intent(getApplicationContext(), FoodActivity.class);
                startActivity(foodActivity);
                finish();
            }
        });

        this.retour = (ImageView) findViewById(R.id.rtn);
        retour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent retActivity = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(retActivity);
                finish();
            }
        });
    }
}