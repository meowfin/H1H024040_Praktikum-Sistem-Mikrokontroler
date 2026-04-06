int led = 13;
int sensor = 1;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  if(sensor == 1){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
