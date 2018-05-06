#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>
#define DEBUG true

SoftwareSerial ser(10, 11); // RX, TX
LiquidCrystal_I2C lcd(0x27,16,2);

int trigPin1 = 7;
int echoPin1 = 6;

int trigPin2 = 9; 
int echoPin2 = 8;

int torenBesar = 180;
int torenSedang = 150;  

int led_merah=2;
int led_kuning=3; 
int led_biru=4;
int buzzer=5;

long duration1, cm1, duration2, cm2, tinggiTB, tinggiTS;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Mulai Monitor");
  lcd.setCursor(7,1);
  lcd.print("Air");
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(led_biru, OUTPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  ser.begin(115200);
  connectWifi();
  Serial.print("TCP/UDP Connection...\n");
  sendCommand("AT+CIPMUX=0\r\n",2000,DEBUG); // reset module
  delay(2000);
}
void loop() {
  delay(3000);
  lcd.clear();
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
  
  //Serial.print("Tinggi Toren Besar : ");
  //Serial.print(tinggiTB);
  //Serial.print("cm");
  //Serial.println();  
  //lcd.setCursor(3,0);
  //lcd.print("Toren Besar");
  //lcd.setCursor(6,1);
  //lcd.print(tinggiTB);
 
  if(tinggiTB>10 && tinggiTS>10)
  {
  lcd.setCursor(0,0);
  lcd.print("Tor.Besar");
  lcd.setCursor(10,0);
  lcd.print(tinggiTB);
  lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("Tor.Kecil");
  lcd.setCursor(10,1);
  lcd.print(tinggiTS);
  lcd.setCursor(14,1);
  lcd.print("cm");
  sendDataID();
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, LOW);
  delay(5000);}
  
  else if(tinggiTB>10 && tinggiTS<=10)
  {
  lcd.setCursor(0,0);
  lcd.print("Tor.Besar");
  lcd.setCursor(10,0);
  lcd.print(tinggiTB);
  lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("Tor.Kecil");
  lcd.setCursor(10,1);
  lcd.print(tinggiTS);
  lcd.setCursor(14,1);
  lcd.print("cm");
  sendDataID();
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, HIGH);
  delay(5000);}

  else if(tinggiTB<=10 && tinggiTS>10)
  {
  lcd.setCursor(0,0);
  lcd.print("Tor.Besar");
  lcd.setCursor(10,0);
  lcd.print(tinggiTB);
  lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("Tor.Kecil");
  lcd.setCursor(10,1);
  lcd.print(tinggiTS);
  lcd.setCursor(14,1);
  lcd.print("cm");
  sendDataID();
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, HIGH);
  delay(5000);}
  
  else
  {
  lcd.setCursor(2,0);
  lcd.print("Status Toren");
  lcd.setCursor(6,1);
  lcd.print("Habis");
  smsDataPass();
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, LOW);
  delay(5000);}
  delay(2000);
}

void sendDataID() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.5";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);
  
  String cmd2 = "GET /depot/getTangkiAirData?sensor1="; // Link ke skrip PHP                    
  cmd2 += tinggiTB;
  cmd2 += "&sensor2=";
  cmd2 += tinggiTS;
  cmd2 += "&order=";
  cmd2 += "full";
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.1.5\r\n\r\n\r\n"; // Host
  String pjg="AT+CIPSEND=";
  pjg += cmd2.length();
  pjg += "\r\n";
  delay(2000);  
  sendCommand(pjg,1000,DEBUG);
  delay(500);
  sendCommand(cmd2,1000,DEBUG);
  delay(3000);
}

void smsDataPass() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.5";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);

  String cmd2 = "GET /depot/getIFTTT?sensor1=";                    
  cmd2 += tinggiTB;
  cmd2 += "&sensor2=";
  cmd2 += tinggiTS;
  cmd2 += "&order=";
  cmd2 += "pass";
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.1.5\r\n\r\n\r\n";
  String pjg="AT+CIPSEND=";
  pjg += cmd2.length();
  pjg += "\r\n";
 
  sendCommand(pjg,1000,DEBUG);
  delay(500);
  sendCommand(cmd2,1000,DEBUG);
  delay(3000);
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

void connectWifi() {

  Serial.print("Restart Module...\n");
  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  delay(2000);
  Serial.print("Set wifi mode : STA...\n");
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  delay(2000);
  Serial.print("Connect to access point...\n");
  sendCommand("AT+CWJAP=\"santika\",\"lenteng12345678\"\r\n",1234,DEBUG);
  delay(2000);
  Serial.print("Check IP Address...\n");
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  delay(2000);
}
