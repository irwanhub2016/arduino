#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define DEBUG true

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).

SoftwareSerial ser(10, 11); // RX, TX untuk McCloud

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//SCL ke A5
//SDA ke A4

int led_merah=3, led_hijau=4;
int buzzer=5;

int sensor1;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  delay(5000);               
  Serial.begin(115200);
  ser.begin(115200);
  connectWifi();
  Serial.print("TCP/UDP Connection...\n");
  sendCommand("AT+CIPMUX=0\r\n",2000,DEBUG); // reset module
  delay(5000);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
   lcd.setCursor(0,0);
  lcd.print("Starting");
   lcd.setCursor(1,1);
  lcd.print("Monitoring...");
}

void loop() {
  sensor1 = sonar.ping_cm();
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sensor1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if(sensor1>5)
  {}
  else if (sensor1<5)
  {  
    sendDataID();
  }
}

void sendDataID() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
  cmd += "192.168.1.4";
  cmd += "\",3000\r\n";
  sendCommand(cmd,1000,DEBUG);
  delay(5000);
  
  String cmd2 = "GET /monitoring?sensor="; // Link ke skrip PHP                    
  cmd2 += id;
  cmd2 += "&sms=";
  cmd2 += HIGH;  
  cmd2 += " HTTP/1.1\r\n";
  cmd2 += "Host: 192.168.1.4\r\n\r\n\r\n"; // Host
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
