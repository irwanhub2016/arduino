#include <MySQL_Cursor.h>
#include <MySQL_Encrypt_Sha1.h>
#include <MySQL_Connection.h>
#include <MySQL_Packet.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


IPAddress server_addr(192,168,1,8); // IP of the MySQL server here
char user[] = "root"; // MySQL user login username
char password[] = "1234"; // MySQL user login password

// WiFi card example
char ssid[] = "santika"; // your SSID
char pass[] = "lenteng12345678"; // your SSID Password

// Sample query
char INSERT_SQL[] = "INSERT INTO monitoring_depot.admin (id_admin, username, password) VALUES (2, 'ade', 'admin')";

WiFiClient client;

MySQL_Connection conn((Client *)&client);

void setup() {
Serial.begin(115200);
// Begin WiFi section
WiFi.begin(ssid, pass);
// Wait for connection
while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}
Serial.println ( "" );
Serial.print ( "Connected to " );
Serial.println ( ssid );
Serial.print ( "IP address: " );
Serial.println ( WiFi.localIP() );
// End WiFi section
Serial.println("DB - Connecting...");
while (conn.connect(server_addr, 3306, user, password) != true) {
delay(500);
Serial.print ( "." );
}
}

void loop() {
delay(2000);

Serial.println("Recording data.");

// Initiate the query class instance
MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
// Execute the query
cur_mem->execute(INSERT_SQL);
// Note: since there are no results, we do not need to read any data
// Deleting the cursor also frees up memory used
delete cur_mem;
}
