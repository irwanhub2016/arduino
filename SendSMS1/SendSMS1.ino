#include <SoftwareSerial.h>
SoftwareSerial Sim900Serial(2, 3);
void setup()
{
  Sim900Serial.begin(115200);               // GPRS baud rate  
  delay(500);
  Sim900Serial.println("AT+IPR=19200");
  delay(500);
  Sim900Serial.begin(19200);               // GPRS baud rate , Tüm shieldlarda aynı değildir 
  delay(1000);
  Serial.begin(9600);               // bilgisayar seri port baud rate
 Serial.println("SMS gondermek icin g tusuna basiniz: "); 
}
void loop()
{   
   if (Serial.available())
    switch(Serial.read())
   {
     case 'g':
       SendTextMessage();
       break;
    } 
   if (Sim900Serial.available())
    Serial.write(Sim900Serial.read());
}
void SendTextMessage()
{
  Sim900Serial.print("AT+CMGF=1\r");    //SMS text halde gönderilir. Bu komutun ne iş yaptığı sim900 AT komut manuelinden bakılır
  delay(100);
  Sim900Serial.println("AT + CMGS = \"05425420000\"");//mesajın gönderileceği numara
  delay(100);
  Sim900Serial.println("golmuhendis.blogspot.com.tr");//gönderilecek mesaj
  delay(100);
  Sim900Serial.println((char)26);
  delay(100);
  Sim900Serial.println();
}


