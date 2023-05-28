int photo = A0;

void setup() {
Serial.begin(9600);
pinMode(photo, INPUT);
}

void loop() {
int lecture = analogRead(photo);
Serial.println(lecture);
delay(1000);
}
