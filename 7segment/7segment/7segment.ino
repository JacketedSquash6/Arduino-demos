#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

const byte segments[6][4] 
{
  {
    B10000001,
    B00001001,
    B00000001,
    B00000010,
  },
  {
    B00000010,
    B10100100,
    B01000000,
    B00000100,
  },
  {
    B00000100,
    B00010010,
    B10001000,
    B01000000,
  },
  {
    B00001000,
    B00001001,
    B00001000,
    B10010000,
  },
  {
    B00010000,
    B00100100,
    B11000000,
    B00100000,
  },
  {
    B00100000,
    B10010010,
    B00000001,
    B01000000,
  }
};
int frame = 0;

void setup() {
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  sevseg.setSegments(segments[frame]);
  frame = (millis()/200)%6;
  sevseg.refreshDisplay(); // Must run repeatedly
}
