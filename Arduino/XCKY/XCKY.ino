#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>;

#define FIREBASE_HOST "myfarmapp-ac116-default-rtdb.firebaseio.com"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "pdWTG1xIJqeB3faEzLqoF5M2hjH0LdSTOAgkYD1p"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"                                //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"                                      //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
String message, str1, str2 ;
int water= 10;


int sensorPin = D1; // Connectez la broche de sortie analogique du capteur à la broche A0 de l'Arduino

void setup() {
  
   //init des données de base
  Serial.begin(115200);
  
// connection du esp8266 au reseau wifi assigné
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
    Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
   //Connexion à la base de données
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //initiation des données dans la base de données
   Firebase.setString("message","");
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Lire la valeur de la broche analogique
  float level = (sensorValue / 1023.0) * 100.0; // Convertir la valeur en pourcentage de niveau d'eau
  Serial.print("Niveau d'eau: ");
  Serial.print(level);
  Serial.println("%");
  if( level==100.00){

    water = water - 5;
    str1= "Hello il reste";
    str2= "litre d'eau dans le reservoir";
    message = str1 + water +str2 ;
    Firebase.setString("message", message);
    Serial.println(message);
    }
   else if(level == 0.00){  
    message = "not thing is happen hier"; 

    // envoie du message à la base de données
    Firebase.setString("message", message);
        Serial.println(message);

}
  delay(1000); // Attendre une seconde avant de lire à nouveau la valeur
}
