#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Données à modifier 
#define FIREBASE_HOST "LIEN VERS LA RTDB"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "CODE SECRET"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
#define trigPin D7
#define echoPin D8
long duration;
int distance;
int water = 100;
int jour = 5;
/* 100 => 5jouurs
    distance => x jours
    pour water = 100 distance = 0
    y = distance =10
    y = */
int x ;
String str1 = "la quantité d'eau restante correspond à ";
String str2 = " jours." ;
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
  Firebase.setInt("distance", 0);
  Firebase.setString("waterlevel", "");

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  /*
   * For Utlrasonic sensor distance measurement
   */
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, MEASURE_TIMEOUT);
  
  // Calculating the distance
  distance= duration / 2.0 * SOUND_SPEED;
  
  x =(distance * jour) / water;
  Serial.print(x);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance / 10.0, 2);
  Firebase.setInt("distance",distance);
  delay(1000);
  
  if(distance /10.0 < 60 && distance != 0){
    
    Serial.println(1);
    Firebase.setString( "presence",str1+ x +str2 );
  }
}
