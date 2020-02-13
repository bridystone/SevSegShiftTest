#include <Arduino.h>
#include <SevSegShift.h>

// creating the Instances of the Objects
/*
  SevSeg Original
  */
// DIGIT PINS = specifying one of the 4 digits
uint8_t digit_pins[] = {A5, A2, A1, 5};
const int size_of_digit_pins = sizeof(digit_pins) / sizeof(digit_pins[0]);
// representing the actual Segement PINs
uint8_t segment_pins[] = {A4, A0, 3, 1, 0, A3, 4, 2};

/*
  SevSegShift information 
  */
#define NUM_OF_DIGITS 4
// Starting from top to bottom (first register: 0..7, second register: 8..16)
// Segment-Ports of Shift register(s) A, B, C, D, E, F, G, DP
                           // A    B   C  D  E   F   G   DP
byte shift_map_segments[] = {8+3, 8+7, 4, 6, 7, 8+4, 3,  5}; //shift pins 0, 7, 8+0, 8+8 not in use
// Digits-Ports of Shift Register(s) 1, 2, 3, 4
byte shift_map_digits[NUM_OF_DIGITS] = {8+2, 8+5, 8+6, 2};

#define SHIFT_PIN_DS   10
#define SHIFT_PIN_STCP 11
#define SHIFT_PIN_SHCP 12


SevSeg sevseg;
SevSegShift sevsegshift(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP);

void setup() {
  //Serial.begin(115200); // interferes with Display ... :()

  // prepare sevseg
  sevseg.begin(COMMON_CATHODE, size_of_digit_pins, digit_pins, segment_pins);
  sevseg.setBrightness(-100);

  // prepare sevsegshift
  sevsegshift.begin(
    COMMON_CATHODE,
    NUM_OF_DIGITS,
    shift_map_digits,
    shift_map_segments
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
    sevseg.setNumber(deciSeconds, 1);
    sevsegshift.setNumber(deciSeconds, 1);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
  sevsegshift.refreshDisplay(); // Must run repeatedly
}

