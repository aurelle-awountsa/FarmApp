#include <ESP8266WiFi.h>
#include "DHT.h";
#include <FirebaseArduino.h>;

#define FIREBASE_HOST "myfarmapp-ac116-default-rtdb.firebaseio.com"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "pdWTG1xIJqeB3faEzLqoF5M2hjH0LdSTOAgkYD1p"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "tilly's Galaxy S22"  //remplacer le nom par le nom du wifi auqudel on veut connecter l'esp8266
#define WIFI_PASSWORD "oych2358"         //remplacer le mot de passe par le mot de passe du wifi auqudel on veut connecter l'esp8266
#define DHTTYPE DHT22 
#define DHTPIN D2    

DHT dht(DHTPIN, DHTTYPE);
int temp,  hum, far;

void setup() {

 //init des données de base
  
  Serial.begin(115200);
  pinMode(D1, OUTPUT);
  Serial.println("DHT TEST");
  dht.begin();
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
  
  Firebase.setInt("temperature", 0);
  Firebase.setInt("humidity", 0);
  Firebase.setInt("farhadey", 0);
}


int n = 0;
void loop() {

  // DHT 22

  //recupere les données envoyées par le capteur
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  far = dht.readTemperature(true);
  Serial.print("Température  ");
  Serial.print(temp);
  Serial.println("°C, "); 
  Serial.print("Humidité  ");
  Serial.print(hum);
  Serial.println("%, ");
  Serial.print("Farhadey  ");
  Serial.print(far);
  Serial.println("°F, ");
  delay(1000);
  
// envoie des données du capteur à la base de données

  Firebase.setInt("temperature", temp);
  Firebase.setInt("humidity", hum);
  Firebase.setInt("farhadey", far);
  
 
 
}
