#include <Wire.h>
#include <TFLI2C.h>
#include <Servo.h>

TFLI2C tflI2C; 
Servo myservo;
int16_t distance;
int16_t adresse = TFL_DEF_ADR;
int lunaPins[] = {3, 5};
int led = 7;       // la led s'allumera en cas de seuil de présence franchit
int buzzer = 9;    // Le buzzer permettra d'émmetre un signal sonore répulsif
int timer = 50;    // retard avant de basculer d'un module à l'autre
int maxPins = 2;   // nombre maximal de pins disponibles comme entrée de tension pour les TF-Lunas


void setup() {
  
  //init des données de base
  Serial.begin(115200);
  Wire.begin();
  myservo.attach(2);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);  
  //definir le mode des pins utilisées pour les différents capteurs luna  
  
   for(int currentPin = 0; currentPin < maxPins ; currentPin++){
    pinMode(lunaPins[currentPin], OUTPUT);
   }
}
void loop(){
     int position;
     for(int currentPin = 0; currentPin < maxPins ; currentPin++){
    
      digitalWrite(lunaPins[currentPin], HIGH);
      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW); 
      
      for (position = 0; position <= 180; position += 5) {  // va de 0 degrés à 180 degré avec un 5° d'intervalle
        if(tflI2C.getData(distance, adresse)){
            Serial.println(String(distance)+" cm  ");
            delay(150);                       // attend 150ms entre chaque détection
            
            //active le buzzer et la led lorsqu'il y a une présence
            if(distance <= 200 && distance != 0){
              digitalWrite(led, HIGH);
              digitalWrite(buzzer, HIGH);
              tone(buzzer, 6000, 600); 
            }
        }
      }
        myservo.write(position);          // commande le servo d'aller à la position dans la variable 'position'
        delay(150);                       // attend 150ms avant la prochaine position du servo
      
      for (position = 180; position >= 5; position -= 10) { // va de 0 degrés à 180 degré avec un 5° d'intervalle
   
        if(tflI2C.getData(distance, adresse)){
            Serial.println(String(distance)+" cm  ");
            delay(150);                       // attend 150ms entre chaque détection 

            //active le buzzer et la led lorsqu'il y a une présence
             if(distance <= 200 && distance != 0){
              digitalWrite(led, HIGH);
              digitalWrite(buzzer, HIGH);
              tone(buzzer, 6000, 600); 
            }
        }
        myservo.write(position);              // commande le servo d'aller à la position dans la variable 'position'
        delay(150);                       // attend 150ms avant la prochaine position du servo
      }

      delay(timer);                    //Attend pendant 'timer' avant de passer au prochain capteur 
     digitalWrite(lunaPins[currentPin], LOW);  // désactive la pin du capteur luna où est transmis le signal afin qu'un autre capteur prenne le relai

      
    }
        
  }
