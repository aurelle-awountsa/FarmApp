package com.example.farmapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Hygrometry extends AppCompatActivity {
    ImageView retour;
    TextView temperature;
    TextView humidity;
    TextView farhadey;
    DatabaseReference dref;
    String status1,status2, status3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hygrometry);
        // on recupere les texviews du fichier xml en utilisant leur id
        //dref fait reference à la base de données

        temperature = (TextView) findViewById(R.id.temp);
        humidity = (TextView) findViewById(R.id.hum);
        farhadey = (TextView) findViewById(R.id.far);
        dref = FirebaseDatabase.getInstance().getReference();

        /*ajoute un ValueEventListener à un objet DatabaseReference (représenté par dref), qui écoute les modifications
         apportées aux données à cet emplacement dans la base de données.
         Tools => Firebase => realtime database => 2 */
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                status1 = snapshot.child("temperature").getValue().toString();
                temperature.setText(status1);
                status2 = snapshot.child("humidity").getValue().toString();
                humidity.setText(status2);
                status3 = snapshot.child("farhadey").getValue().toString();
                farhadey.setText(status3);

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

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