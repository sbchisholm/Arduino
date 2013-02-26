/* Blink
 * Turns on an LED for one second, then off for one second,
 * repeatedly.
 */

int ledPin = 9;

// The setup() method runs once, when the sketch starts
void setup() {
  pinMode(ledPin, OUTPUT);
}

// the loop() method runs over and over again,
// as long as the Arduino has power
void loop() {
  // increase brightness
  for(int i = 10; i <= 255; i += 10) {
    analogWrite(ledPin, i);
    delay(30);
  }
  // decrease brightness
  for(int i = 255; i >= 10; i -= 10) {
    analogWrite(ledPin, i);
    delay(30);
  }
}
