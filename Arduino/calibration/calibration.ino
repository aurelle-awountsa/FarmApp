#include "HX711.h" 
#define DOUT  D7
#define CLK  D5
 
HX711 scale;
 
float calibration_factor = -549055  ; // -139055 valeur à ajuster selon la balance
 
void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, CLK);
  Serial.println("Retirer tout objet de la balance");
  Serial.println("Poser un objet avec une masse connue");
  Serial.println("Appuyer a,s,d,f pour augmenter le facteur de calibration  respectivement par 10,100,1000,10000");
  Serial.println("Appuyer z,x,c,v pour diminuer le facteur de calibration  respectivement par 10,100,1000,10000 ");
  Serial.println("Appuyer t pour tarer");
  scale.set_scale();
  scale.tare(); //mettre la balance à 0
 
  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
}
 
void loop() {
 
  scale.set_scale(calibration_factor); //Ajuster le facteur de calibrationfactor
 
  Serial.print("Lecture: ");
  Serial.print(scale.get_units(), 3);
  Serial.print(" kg");
  Serial.print(" facteur de calibration: ");
  Serial.print(calibration_factor);
  Serial.println();
  delay(1000);
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if(temp == 's')
      calibration_factor += 100;  
    else if(temp == 'x')
      calibration_factor -= 100;  
    else if(temp == 'd')
      calibration_factor += 1000;  
    else if(temp == 'c')
      calibration_factor -= 1000;
    else if(temp == 'f')
      calibration_factor += 10000;  
    else if(temp == 'v')
      calibration_factor -= 10000;  
    else if(temp == 't')
      scale.tare();  
  }
}
