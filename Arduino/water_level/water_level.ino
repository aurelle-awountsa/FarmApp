#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Données à modifier 
#define FIREBASE_HOST "myfarmapp-ac116-default-rtdb.firebaseio.com"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "pdWTG1xIJqeB3faEzLqoF5M2hjH0LdSTOAgkYD1p"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
#define trigPin D7
#define echoPin D8
long duration;
int distance;
int hauteur_recipient = 400; //en cm
int quantite = 40; //litre
/* 100m => 100L
    distance => x l
    jours = x / quantité d'eau journalière*/
int x ; //nombre de litre restant
String str1 = "la quantité d'eau restante correspond à ";
String str2 = " Litres." ;
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = 8m à 340m/s
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  
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
  Firebase.setInt("distance_eau", 0);
  Firebase.setString("message", "");

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /*
   * Pour la mesure du capteur de distance à ultrason
   */
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // lire echoPin, renvoie le temps de parcours de l'onde sonore en microsecondes

  duration = pulseIn(echoPin, HIGH, MEASURE_TIMEOUT);
  
  // Calcul de la distance
  distance= duration / 2.0 * SOUND_SPEED;
  
  x =quantite - ((distance * quantite) / hauteur_recipient);
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance / 10.0, 2);
  Serial.println(x);
  Firebase.setInt("distance_eau",distance);
  delay(1000);
  Firebase.setString( "message",str1+ x +str2 );
  
}
