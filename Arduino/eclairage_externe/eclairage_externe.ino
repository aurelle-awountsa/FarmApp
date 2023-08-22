#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "XXXXX"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "XXXXX"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "XXXXX"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "XXXXX"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
#define LEDPIN D8
 

void setup() {
Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  
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
  
  Firebase.setInt("LED_STATUS", 0);

}

int x = 0; //recupere le statut de la led dans la db

void loop() {
  
  x = Firebase.getInt("LED_STATUS");

  digitalWrite(LEDPIN, LOW);
  
  // activation de la led
  
  if (x == 1) {
      Serial.println("LED ON");
      digitalWrite(LEDPIN, HIGH);
      return;
      delay(20000);
      digitalWrite(LEDPIN, LOW);
      Serial.println("LED OFF");
      Firebase.setInt("LED_STATUS", 0);

  }


}
