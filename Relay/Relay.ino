#define D0 16
//#define LED D0
//relay harus ke 3 Volt
//relay 3V gn nyala pas compile
void setup() 
{
  pinMode(D0,OUTPUT); // setup output
}

void loop() 
{
  digitalWrite(D0,HIGH); // Pin D0 is HIGH

}
