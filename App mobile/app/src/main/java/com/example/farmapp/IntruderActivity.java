package com.example.farmapp;

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

public class IntruderActivity extends AppCompatActivity {
    private ImageView retour;
    TextView intruder;
    DatabaseReference myRefIntruder;
    String statusI;
    Button on;
    Button off;
    DatabaseReference myRef;

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intruder);
        off = (Button) findViewById(R.id.off);
        on = (Button) findViewById(R.id.on);
        myRef = FirebaseDatabase.getInstance().getReference();
        intruder = (TextView) findViewById(R.id.intrus);



        on.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("BUZZER");

                myRef.setValue(1);

            }
        });

        off.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                FirebaseDatabase database = FirebaseDatabase.getInstance();
                DatabaseReference myRef = database.getReference("BUZZER");

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

        myRefIntruder = FirebaseDatabase.getInstance().getReference();


        myRefIntruder.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
// Remplacer la valeur initiale par celle provenant de firebase

                statusI = dataSnapshot.child("presence").getValue().toString();
                intruder.setText(statusI);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}