//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int trigPin2 = 9; //Trig – green Jumper
int echoPin2 = 8; //Echo – yellow Jumper
long duration1, cm1, duration2, cm2, tinggiTB, tinggiTS;
  
int torenBesar = 180;
int torenSedang = 150;  
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//SCL ke A5
//SDA ke A4
void setup()      
{
    pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Arduino LCM IIC 2004");
  lcd.setCursor(1,1);
  lcd.print("Power By Ec-yuan!");
  delay(3000);
  lcd.clear();
}


void loop()
{
digitalWrite(trigPin2, LOW);
delayMicroseconds(5);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
pinMode(echoPin2, INPUT);
duration2 = pulseIn(echoPin2, HIGH);
cm2 = (duration2/2) / 29.1;
tinggiTS = torenSedang - cm2;
Serial.print("Tingggi Toren Sedang : ");
Serial.print(tinggiTS);
Serial.print("cm");
Serial.println();
Serial.print("===============================================");
Serial.println();
lcd.setCursor(0,0);
lcd.print(tinggiTS);
delay(1000);
lcd.clear();
delay(1000);
}
