 #include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
//#include <NewPing.h>
#define DEBUG true

//#define TRIGGER_PIN_SATU  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define ECHO_PIN_SATU     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define TRIGGER_PIN_DUA  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define ECHO_PIN_DUA     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).
//NewPing sonarSatu(TRIGGER_PIN_SATU, ECHO_PIN_SATU, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//NewPing sonarDua(TRIGGER_PIN_DUA, ECHO_PIN_DUA, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

SoftwareSerial ser(10, 11); // RX, TX untuk McCloud

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int trigPin1 = 7; //Trig – green Jumper
int echoPin1 = 6; //Echo – yellow Jumper

int trigPin2 = 9; //Trig – green Jumper
int echoPin2 = 8; //Echo – yellow Jumper

int torenBesar = 180;
int torenSedang = 150;  

long duration1, cm1, duration2, cm2, tinggiTB, tinggiTS;
int led_merah=2;
int led_kuning=4; 
int led_biru=3;
int buzzer=5;
void setup() {
  // put your setup code here, to run once:
  delay(2000); 
  
  Serial.begin(115200);
  ser.begin(115200);  
  pinMode(led_biru, OUTPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  connectWifi();
  Serial.print("TCP/UDP Connection...\n");
  sendCommand("AT+CIPMUX=0\r\n",2000,DEBUG); // reset module
  delay(2000);
  lcd.init();                      // initialize the lcd 
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
}

void loop() {

digitalWrite(trigPin1, LOW);
digitalWrite(trigPin2, LOW);
delayMicroseconds(5);
digitalWrite(trigPin1, HIGH);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
digitalWrite(trigPin2, LOW);
pinMode(echoPin1, INPUT);
pinMode(echoPin2, INPUT);


duration1 = pulseIn(echoPin1, HIGH);
duration2 = pulseIn(echoPin2, HIGH);
cm1 = (duration1/2) / 29.1;
cm2 = (duration2/2) / 29.1;

tinggiTB = torenBesar - cm1;
tinggiTS = torenSedang - cm2;

Serial.print(cm1);
Serial.print("cm");
Serial.println();
Serial.print(cm2);
Serial.print("cm");
Serial.println();

if((tinggiTB>10 && tinggiTB<=150) && (tinggiTS>10 && tinggiTS<=100))
{
    /*
    lcd.clear();  

    digitalWrite(led_biru, HIGH);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, LOW);
 
    lcd.setCursor(3,0);
    lcd.print("Kondisi Air");
    lcd.setCursor(4,1);
    lcd.print("Penuh");
    delay(3000);
    lcd.clear();
    Serial.print(cm1);
    Serial.print("cm");
    Serial.println();
    
    lcd.setCursor(3,0);
    lcd.print("Toren 1 : ");
    lcd.setCursor(4,1);
    lcd.print(tinggiTB);
    lcd.setCursor(7,1);
    lcd.print("cm");
    delay(1000);
    lcd.clear();

    Serial.print(tinggiTS);
    Serial.print("cm");
    Serial.println();
    
    lcd.setCursor(3,0);
    lcd.print("Toren 2 : ");
    lcd.setCursor(4,1);
    lcd.print(cm2);
    lcd.setCursor(7,1);
    lcd.print("cm");
    sendDataID();
    delay(5000);*/
    sendDataID();
    delay(5000);
  }
  
else if((tinggiTB>10 && tinggiTB<=150) && tinggiTS<10)  
{
    /*lcd.clear();  
    digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);            
    lcd.clear();
    
    Serial.print(tinggiTB);
    Serial.print("cm");
    Serial.println();
    lcd.setCursor(5,0);
    lcd.print("Status");
    lcd.setCursor(0,1);
    lcd.print("Toren 2 Habis");
    sendDataID();
    delay(5000);*/
    sendDataID();
    delay(5000);
}

else if((tinggiTS>10 && tinggiTS<=100) && tinggiTB<10)  
{
    /*digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);            
    lcd.clear();
    
    Serial.print(tinggiTB);
    Serial.print("cm");
    Serial.println();
    
    lcd.setCursor(5,0);
    lcd.print("Status");
    lcd.setCursor(0,1);
    lcd.print("Toren 1 Habis");
    sendDataID();
    delay(5000);*/    
    sendDataID();
    delay(5000);
}

else if(cm1<10 && cm2<10)  
{
    /*digitalWrite(led_biru, LOW);  
    digitalWrite(led_merah, HIGH);
    digitalWrite(led_kuning, LOW);
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);    
    digitalWrite(buzzer, HIGH);
    delay(250);    
    digitalWrite(buzzer, LOW);
    delay(250);            
    lcd.clear();
    Serial.print(cm1);
    Serial.print("cm");
    Serial.println();
    lcd.setCursor(5,0);
    lcd.print("Status");
    lcd.setCursor(4,1);
    lcd.print("Air Habis");
    delay(1000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Proses");
    lcd.setCursor(4,1);
    lcd.print("Kirim Air");
    delay(3000);  
    lcd.clear();
    delay(3000);*/    
    sendDataID();
     delay(5000);   
    smsDataPass();
    delay(5000);
}

else
{
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Tidak");
    lcd.setCursor(4,1);
    lcd.print("Ada Data");
    Serial.println("Tidak ada data yang terdeteksi");
    //delay(3000);
    sendDataID();
    delay(5000);
  }

  delay(3000);
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

void smsDataPass() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.5";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);

  String cmd2 = "GET /depot/getIFTTT?order="; // Link ke skrip PHP                    
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

void smsDataFull() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.5";
  cmd += "\",1234\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);

  String cmd2 = "GET /depot/getIFTTT?order="; // Link ke skrip PHP                    
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

