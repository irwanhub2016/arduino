#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DEBUG true 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int trigPin1 = 7; //Trig – green Jumper
int echoPin1 = 6; //Echo – yellow Jumper

int trigPin2 = 9; //Trig – green Jumper
int echoPin2 = 8; //Echo – yellow Jumper

int torenBesar = 180;
int torenSedang = 150;  

long duration1, cm1, duration2, cm2, tinggiTB, tinggiTS;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Mulai Monitor");
  lcd.setCursor(7,1);
  lcd.print("Air");
  delay(1000);

  lcd.clear();  
  delay(3000);
  
  }

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
lcd.clear();
delay(1000);
digitalWrite(trigPin1, LOW);
delayMicroseconds(5);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
pinMode(echoPin1, INPUT);
duration1 = pulseIn(echoPin1, HIGH);
cm1 = (duration1/2) / 29.1;
tinggiTB = torenBesar - cm1;

digitalWrite(trigPin2, LOW);
delayMicroseconds(5);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
pinMode(echoPin2, INPUT);
duration2 = pulseIn(echoPin2, HIGH);
cm2 = (duration2/2) / 29.1;
tinggiTS = torenSedang - cm2;

Serial.print("Tingggi Toren Besar : ");
Serial.print(tinggiTB);
Serial.print("cm");
Serial.println();
Serial.print("Tingggi Toren Sedang : ");
Serial.print(tinggiTS);
Serial.print("cm");
Serial.println();
Serial.print("===============================================");
Serial.println();
lcd.setCursor(0,0);
lcd.print("Toren 2");
lcd.setCursor(9,0);
lcd.print(tinggiTS);
lcd.setCursor(0,1);
lcd.print("Toren 1");
lcd.setCursor(9,1);
lcd.print(tinggiTB);
delay(1000);
lcd.clear();
delay(1000);
}
