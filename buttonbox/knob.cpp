#include "Arduino.h"
#include "knob.h"

Knob::Knob(int pin0, int pin1, int cw, int ccw) {
  //Serial.println("Knob constructor");
  knob = new Encoder(pin0, pin1); // might need to delete this pointer?
  position = 0;
  cw_button = cw;
  ccw_button = ccw;
}

int Knob::read(void) {
  long new_position;
  new_position = knob->read();
  if (new_position != position) {
    if (new_position > position) {
      // turning cw
      //Serial.println("CW");
      position = new_position;
      return 1;
    } else if (new_position < position) {
      // turning ccw
      //Serial.println("CCW");
      position = new_position;
      return -1;
    }
  }

  return 0;
}
