#include <SoftwareSerial.h>
#define RX 10
#define TX 11
//#define kipas 3

String apiKey = "pd-rA0kgBEZ5jGgnAS_EePIGmhnY-yZTCTVZZAFxviR"; //GANTI APIKEYNYA
String Wifi = "santika"; //SSID wifi
String Pass = "lenteng12345678"; //password wifi

SoftwareSerial esp(RX,TX);

void setup()
{
  Serial.begin(115200);
  esp.begin(115200);
  Serial.println("Koneksi dimulai");

  String buatLogin = "AT+CWJAP=\"";
  buatLogin +=Wifi;
  buatLogin +="\",\"";
  buatLogin +=Pass;
  buatLogin +="\"";
  
  //SETTING ESP AWAL
  esp.println("AT+CWMODE=3");
  delay(2000);
  esp.println(buatLogin);
  Serial.println(buatLogin);
  delay(5000);
  esp.println("AT+CIPMUX=0");
  delay(1000);
    delay(2000);
   
  String cmd ="AT+CIPSTART=\"TCP\",\"maker.ifttt.com\",80";
  Serial.println(cmd);
  esp.println(cmd);

  if(esp.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
    
  String getStr ="GET /trigger/PesanGalon/with/key/";
  
  //String getStr ="GET /api/data?api_key=86585cab9282b29743fe2b70b11a0c2c&attributes={\"T1\":39,\"H1\":20}"; // geeknesia
  
  getStr +=apiKey;
  
  getStr +="\r\n\r\n";

  cmd="AT+CIPSEND=";
  cmd +=String(getStr.length());
  Serial.println(cmd);
  esp.println(cmd);
  delay(3000);

  if(esp.find(">"))
  {
    Serial.print(getStr);
    esp.print(getStr);
    Serial.print("\n");
  }
  else
  {
    esp.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE \n");
  }
  delay(5000);
 }

void loop()
{

}
