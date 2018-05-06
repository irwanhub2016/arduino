#define echoPin 7 //Echo Pin
#define trigPin 6 //Trigger Pin
 
int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 0; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak
 
void setup() {
Serial.begin (9600); //inisialiasasi komunikasi serial
//deklarasi pin
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
