package com.example.farmapp;

import static com.example.farmapp.R.id.message;
//import static com.example.farmapp.R.id.on;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Objects;

public class WaterActivity extends AppCompatActivity {
    ImageView retour;
   // Button on;
  //  Button off;
    TextView eau;
    DatabaseReference myRef;
    String status;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_water);

       // on = (Button) findViewById(R.id.on);
       // off = (Button) findViewById(R.id.off);
        eau = (TextView) findViewById(R.id.message);

        myRef = FirebaseDatabase.getInstance().getReference();


        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
// Remplacer la valeur initiale par celle provenant de firebase

                status = dataSnapshot.child("message").getValue().toString();
                eau.setText(status);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });



/* Envoyer les instructions d'allumage et d'extextion à firebase

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
        });*/


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