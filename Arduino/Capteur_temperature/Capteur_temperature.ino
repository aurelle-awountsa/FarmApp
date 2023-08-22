#include <ESP8266WiFi.h>
#include <DHT.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "XXXXX"   // lien qui mène vers notre base de données
#define FIREBASE_AUTH "XXXXX"      // système d'authentification avec les jettons (jetton propre à la db)
#define WIFI_SSID "XXXXX"  //remplacer le nom par le nom du wifi auquel on veut connecter l'esp8266
#define WIFI_PASSWORD "XXXXX"         //remplacer le mot de passe par le mot de passe du wifi auquel on veut connecter l'esp8266
#define DHTTYPE DHT22 
#define DHTPIN D7   
#define FANPIN D6 
   

DHT dht(DHTPIN, DHTTYPE);
int temperature,  humidity, farhadey; //variable de température en Celsius, humidité et en température farhadey

void setup() {

 //init des données de base
  
  Serial.begin(115200);
  pinMode(DHTPIN, OUTPUT);
  pinMode(FANPIN, INPUT);

  Serial.println("DHT OK");
  dht.begin();
// connexion de l'esp8266 au reseau wifi assigné

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

  digitalWrite(FANPIN , LOW);
  //recupere les données envoyées par le capteur
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  farhadey = dht.readTemperature(true);
  
//envoie des données du capteur dans la base de données
  Firebase.setInt("temperature", temperature);
  Firebase.setInt("humidity", humidity);
  Firebase.setInt("farhadey", farhadey);

  
  Serial.print("Température  ");
  Serial.print(temperature);
  Serial.println("°C, "); 
  Serial.print("Humidité  ");
  Serial.print(humidity);
  Serial.println("%, ");
  Serial.print("Farhadey  ");
  Serial.print(farhadey);
  Serial.println("°F, ");
  
  //traiter le seuil de température
  while( temperature >= 30){
      digitalWrite(D6, HIGH);
       Serial.println("Fan ON");

  }
  
}
