const int analogInPin = A0;
int tinggiGalon;
int sensorValue = 0;        // value read from the pot
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(analogInPin);
tinggiGalon = sensorValue + 7;
    if(sensorValue>50)
    {Serial.println("Air nyala");
    Serial.println(sensorValue);}
    else if(sensorValue<50)
    {Serial.println("Air mati");
    Serial.println(sensorValue);
    Serial.print("Tinggi galon: ");
    Serial.print(tinggiGalon);
    Serial.println(" cm");}
    delay(1000);
}
