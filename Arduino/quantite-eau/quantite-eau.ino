#include "ESP8266WiFi.h"
#include <FirebaseArduino.h>


#define FIREBASE_HOST "XXXXX"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "XXXXX"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "XXXXX"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "XXXXX"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266

//déclaration des broches 
const int TRIGGER = D0; 
const int ECHO = D1; 

long duration;
int distance_cm;
float profondeur = 19; // profonfeur du recipient en cm
//Constantes pour le timeout 
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000; //Vitesse du son dans l'air en mm/us 


void setup() {
  
  Serial.begin(115200);
  // connection du esp8266 au reseau wifi assigné  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("distance", 0);
  Firebase.setString("message", " ");

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}
void loop() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  
  //envoie une impulsion HIGH de 10 us sur broche trigger 
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  
  //Mesure le temps entre l'envoi de l'impulsion et son echo
  duration = pulseIn(ECHO, HIGH);
  distance_cm = duration /59; //  calcul la distance a partir du temps mesuré 
  double niveau = profondeur - distance_cm; // niveau d'eau dans le récipient 
  
  if(niveau > 0){
    long pourcentage = (niveau / profondeur)*100 ; //quantité d'eau en pourcentage
      Serial.println("pourcentage");
      Serial.print(pourcentage);
      Serial.print(" %"); 
      Firebase.setInt("distance",pourcentage);
      Firebase.setString("message","Il reste " + String(pourcentage)+ " % d'eau d'eau dans le réservoire"); ;
      delay(1000);

    }
    else{
      Serial.println("pourcentage ");
      Serial.print(0);
      Firebase.setInt("distance",0);

    }
    

  Serial.println("distance ");
  Serial.print(distance_cm );
  Serial.print("cm de ");
  delay(1000);

}
