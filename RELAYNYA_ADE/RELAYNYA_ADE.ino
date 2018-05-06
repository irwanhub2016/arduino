#define D0 16
#define D8 15
//relay harus ke 3 Volt
//relay 3V gn nyala pas compile
void setup() 
{
  pinMode(D0,OUTPUT); // setup output
    pinMode(D8,OUTPUT); // setup output
}

void loop() 
{
  digitalWrite(D0,LOW); // Pin D0 is HIGH // kalo low relay nyala
  digitalWrite(D8,LOW); // Pin D0 is HIGH // kalo low relay nyala
  delay(500);
  digitalWrite(D0,HIGH); // Pin D0 is LOW
    digitalWrite(D0,HIGH); // Pin D0 is LOW
  delay(500);
}
