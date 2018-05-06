int led_merah=2;
int led_kuning=4; 
int led_biru=3;
int buzzer=5;
void setup() {
  // put your setup code here, to run once:
  pinMode(led_biru, OUTPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_biru, HIGH);
  digitalWrite(led_kuning, HIGH);
  delay(1000);
  digitalWrite(led_merah, LOW);
  digitalWrite(led_biru, LOW);
  digitalWrite(led_kuning, LOW);  
  digitalWrite(buzzer, HIGH);
  delay(1000);
}
