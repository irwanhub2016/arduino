#include "Adafruit_FONA.h"
#include <Wire.h>

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// this is a large buffer for replies
char replybuffer[255];
// We default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Hardware serial is also possible!
//  HardwareSerial *fonaSerial = &Serial1;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

void setup() {
  
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("SIM800L V2 test!"));
  Serial.println(F("Initializing...."));
  
  // make it slow so its easy to read!
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    
    Serial.println(F("Couldn't find SIM800L"));
    while(1);
  }
  Serial.println(F("SIM800L Detected"));
  delay (3000);

  
  // Print SIM card IMEI number.
  char imei[15] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
   
  Serial.println("SIM800L IMEI: "); 
  Serial.println(imei);
  delay (3000);
  }

  // Print SIM card CCID number.
  char ccid[20] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t ccidLen = fona.getSIMCCID(ccid);
  if (ccidLen > 0) {
  Serial.println("SIM card CCID: "); 
  Serial.println(ccid);
  delay (3000);
  }
  
  // Print SIM card CCID number.
  uint8_t stat = fona.getNetworkStatus();
  Serial.println("SIM Network Status: "); 
  if(stat==0){
  Serial.println(F("Not Registered!!"));
  }
  if(stat==1){
  Serial.println(F("Registered Ntwrk"));
  }
  if(stat==2){
  Serial.println(F("Searching Ntwrk!"));
  }

 delay (2000);
// Print Battery Percent & Voltage
 Serial.println (F("   ->Battery Percent & Voltage"));
 uint16_t *p = 0;
 fona.getBattPercent(p);
  Serial.println("SIM Battery Stat "); 
  Serial.println(F("di SerialMonitor"));

    delay(3000);
  Serial.println("Hello World.....");
  Serial.println("SIM800L V2 Ready ");
  Serial.println(F("Finish"));
}

  
void loop() {
 
}
