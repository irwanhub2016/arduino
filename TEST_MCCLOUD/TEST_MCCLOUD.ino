#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define DEBUG true

SoftwareSerial ser(10, 11); // RX, TX untuk McCloud

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int trigPin1 = 7; 
int echoPin1 = 6; 

int trigPin2 = 9; 
int echoPin2 = 8; 

long duration1, cm1, duration2, cm2, tinggiTB, tinggiTS;

int torenBesar = 180;
int torenSedang = 150;  

int led_merah=2;
int led_kuning=4; 
int led_biru=3;
int buzzer=5;

void setup() {
  delay(2000);
  Serial.begin(115200);
  ser.begin(115200);  
  connectWifi();
  Serial.print("TCP/UDP Connection...\n");
  sendCommand("AT+CIPMUX=0\r\n",2000,DEBUG); // reset module
  delay(3000);
  
  pinMode(led_biru, OUTPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  
  pinMode(buzzer, OUTPUT);
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
  
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, HIGH);
  delay(1000);
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, LOW);
  lcd.clear();  
  delay(1000);
}

void loop() {

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
lcd.clear();

sendDataID();

smsDataPass();

    
delay(100);

/*if((tinggiTB>10 && tinggiTB<=180) && (tinggiTS>10 && tinggiTS<=150))
{
    digitalWrite(led_biru, HIGH);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, LOW); 
    delay(500); 
    lcd.setCursor(3,0);
    lcd.print("Kondisi Air");
    lcd.setCursor(4,1);
    lcd.print("Penuh");
    delay(1000);
    lcd.clear();
    delay(1000);
    Serial.print(tinggiTB);
    Serial.print("cm");
    Serial.println();
    Serial.print(tinggiTS);
    Serial.print("cm");
    Serial.println();
    sendDataID();
    delay(5000);
}

else if((tinggiTB>10 && tinggiTB<=180) && tinggiTS<10)  
{
    digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, HIGH); 
    delay(500); 
    lcd.setCursor(3,0);
    lcd.print("Toren Sedang");
    lcd.setCursor(4,1);
    lcd.print("Habis");
    delay(1000);
    lcd.clear();
    delay(1000);
    Serial.print(tinggiTS);
    Serial.print("cm");
    Serial.println();
    sendDataID();
    delay(5000);
}

else if((tinggiTS>10 && tinggiTS<=100) && tinggiTB<10)  
{
    digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, HIGH);
    delay(500); 
    lcd.setCursor(3,0);
    lcd.print("Toren Besar");
    lcd.setCursor(4,1);
    lcd.print("Habis");
    delay(1000);
    lcd.clear();
    delay(1000);
    Serial.print(tinggiTB);
    Serial.print("cm");
    Serial.println();
    sendDataID();
    delay(5000);
}

else if(tinggiTB<10 && tinggiTS<10)  
{
    digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, HIGH);
    digitalWrite(led_kuning, LOW); 
    delay(500);      
    lcd.setCursor(3,0);
    lcd.print("Tangki Air");
    lcd.setCursor(4,1);
    lcd.print("Habis Total");
    delay(1000);
    lcd.clear();
    delay(1000);
    smsDataPass();
    delay(5000);
}
else
{
    digitalWrite(led_biru, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(led_biru, LOW);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(led_biru, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(led_biru, LOW);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(led_biru, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(led_biru, LOW);
    digitalWrite(buzzer, HIGH);
    delay(50);
}*/ 
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

void smsDataPass() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.5";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);

  String cmd2 = "GET /depot/getIFTTT?order=";    
  cmd2 += "pass";
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.1.5\r\n\r\n\r\n"; // Host
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
