#include <ESP8266WiFi.h>
const char* ssid  = "santika";
const char* password = "lenteng12345678";
const char* host = "192.168.1.8";
const char* passcode = "admin";

// Switch pin numbers
// Wake from sleep, in seconds.
#define wakeuptime 30
#define TRIGGER 5
#define ECHO    4

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  delay(10);
  Serial.println();
  Serial.println();
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

  delay(3000);

  // Connect to host
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  delay(500);
  // Read switch values
  // Create a URL for the request. Modify YOUR_HOST_DIRECTORY so that you're pointing to the PHP file.
  String url = "/test.php?ketinggian=";
  url += distance;
  url += "&pass=";
  url += passcode;

  // This will send the request to the server
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
  
  // Sleep
  Serial.println("Going to sleep");
  delay(5000);
  ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
  delay(5000);
}

void loop() {
}

