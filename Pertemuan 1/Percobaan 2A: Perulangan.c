int led = 13;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for(int i = 0; i < 5; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
