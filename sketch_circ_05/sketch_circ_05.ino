/* vim: set makeprg=make
 *     ---------------------------------------------------------
 *     |  Arduino Experimentation Kit Example Code             |
 *     |  CIRC-05 .: 8 More LEDs :. (74HC595 Shift Register)   |
 *     ---------------------------------------------------------
 *
 * We have already controlled 8 LEDs however this does it in a slightly
 * different manner. Rather than using 8 pins we will use just three
 * and an additional chip.
 *
 *
 */

#include <Arduino.h>
#include <ShiftRegister.h>


//Pin Definitions
//The 74HC595 uses a serial communication
//link which has three pins
short data = 2;
short clock = 3;
short latch = 4;
const short pinCount = 8;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the three control pins to outputs
 */
void setup()
{
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
}

/*
 * loop() - this function will start after setup finishes and then repeat
 * we set which LEDs we want on then call a routine which sends the states to the 74HC595
 */
void loop()
{
  ShiftRegister<pinCount> shiftRegister(data, clock, latch);

  // off on off on off on off on
  shiftRegister.setState(B01010101);
  shiftRegister.writeState();
  delay(1000);

  shiftRegister.setPin(7, LOW);
  shiftRegister.setPin(6, HIGH);
  shiftRegister.setPin(5, LOW);
  shiftRegister.setPin(4, HIGH);
  shiftRegister.setPin(3, LOW);
  shiftRegister.setPin(2, HIGH);
  shiftRegister.setPin(1, LOW);
  shiftRegister.setPin(0, HIGH);
  shiftRegister.writeState();
  delay(1000);

  // on off on off on off on off
  shiftRegister.setState(B10101010);
  shiftRegister.writeState();
  delay(1000);

  shiftRegister.setPin(7, HIGH);
  shiftRegister.setPin(6, LOW);
  shiftRegister.setPin(5, HIGH);
  shiftRegister.setPin(4, LOW);
  shiftRegister.setPin(3, HIGH);
  shiftRegister.setPin(2, LOW);
  shiftRegister.setPin(1, HIGH);
  shiftRegister.setPin(0, LOW);
  shiftRegister.writeState();
  delay(1000);

  short delayTime = 100;

  // Count backwards from 255 to 0.
  for (byte i = B11111111 ; i >= B00000000; i--) {
    shiftRegister.setState(i);
    shiftRegister.writeState();
    delay(delayTime);
  }

  // Count forwards from 0 to 255.
  for (byte i = B11111111; i >= B00000000; i--) {
    shiftRegister.setState(i);
    shiftRegister.writeState();
    delay(delayTime);
  }
}

