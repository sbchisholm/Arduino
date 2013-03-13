/*
  Button
Turns on and off a light emitting diode(LED) connected to digital  
pin 13, when pressing a pushbutton attached to pin 7.
The circuit:
* LED attached from pin 13 to ground
* pushbutton attached to pin 2 from +5V
* 10K resistor attached to pin 2 from ground
* Note: on most Arduinos there is already an LED on the board
attached to pin 13.
created 2005
by DojoDave 
modified 17 Jun 2009
by Tom Igoe
  http://www.arduino.cc/en/Tutorial/Button
*/
// constants won’t change. They’re used here to
// set pin numbers:
const int inputPin1 = 3;     // the number of the pushbutton pin
const int inputPin2 = 2;
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(inputPin1, INPUT);    
  pinMode(inputPin2, INPUT);    
}

void loop(){
  off_loop();
}

void off_loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(inputPin2);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

void on_off_loop(){
  if (digitalRead(inputPin1) == LOW) {
    digitalWrite(ledPin, LOW); // turn LED OFF
  } else if (digitalRead(inputPin2) == LOW) {
    digitalWrite(ledPin, HIGH); // turn LED ON
  }
}

int value = 0;
void fading_loop(){
  if (digitalRead(inputPin1) == LOW) { value–; }
  else if (digitalRead(inputPin2) == LOW) { value++; }
  value = constrain(value, 0, 255);
  analogWrite(ledPin, value);
  delay(10);
}

