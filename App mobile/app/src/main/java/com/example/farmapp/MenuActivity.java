package com.example.farmapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;


public class MenuActivity extends AppCompatActivity {
    private ImageView retour;
    private Button water;
    private  Button food;
    private Button light;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        this.water = (Button) findViewById(R.id.water) ;
        water.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  eauActivity = new Intent(getApplicationContext(), WaterActivity .class);
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

        this.light = (Button) findViewById(R.id.light) ;


        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel("My notification", "My notification",importance);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }

        light.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                NotificationCompat.Builder builder = new NotificationCompat.Builder(MenuActivity.this,"My notification")
                        .setSmallIcon(R.drawable.food)
                        .setContentTitle("Test")
                        .setContentText("Ici s'affichera le cotenu de ma notification")
                        .setPriority(NotificationCompat.PRIORITY_DEFAULT);


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