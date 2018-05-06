/*
 * This example show how to ping a remote machine using it's hostname
 */

#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid     = "santika";
const char* password = "lenteng12345678";

const char* remote_host = "127.0.0.1";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");  
  Serial.println(WiFi.localIP());

  Serial.print("Pinging host ");
  Serial.println(remote_host);

  if(Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
}

void loop() { }
