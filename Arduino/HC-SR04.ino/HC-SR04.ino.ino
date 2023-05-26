#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Données à modifier 
#define FIREBASE_HOST "myfarmapp-ac116-default-rtdb.firebaseio.com"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "pdWTG1xIJqeB3faEzLqoF5M2hjH0LdSTOAgkYD1p"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
#define trigPin D7
#define echoPin D8
#define led D3
long duration;
int distance;
String str1 = "Un intrus est proche et se trouve à ";
String str2 = " mm de la ferme";


const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Définir la broche de déclenchement comme une sortie
  pinMode(echoPin, INPUT); // Définir la broche echoPin comme une entrée.
  pinMode(led, OUTPUT);
  
  
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
  Firebase.setString("presence", "");

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /*
   * Pour la mesure de la distance par capteur ultrasonique
   */
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //Lire la broche echoPin, renvoie le temps de parcours de l'onde sonore en microsecondes
  duration = pulseIn(echoPin, HIGH, MEASURE_TIMEOUT);
  
  // Calcul de la distance
  distance= duration / 2.0 * SOUND_SPEED;
  
  
  // Imprimer la distance sur le moniteur série
  Serial.print("Distance: ");
  Serial.println(distance / 10.0, 2);// convertir en cm
  Firebase.setInt("distance",distance);
  delay(1000);
  
  if(distance /10.0 < 60 && distance != 0){
    digitalWrite(led, HIGH);
    Firebase.setString("presence",str1 + distance + str2); 
  }
  else{
    
    digitalWrite(led, LOW);
    Firebase.setString("presence","Il n'y a aucune présence par ici");
}
  
}
