package com.example.farmapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class CameraActivity extends AppCompatActivity {
    ImageView retour;
    Button camera1;
    Button camera2;

    DatabaseReference myRef;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);

        myRef = FirebaseDatabase.getInstance().getReference();
        this.retour = (ImageView) findViewById(R.id.rtr1);
        retour.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent returnActivity = new Intent(getApplicationContext(), MenuActivity.class);
                startActivity(returnActivity);
                finish();
            }

        });
        this.camera1 = (Button) findViewById(R.id.videoIn) ;
        camera1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent cameraActivity = new Intent(Intent.ACTION_VIEW, Uri.parse("http://192.168.XX.XX"));
                startActivity(cameraActivity);
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("LED_STATUS");
                myRef.setValue(1);
                finish();
            }
        });

        this.camera2 = (Button) findViewById(R.id.videoOut) ;
        camera2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent cameraActivity = new Intent(Intent.ACTION_VIEW, Uri.parse("http://192.168.XX.XX"));
                startActivity(cameraActivity);
                finish();
            }
        });
    }
}