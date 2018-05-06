//Baru untuk Pengisian aja 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include <NTPtimeESP.h>
#define DEBUG_ON

NTPtime NTPch("id.pool.ntp.org");   // Choose server pool as required
const char* ssid     = "halo123";      // SSID
const char* password = "nasibasi";      // Password
//const char* ssid     = "santika";      // SSID
//const char* password = "lenteng12345678";      // Password
//const char *ssid = "XWORK"; // The name of the Wi-Fi network that will be created
//const char *password = "XWork-lt'23";   // The password required to connect to it, leave blank for an open network
const char* host = "192.168.43.251";  // IP serveur - Server IP
const int   port = 1234;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 
strDateTime dateTime;
    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;

//scl->D1
//SDA->D2
#define BUTTON 0 //D3 limit switch
#define SAKLAR_GALON  15 //D8
#define SAKLAR_LAMPU  16 //D0
const int analogInPin = A0; //INFRARED
HX711 scale(2, 13);

int tinggiGalon;
int sensorValue = 0; 
int buttonState = 0;
float calibration_factor = 2230; // this calibration factor LOADCELL
float units;
float ounces;    
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(BUTTON, INPUT);
  pinMode(SAKLAR_GALON, OUTPUT);
  pinMode(SAKLAR_LAMPU, OUTPUT);  
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();

  //LOADCELL
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {
    sensorValue = analogRead(analogInPin);
    tinggiGalon = sensorValue + 7;
    buttonState = digitalRead(BUTTON);

    //nsp off di LCD saat buttonState High
    if(buttonState == HIGH && sensorValue>500) 
    {
      lcd.clear(); 
      lcd.setCursor(1, 0);
      lcd.print("SYSTEM ON");
      Serial.println("SYSTEM ON");
      Serial.println(sensorValue);
      digitalWrite(SAKLAR_GALON, LOW); //INI Nyala, tp Karena tipe relaynya beda aja
      //PEMANGGILAN FUNGSI UTK LOAD CELL
      loadcell();
        {
          lcd.setCursor(6, 1);
          lcd.print(units);
          lcd.print(" Gram");
        };
      }
   else if (buttonState == HIGH && sensorValue<500) 
    {
      lcd.clear(); 
      lcd.setCursor(1, 0);
      lcd.print("PENUH");
      Serial.println(sensorValue);
      digitalWrite(SAKLAR_GALON, HIGH); //INI mati, tp Karena tipe relaynya beda aja
      Serial.println("PENUH");
      loadcell();
      kirimData();
      //PEMANGGILAN FUNGSI UNTUK JAM UNTUK DITAMPILKAN DI LCD
      //KODINGAN UNTUK NGIRIM DATA KE SERVER
     }
    else 
    {
      lcd.clear(); 
      lcd.setCursor(1, 0);
      lcd.print("SYSTEM OFF");
      Serial.println("SYSTEM OFF");
      Serial.println(sensorValue);
      digitalWrite(SAKLAR_GALON, HIGH); //INI mati, tp Karena tipe relaynya beda aja
      //PEMANGGILAN FUNGSI UNTUK JAM UNTUK DITAMPILKAN DI LCD
         }
delay(100);
}

//KODINGAN TERPISAH UNTUK LOAD CELL 
void loadcell()
{
    scale.set_scale(calibration_factor); //Adjust to this calibration factor

    Serial.print("Reading: ");
    units = scale.get_units(), 10;
    if (units < 0)
    {
      units = 0.00;
    }
    ounces = units * 0.035274;
    Serial.print(units);
    Serial.print(" grams"); 
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();/*
    lcd.setCursor(6, 1);
    lcd.print(units);
    lcd.print(" Gram");*/

    if(Serial.available())
    {
      char temp = Serial.read();
      if(temp == '+' || temp == 'a')
      calibration_factor += 1;
      else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
    }
}


void kirimData()
{
  unsigned long currentMillis = millis();
 
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }
 
    /*String url = "/watchdog?command=watchdog&uptime=";
    url += String(millis());
    url += "&ip=";
    url += WiFi.localIP().toString();*/
   
    String url = "/pengisian?berat=";
    url += units;
    url += "&status_lampu=";
    url += "nyala";
        
    // Envoi la requete au serveur - This will send the request to the server
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
      // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }  
}

void waktu()
{
  
    dateTime = NTPch.getNTPtime(7.0, 0);
    if(dateTime.valid)
    {

    
    if(actualHour > 17 && actualHour < 5)
    {
     //lampu nyala 
     Serial.print("Jam : ");
     Serial.print(actualHour);
     Serial.print(" Menit : ");
     Serial.print(actualMinute);
     Serial.print(" Detik : ");
     Serial.println(actualsecond); 
     digitalWrite(SAKLAR_LAMPU,LOW);    
     delay(50);      
    }
    
    else
    {
      //lampu mati
     Serial.print("Jam : ");
     Serial.print(actualHour);
     Serial.print(" Menit : ");
     Serial.print(actualMinute);
     Serial.print(" Detik : ");
     Serial.println(actualsecond);
     digitalWrite(SAKLAR_LAMPU,HIGH);           
     delay(50);      
    }
       
    }    
  }
