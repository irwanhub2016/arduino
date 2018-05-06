#include <Wire.h>

const int pingPin = 12;
int inPin = 11;

long duration, cm;
int mark;

//lebih dari 3 meter = 190
//antara 1,5 sampai 2,5 = 80
//kurang dari 1,5 = 50   

void setup() {
  pinMode(pingPin, OUTPUT);
  pinMode(inPin, INPUT);
  Serial.begin(9600);
  }

void loop(){

mark = 0;

digitalWrite(pingPin, LOW);
delayMicroseconds(2);
digitalWrite(pingPin, HIGH);
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
duration = pulseIn(inPin, HIGH);

cm = microsecondsToCentimeters(duration);
Serial.println(cm);
delay(1000);
}


long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
