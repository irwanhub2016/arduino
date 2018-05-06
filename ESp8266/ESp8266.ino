#include <SoftwareSerial.h>
#define RX 10
#define TX 11

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
 
}

void loop()
{
  delay(2000);

  String cmd ="AT+CIPSTART=\"TCP\",\"192.168.1.4\",80";
  Serial.println(cmd);
  esp.println(cmd);

  if(esp.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
    
  String getStr ="GET /kirim.php?something=";
  getStr +="something";
  //HTTP/1.1\r\n Host: 192.168.1.4\r\n\r\n\r\n";
  //getStr += " HTTP/1.1\r\n";
  //getStr += "Host: 192.168.1.4\r\n\r\n\r\n"; // Host
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
  delay(10000);
}



