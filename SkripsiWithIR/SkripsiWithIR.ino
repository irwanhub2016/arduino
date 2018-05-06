/*
   This sketch shows an example of sending a reading to data.sparkfun.com once per day.

   It uses the Sparkfun testing stream so the only customizing required is the WiFi SSID and password.

   The Harringay Maker Space
   License: Apache License v2
*/
#include <LiquidCrystal_I2C.h>
#include "HX711.h"  //You must have this library in your arduino library folder
#include <NTPtimeESP.h>
#include <ESP8266WiFi.h>

#define DEBUG_ON

#define SAKLAR  16 //D0
#define SAKLAR_GALON  15 //D0
#define BUTTON  0

#define DOUT  2
#define CLK  13

#define TRIGGER_PIN  14 // D5
#define ECHO_PIN     12 //D6 

LiquidCrystal_I2C lcd(0x27, 16, 2);

HX711 scale(DOUT, CLK);
float calibration_factor = -96650;
int buttonState = 0;

NTPtime NTPch("id.pool.ntp.org");   // Choose server pool as required
char *ssid      = "santika";               // Set you WiFi SSID
char *password  = "lenteng12345678";               // Set you WiFi password
const char* host = "192.168.1.8";
const char* passcode = "admin";

const int analogInPin = A0;
int tinggiGalon;
int sensorValue = 0;        // value read from the pot
/*
 * The structure contains following fields:
 * struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte dayofWeek;
  boolean valid;
};
 */
strDateTime dateTime;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");
   
  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);

  Serial.print("Connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  
  pinMode(SAKLAR, OUTPUT);
  pinMode(SAKLAR_GALON, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON, INPUT);
  
  scale.set_scale(-96650);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0
}

void loop() {

  dateTime = NTPch.getNTPtime(7.0, 0);
  double duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2);  
  digitalWrite(TRIGGER_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);  
  duration = pulseIn(ECHO_PIN, HIGH); 
  distance = (duration/2) / 29.1;
  
  sensorValue = analogRead(analogInPin);
  tinggiGalon = sensorValue + 7;
  int distanceBaru=distance+30;

  buttonState = digitalRead(BUTTON);
  delay(50);
  
  if (buttonState == HIGH && distance>10 && distance<=70) 
  {
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("Pengisian Nyala");
    digitalWrite(SAKLAR_GALON, HIGH);
  
    if(dateTime.valid)
    {
    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;
    if(actualMinute>18)
    {
        lcd.clear();
        digitalWrite(SAKLAR_GALON, HIGH);
        digitalWrite(SAKLAR_LAMPU, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Lampu dinyalakan");
        lcd.setCursor(0, 1);
        lcd.println(distance);
        lcd.setCursor(2, 1);
        lcd.println(" cm");
        Serial.print("Weight: ");
        Serial.print(scale.get_units(), 3);  
        Serial.println(" kg");
        if(distance==10)
        {              
              delay(500);
              String url = "/test.php?ketinggian=";
              url += distanceBaru;
              url += "&berat=";
              url += berat;
              url += "&pass=";
              url += passcode;
            
              Serial.print("Requesting URL: ");
              Serial.println(url);
              client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");
              unsigned long timeout = millis();
              while (client.available() == 0) {
                if (millis() - timeout > 5000) {
                  Serial.println(">>> Client Timeout !");
                  client.stop();
                  return;
                }
              }
            
              Serial.println();
              Serial.println("Closing connection");
              
              Serial.println("Going to sleep");
              delay(5000);
              ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
              delay(5000);}--p
       
        else
        {}       
    }
    
    else
    {
        lcd.clear();
        digitalWrite(SAKLAR_GALON, HIGH);
        digitalWrite(SAKLAR_LAMPU, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Lampu dimatikan");
        lcd.setCursor(0, 1);
        lcd.println(distance);
        lcd.setCursor(2, 1);
        Serial.print("Weight: ");
        Serial.print(scale.get_units(), 3);  
        Serial.println(" kg");

        if((actualMinute==07 && actualsecond==01) || (distance==10))
        {     
              delay(500);
              String url = "/test.php?statusLampu=";
              url += statusLampu;
              url += "&ketinggian=";
              url += distanceBaru;
              url += "&pass=";
              url += passcode;
            
              Serial.print("Requesting URL: ");
              Serial.println(url);
              client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");
              unsigned long timeout = millis();
              while (client.available() == 0) {
                if (millis() - timeout > 5000) {
                  Serial.println(">>> Client Timeout !");
                  client.stop();
                  return;
                }
              }
            
              Serial.println();
              Serial.println("Closing connection");
              
              Serial.println("Going to sleep");
              delay(5000);
              ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
              delay(5000);}
        else
        {}
    }
//    delay(50);
  }
  } 

  else if (buttonState == HIGH && distance < 10 ) 
  {
  }
  
  else 
  {
    digitalWrite(SAKLAR_GALON, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pengisian Mati");

    if(dateTime.valid){   
    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;
    Serial.println(actualHour);
    
    if(actualMinute>18)
    {
        digitalWrite(SAKLAR_LAMPU, HIGH);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("Saatnya Sholat Maghrib");
        lcd.setCursor(0, 1);
        lcd.println(distance);
        lcd.setCursor(2, 1);
        lcd.println(" cm");
        Serial.print("Weight: ");
        Serial.print(scale.get_units(), 3);  
        Serial.println(" kg");            

        if(actualsecond==01)
        {              
              delay(500);
              String url = "/test.php?statusLampu=";
              url += statusLampu;
              url += "&pass=";
              url += passcode;
            
              Serial.print("Requesting URL: ");
              Serial.println(url);
              client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");
              unsigned long timeout = millis();
              while (client.available() == 0) {
                if (millis() - timeout > 5000) {
                  Serial.println(">>> Client Timeout !");
                  client.stop();
                  return;
                }
              }
            
              Serial.println();
              Serial.println("Closing connection");
              
              Serial.println("Going to sleep");
              delay(5000);
              ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
              delay(5000);}
        else
        {}
    }
    else
    {
        digitalWrite(SAKLAR_LAMPU, LOW);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.println(distance);
        lcd.setCursor(2, 1);
        lcd.println(" cm");
        Serial.print("Weight: ");
        Serial.print(scale.get_units(), 3);  
        Serial.println(" kg");
        if(actualMinute==07 && actualsecond==01 )
        {     
              delay(500);
              String url = "/test.php?statusLampu=";
              url += statusLampu;
              url += "&pass=";
              url += passcode;
            
              Serial.print("Requesting URL: ");
              Serial.println(url);
              client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                           "Host: " + host + "\r\n" +
                           "Connection: close\r\n\r\n");
              unsigned long timeout = millis();
              while (client.available() == 0) {
                if (millis() - timeout > 5000) {
                  Serial.println(">>> Client Timeout !");
                  client.stop();
                  return;
                }
              }
            
              Serial.println();
              Serial.println("Closing connection");
              
              Serial.println("Going to sleep");
              delay(5000);
              ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
              delay(5000);}
        else
        {}           
    }
//    delay(50);
  }
  }
}
