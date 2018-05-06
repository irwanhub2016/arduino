#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
#define DEBUG true

#define TRIGGER_PIN_SATU  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_SATU     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_DUA  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_DUA     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).
#define buzzer 5 // Maximum distance we want to ping for (in centimeters).
#define led_merah 2 // Maximum distance we want to ping for (in centimeters).
#define led_biru 3 // Maximum distance we want to ping for (in centimeters).
#define led_kuning 4 // Maximum distance we want to ping for (in centimeters).


NewPing sonarSatu(TRIGGER_PIN_SATU, ECHO_PIN_SATU, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarDua(TRIGGER_PIN_DUA, ECHO_PIN_DUA, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

SoftwareSerial ser(10, 11); // RX, TX untuk McCloud
//RX mc ke RX arduino -> sebaliknya

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//SCL ke A5
//SDA ke A4

int led_merah=2;
int led_kuning=4; 
int led_biru=3;
int buzzer=5;

int sensor1;
int sensor2;


void setup() {
  Serial.begin(115200);
  ser.begin(115200);

  pinMode(led_biru, OUTPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  //connectWifi();
  //Serial.print("TCP/UDP Connection...\n");
  //sendCommand("AT+CIPMUX=0\r\n",2000,DEBUG); // reset module
  delay(3000);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
   lcd.setCursor(0,0);
  lcd.print("Mulai Monitor");
   lcd.setCursor(7,1);
  lcd.print("Air");
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, HIGH);
  delay(3000);
}

void loop() {
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, LOW);
  digitalWrite(buzzer, LOW);

  // put your main code here, to run repeatedly:
  sensor1 = sonarSatu.ping_cm();
  sensor2 = sonarDua.ping_cm();
//  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping Sensor 1 : ");
  Serial.print(sensor1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping Sensor 2 : ");
  Serial.print(sensor2); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  delay(3000);
    digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, HIGH);
    digitalWrite(buzzer, HIGH);
  delay(3000);
    sendDataID();
    delay(5000);
  /*digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, LOW);
  delay(1000);
  sensor1 = sonarSatu.ping_cm();
  sensor2 = sonarDua.ping_cm();
//  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping Sensor 1 : ");
  Serial.print(sensor1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping Sensor 2 : ");
  Serial.print(sensor2); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, HIGH);
  delay(1000);
    
  /*if(sensor1>10)
  {
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, HIGH);
    sendDataID();
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("Tinggi Air");
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Toren 1 : ");
    lcd.setCursor(4,1);
    lcd.print(sensor1);
    lcd.setCursor(8,1);
    lcd.print("cm");
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Toren 2 : ");
    lcd.setCursor(4,1);
    lcd.print(sensor2);
    lcd.setCursor(8,1);
    lcd.print("cm"); 
    delay(2000);
  }
  else if (sensor1<10)
  {  
    digitalWrite(led_kuning, LOW);
    digitalWrite(led_merah, HIGH);
    sendDataID();
    if(sensor1<10)
    {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Toren Besar Habis");
    delay(2000);}
    else if(sensor2<10)
    {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Toren Sedang Habis");
    delay(2000);}
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Status");
    lcd.setCursor(4,0);
    lcd.print(sensor1);
    lcd.setCursor(10,0);
    lcd.print("cm");
    lcd.setCursor(0,1);
    lcd.print("Air Habis");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proses");
    lcd.setCursor(0,1);
    lcd.print("Kirim Air");
    lcd.clear();
    delay(2000);
  }
  
  /*else if (sensor1<10)
  {
//    delay(15000);
//    delay(15000);
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("Status");
    lcd.setCursor(7,1);
    lcd.print("Air Habis");
    delay(1000);
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("Proses");
    lcd.setCursor(7,1);
    lcd.print("Kirim Air");
    lcd.clear();
    delay(2000);
    //sendDataID();
    //sendSMS();
    }*/

}

void sendDataID() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.3";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);
  
  String cmd2 = "GET /depot/getTangkiAirData?sensor1="; // Link ke skrip PHP                    
  cmd2 += sensor1;
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.1.3\r\n\r\n\r\n"; // Host
  String pjg="AT+CIPSEND=";
  pjg += cmd2.length();
  pjg += "\r\n";
    
  sendCommand(pjg,1000,DEBUG);
  delay(500);
  sendCommand(cmd2,1000,DEBUG);
  delay(5000);
}

String sendCommand(String command, const int timeout, boolean debug) {
  String response = "";
      
  ser.print(command); // send the read character to the esp8266
      
  long int time = millis();
      
  while( (time+timeout) > millis()) {
    while(ser.available()) {
      // The esp has data so display its output to the serial window 
      char c = ser.read(); // read the next character.
      response+=c;
    }  
  }
     
  if(debug) {
    Serial.print(response);
  }
      
  return response;
}

void sendSMS() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.43.251";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);
  
  String cmd2 = "GET /depot/getIFTTT?order="; // Link ke skrip PHP                    
  cmd2 += "send";
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.43.251\r\n\r\n\r\n"; // Host
  String pjg="AT+CIPSEND=";
  pjg += cmd2.length();
  pjg += "\r\n";
    
  sendCommand(pjg,1000,DEBUG);
  delay(500);
  sendCommand(cmd2,1000,DEBUG);
  delay(5000);
}

void connectWifi() {
  //Set-wifi
  Serial.print("Restart Module...\n");
  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  delay(5000);
  Serial.print("Set wifi mode : STA...\n");
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  delay(5000);
  Serial.print("Connect to access point...\n");
  sendCommand("AT+CWJAP=\"santika\",\"lenteng12345678\"\r\n",3000,DEBUG);
  delay(5000);
  Serial.print("Check IP Address...\n");
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  delay(5000);
}
