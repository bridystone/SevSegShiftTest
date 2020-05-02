#include <Arduino.h>
#include <SevSegShift.h>

// DIGIT PINS = specifying one of the 4 digits
uint8_t digit_pins[] = {4, 5, 6, 7}; // These are the PINS of the Arduino
const int size_of_digit_pins = sizeof(digit_pins) / sizeof(digit_pins[0]);
// representing the actual Segement PINs
                      //  A  B  C  D  E  F  G  DP
uint8_t segment_pins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // these are the PINs of the Shift register

/*
  SevSegShift information 
  */
#define NUM_OF_DIGITS 4

#define SHIFT_PIN_DS   8
#define SHIFT_PIN_STCP 9
#define SHIFT_PIN_SHCP 10

SevSegShift sevsegshift(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);

void setup() {

  // prepare sevsegshift
  sevsegshift.begin(
    COMMON_CATHODE,
    NUM_OF_DIGITS,
    digit_pins,
    segment_pins
  );
  sevsegshift.setBrightness(-100); 
}

/****************************/
/* loop copied from example */
/****************************/
void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  if (millis() - timer >= 100) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond

    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevsegshift.setNumber(deciSeconds, 1);
  }
  sevsegshift.refreshDisplay(); // Must run repeatedly
}

