#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


//#define sensorPin2 D2
//#define typeDHT DHT11
//DHT dht(sensorPin1, typeDHT);

char ssid[] = "santika";                 // Network Name
char pass[] = "lenteng12345678";                 // Network Password
byte mac[6];

WiFiServer server(80);
IPAddress ip(192, 168, 1, 7);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO test.test (sensor) VALUES (4)";
//char INSERT_SQL[] = "INSERT INTO officeto_plants.TBL_READINGS(ID_PLANT, AIR_HUMIDITY, AIR_TEMPERATURE, SOIL_MOISTURE_1, SOIL_MOISTURE_2) VALUES (1, NULL, NULL, %d, %d)";
char query[128];

IPAddress server_addr(127, 0 , 0, 1);          // MySQL server IP
char user[] = "root";           // MySQL user
char password[] = "";       // MySQL password

void setup() {

  Serial.begin(9600);

  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");  

}

void loop() {

  int soil_hum = 4;
  //float t = dht.readTemperature();

  //Serial.println(t);

  delay(10000); //10 sec

  sprintf(query, INSERT_SQL, soil_hum);
  //sprintf(query, INSERT_SQL, soil_hum, t);

  Serial.println("Recording data.");
  Serial.println(query);
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  
  cur_mem->execute(query);

  delete cur_mem;

}
