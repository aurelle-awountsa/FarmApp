package com.example.farmapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import com.pusher.pushnotifications.PushNotifications;


public class MenuActivity extends AppCompatActivity {
    private ImageView retour;
    private Button water;
    private  Button food;
    private Button light;
    private Button hygrometry;
    private Button intruder;
    private Button camera;



    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
        PushNotifications.start(getApplicationContext(), "e09d957f-406d-4c38-8f7b-d046fc9a7089");
        PushNotifications.addDeviceInterest("hello");

        this.water = (Button) findViewById(R.id.water) ;
        water.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  eauActivity = new Intent(getApplicationContext(), WaterActivity .class);
                startActivity(eauActivity);
                finish();
            }
        });
        this.camera = (Button) findViewById(R.id.camera) ;
        camera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  cameraActivity = new Intent(getApplicationContext(),  CameraActivity.class);
                startActivity(cameraActivity);
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
/*
        this.light = (Button) findViewById(R.id.light) ;
        light.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  lightActivity = new Intent(getApplicationContext(), LightActivity.class);
                startActivity(lightActivity);
                finish();
            }
        });*/

        this.hygrometry = (Button) findViewById(R.id.hygro) ;
        hygrometry.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  hygrometryActivity = new Intent(getApplicationContext(), Hygrometry.class);
                startActivity(hygrometryActivity);
                finish();
            }
        });
      /*  this.intruder = (Button) findViewById(R.id.intruder) ;
        intruder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent  intruderActivity = new Intent(getApplicationContext(), IntruderActivity.class);
                startActivity(intruderActivity);
                finish();
            }
        });*/


        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel("My notification", "My notification",importance);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }


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