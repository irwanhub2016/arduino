#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Sensor 1
int sensorPin1 = 5;
int ledPin1 = 13;

// Sensor 2
int sensorPin2 = 4;
int ledPin2 = 12;

// Sensor 3
int sensorPin3 = 0;
int ledPin3 = 14;

void setup() {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("yourSSID", "yourPASS");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}

void loop() {

 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;    //Declare object of class HTTPClient
   int sensor = digitalRead(sensorPin1);
   int sensor1 = digitalRead(sensorPin2);
   int sensor2 = digitalRead(sensorPin3);
   http.begin("http://192.168.1.69:80/smart_parking/sensor.php");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   String reqBody = "sensor=" + sensor + "&sensor1=" + sensor1 + "&sensor2=" + sensor2;
   int httpCode = http.POST(reqBody);   //Send the request
   String payload = http.getString();                  //Get the response payload

   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection

 }else{

    Serial.println("Error in WiFi connection");   

 }

  delay(30000);  //Send a request every 30 seconds

}

