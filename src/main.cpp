#include <Arduino.h>
#include <SevSegShift.h>

#define NUM_OF_DIGITS 4

#define SHIFT_PIN_SHCP 6
#define SHIFT_PIN_STCP 7
#define SHIFT_PIN_DS   8

// DIGIT PINS = specifying one of the 4 digits
uint8_t digit_pins[] = {5, 4, 3, 2}; // These are the PINS of the ** Arduino **
// representing the actual Segement PINs
                      //  A  B  C  D  E  F  G  DP
uint8_t segment_pins[] = {0, 2, 4, 6, 7, 1, 3, 5}; // these are the PINs of the ** Shift register **


SevSegShift sevsegshift(
                  SHIFT_PIN_DS, 
                  SHIFT_PIN_SHCP, 
                  SHIFT_PIN_STCP, 
                  1, /* number of shift registers there is only 1 Shiftregister 
                        used for all Segments (digits are on Controller)
                        default value = 2 (see SevSegShift example)
                        */
                  true /* Digits are connected to Arduino directly 
                          default value = false (see SevSegShift example)
                        */
                );

void setup() {

  // prepare sevsegshift
  sevsegshift.begin(
    COMMON_CATHODE,
    NUM_OF_DIGITS,
    digit_pins,
    segment_pins
  );
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

