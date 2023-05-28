package com.example.farmapp;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.core.app.NotificationCompat;

import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

public class MyFirebaseMessagingService extends FirebaseMessagingService {
    private static final String CANAL = "MyNotifCanal";

    @Override
    public void onMessageReceived(@NonNull RemoteMessage remoteMessage) {
        super.onMessageReceived(remoteMessage);
        String myMessage = remoteMessage.getNotification().getBody();
        Log.d("FirebaseMessage", "Vous venez de recevoir un nouveau message:" + myMessage);
        //action
        // diriger la notification vers une page
        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setClass(this, WaterActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, 0);

        //créer une notiifcation
        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this, CANAL);
        notificationBuilder.setContentTitle("Ma notf");
        notificationBuilder.setContentText(myMessage);

        // créer une action
        notificationBuilder.setContentIntent(pendingIntent);
        //icone
        notificationBuilder.setSmallIcon(R.drawable.cloche);

        //envoie de la notification
        NotificationManager notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
         if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
             String channelId = getString(R.string.notification_channel_id);
             String channelTitle = getString(R.string.notification_channel_title);
             String channelDescription = getString(R.string.notification_channel_desc);
             NotificationChannel channel = new NotificationChannel(channelId, channelTitle, NotificationManager.IMPORTANCE_DEFAULT);
             channel.setDescription(channelDescription);
             notificationManager.createNotificationChannel(channel);
             notificationBuilder.setChannelId(channelId);
         }
        notificationManager.notify(1, notificationBuilder.build());
    }
}
