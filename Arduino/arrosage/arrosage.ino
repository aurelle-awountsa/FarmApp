
int pin8 = 8;
int capteuranalogique = A1;
int capteurnumerique = A0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int maxi = 1023; // pour avoir toute la fenetre du traceur série 
int mini = 0; // pour avoir toute la fenetre du traceur serie
void setup() {
pinMode(pin8, OUTPUT); // broche d'alimentation du relais
pinMode(4, OUTPUT); // broche d'alimentation de la sonde
Serial.begin(9600); // SI ON VEUT VOIR LE TRACEUR SERIE
digitalWrite(pin8, LOW);
digitalWrite(4, LOW); // met la sonde hors tension - protection oxydation
}
void loop() {
digitalWrite(4, LOW); // remet la sonde hors tension pendant temporisation pour protection oxydation  
for(int temporisation = 0; temporisation <= 8640 ; temporisation = temporisation+1) // mettre 8640 !
{
  delay(10000); // cette boucle for protège la sonde car ne fait qu'une mesure par 24h
}
digitalWrite(4, HIGH); // met la sonde sous tension
delay(1000);
sensorValue1 = analogRead(capteuranalogique); // mesure humidité
sensorValue2 = analogRead(capteurnumerique);
Serial.print(maxi);
Serial.print(" ; ");
Serial.print(mini);
Serial.print("  ;  VALEUR ANALOGIQUE = ");
Serial.print(sensorValue1);
Serial.print("  ; VALEUR NUMERIQUE = " );
Serial.println(sensorValue2);
// si sensorValue1 est supérieur au seuil sec
  if (sensorValue1 > 900) {
  Serial.println(" TROP SEC - ACTIVATION ARROSAGE ");
  for(int arrosage = 1 ; arrosage <= 10 ; arrosage = arrosage+1) // cycle maxi de 10 tests + arrosage
     {
     sensorValue1 = analogRead(capteuranalogique); 
     if (sensorValue1 > 900) {
        Serial.print(arrosage);
        Serial.print(" arrosage ");
        Serial.print(" ; ");
        Serial.println(sensorValue1);
        digitalWrite(pin8, HIGH); 
        delay(2000); // durée fixe activation pompe
        digitalWrite(pin8, LOW); 
        delay(5000); // pause pompe pour laisser a l'eau le tps de pénétrer la terre  
        }
      else
      {
      Serial.println(" FIN CYCLE ARROSAGE ");    
      }
     }
  }
}
