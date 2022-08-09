#include <Encoder.h>
#include <Joystick.h>
#include <Keypad.h>

#include "knob.h"

//keypad


const byte NUMROWS = 5; //four rows
const byte NUMCOLS = 5; //three columns
byte keys[NUMROWS][NUMCOLS] = {
  {0, 1, 2, 3, 4},
  {5, 6, 7, 8, 9},
  {10, 11, 12, 13, 14},
  {15, 16, 17, 18, 19},
  {20, 21, 22, 23},
};
byte rowPins[NUMROWS] = {8, 9, 10, 16, 14}; //connect to the row pinouts of the keypad
byte colPins[NUMCOLS] = {15, 18, 19, 20, 21}; //connect to the column pinouts of the keypad
Keypad buttbx = Keypad(makeKeymap(keys), rowPins, colPins, NUMROWS, NUMCOLS);

// Encoder setup
const int NUMENCODERS = 3; // number of encoders
Knob knobs[NUMENCODERS] = {
  Knob(3, 2, 24, 25),
  Knob(4, 5, 26, 27),
  Knob(6, 7, 28, 29)
};


// Create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   30, 0, // Button Count, Hat Switch Count
                   false, false, false, // no X, Y and Z Axis
                   false, false, false, // No Rx, Ry, or Rz
                   false, false, // No rudder or throttle
                   false, false, false); // No accelerator, brake, or steering

void setup() {
  //init serial port
  //Serial.begin(115200);
  delay(250);
  //Initialize Joystick Library
  Joystick.begin();
  //Serial.println("Encoder test");
}

void loop() {
  CheckAllButtons();
  CheckAllEncoders();
  delay(100);
}

void CheckAllEncoders(void) {
  for (int ii = 0; ii < NUMENCODERS; ii++) {
    int button = knobs[ii].read();
    if (button == 0) {
      Joystick.setButton(knobs[ii].cw_button, 0);
      Joystick.setButton(knobs[ii].ccw_button, 0);
    } else if (button > 0 ) {
      Joystick.setButton(knobs[ii].cw_button, 1);
    } else if (button < 0 ) {
      Joystick.setButton(knobs[ii].ccw_button, 1);
    }
  }
}

void CheckAllButtons(void) {
  if (buttbx.getKeys()) {
    for (int ii = 0; ii < LIST_MAX; ii++) {
      if (buttbx.key[ii].stateChanged) {
        //Serial.print((int) buttbx.key[ii].kchar);
        switch (buttbx.key[ii].kstate) {
          case HOLD:
          case PRESSED:
            //Serial.println(" pressed");
            Joystick.setButton(buttbx.key[ii].kchar, 1);
            break;
          case RELEASED:
          case IDLE:
            //Serial.println(" released");
            Joystick.setButton(buttbx.key[ii].kchar, 0);
            break;

        }
      }
    }
  }
}
