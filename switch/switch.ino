#define BUTTON  0
int buttonState = 0;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(BUTTON);
  delay(50);
  if (buttonState == HIGH)
  {Serial.println("OK");
  }
  else
  {Serial.println("NONE");
  }
}
