#include <Arduino.h>

// Starting from top to bottom (first register: 0..7, second register: 8..16)
                        // Digit A, B, C, D, E, F, G, DP
                        // A  B   C    D    E   F   G    DP
byte shift_map_digits[] = {2, 6, 8+3, 8+5, 8+6, 3, 8+2, 8+4}; //shift pins 0, 7, 8+0, 8+8 not in use
                        // Segment 1, 2, 3, 4
byte shift_map_segments[] = {1, 4, 5, 8+1};

#define SHIFT_PIN_STCP 10
#define SHIFT_PIN_SHCP 11
#define SHIFT_PIN_DS   12

class Base {
public:
  virtual void printBase();
  void print();
};

class Child:public Base {
public:
  virtual void printBase();
};

void Base::print() {
  printBase();
}

void Base::printBase() {
  Serial.println("BASE");
}
void Child::printBase() {
  Serial.println("CHILD");
}

Base base = Base();
Base *pBase = new Base();
Child child = Child();
Child *pChild = new Child();

void setup() {
  Serial.begin(115200);
  base.print();
  pBase->print();
  child.print();
  pChild->print();
}

void loop() {
}