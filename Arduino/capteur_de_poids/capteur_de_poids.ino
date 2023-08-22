#include "HX711.h"
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "XXXXX"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "XXXXX"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266

Servo myservo;
HX711 scale;

float weight;
float calibration_factor = -549055; 
 
void setup() 
{
  Serial.begin(115200);
  scale.begin(D7, D5);
  myservo.attach(D4);
  scale.set_scale();
  scale.tare(); 
  long zero_factor = scale.read_average();
  
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
  
   Firebase.setString("foodRemain", "");
}
 
void loop() 
{
  scale.set_scale(calibration_factor); //ajuster le facteur de calibration
 
  weight = scale.get_units(5); // moyenne de 5 mesure
  
  if(weight >= 0.5 ){
    float foodRemain, foodInit = 5; //ces variables sont respectivement la quantité de nourriture restante et la quantité initiale
    int foodGive = 0;   // le nombre de fois que le servo moteur s'activera pour remplir les mangeoires

      myservo.write(0);
      Serial.println("servo 0");
      delay(20000); // au bout de 2minutes, le poids de nourriture dans la mangeoire est de 2 kg
      myservo.write(180);
      Serial.println("servo 180");
      foodGive += 1;
      foodRemain = foodInit - (2-0.2) * foodGive;
      Firebase.setString("foodRemain", " la quantité de nouriture restante est de " + String(foodRemain) + " kg");

      return;
   }
     
  Serial.print("Poids: ");
  Serial.print(weight);
  Serial.println(" kg");
 
  delay(1000);
  Serial.println();
  
 
}
