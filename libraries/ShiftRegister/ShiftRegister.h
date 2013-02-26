
// ShiftRegister is a class to provide an easy interface for controlling shift
// registers. 

#ifndef ShiftRegister_h_included_
#define ShiftRegister_h_included_

#include <Arduino.h>

// DataType must be able to hold a maximum value of 2^PinCount-1
template<int PinCount, typename DataType>
class ShiftRegister
{
public:
  // :: ----------------------------------------------------
  // :: Constructor ----------------------------------------

  ShiftRegister(const short& data, const short& clock, const short& latch)
    : m_data(data)
    , m_clock(clock)
    , m_latch(latch)
    , m_state(0)
    , m_MAX(1)
  {
    for (DataType i = 0; i < PinCount; i++) m_MAX |= (1 << i);
  }

public:
  // :: ----------------------------------------------------
  // :: Interface ------------------------------------------

  // valid pin values are 0,1,2,...,7.
  void setPin(const short& pin, const short& pinState) {
    // Make sure that the input values are valid.
    // TODO: Add error handling.
    if (pin < 0 or pin > PinCount-1) return;
    if (not pinState == LOW or not pinState == HIGH) return;

    // Set the pin we are addressing to LOW.
    m_state = m_state & getMask(pin);

    // If the bit is set to HIGH turn it on.
    if (pinState == HIGH)
      m_state == pinState | getBit(pin);
  }

  // Override the current state with the given one.
  void setState(const DataType &state) { m_state = state; }

  // Write the current state out to the shift register.
  void writeState() {
    // Copy the current state to a temporary value
    DataType state = m_state;
    // Pulls the chips latch low
    digitalWrite(m_latch, LOW);

    // Will repeat once for each pin
    for(DataType i = 0; i < PinCount; i++) {
      // We use a "bitmask" to select only the highest
      // bit in our number (the one we are addressing this time through
      DataType bit = state & (1 << (PinCount - 1));

      // Shift the state by one so that the next value is in the highest bit
      // position.
      state = state << 1;

      // If the highest bit is set then set our data pin to HIGH otherwise set
      // it LOW.
      digitalWrite(m_data, bit ? HIGH : LOW);

      // The next three lines pulse the clock pin.
      digitalWrite(m_clock, HIGH);
      delay(1);
      digitalWrite(m_clock, LOW);
    }

    // Pulls the latch high shifting our data into being displayed.
    digitalWrite(m_latch, HIGH);
  }

  // Write the current state to the shift register using the built in shiftOut
  // function.
  void writeStateShort() {
    //Pulls the chips latch low
    digitalWrite(m_latch, LOW);
    //Shifts out the 8 bits to the shift register, shiftOut() will only shift of a
    //byte of data
    shiftOut(m_data, m_clock, MSBFIRST, m_state);
    //Pulls the latch high displaying the data
    digitalWrite(m_latch, HIGH);
  }

  DataType getBit(const DataType& pin) {
    DataType bit = 1;
    for (DataType i = 0; i < pin; i++) {
      bit = bit << 1;
    }
    return bit;
  }

  DataType getMask(const DataType& pin) {
    return getBit(pin) ^ m_MAX;
  }

private:
  // :: ----------------------------------------------------
  // :: Members --------------------------------------------

  short m_data;
  short m_clock;
  short m_latch;
  DataType m_state;
  DataType m_MAX;
};

#endif
