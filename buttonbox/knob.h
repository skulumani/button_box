#ifndef KNOB_H
#define KNOB_H
#include "Arduino.h"
#include <Encoder.h>

class Knob {
  public:
    Knob(int pin0, int pin1, int cw, int ccw);
    Knob(void) {};
    
    int read(void);

    long position;
    int cw_button;
    int ccw_button;
    Encoder* knob;
  private:
};

#endif
