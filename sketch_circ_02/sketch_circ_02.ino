
int ledPins[] = {2,3,4,5,6,7,8,9};
int ledCount = 8;

void setup() {
  for (int i = 0; i < ledCount; i++)
    pinMode(ledPins[i], OUTPUT);
}

void loop() {
  oneAfterAnotherNoLoop();
}

void oneAfterAnotherNoLoop() {
  int delayTime = 100;
  // turn on each LED
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }
  
  // turn off each LED
  for (int i = ledCount-1; i >=0; i--) {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}
