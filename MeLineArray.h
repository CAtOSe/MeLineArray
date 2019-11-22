/*
  MeLineArray.h - Library for reading Makeblock Line Array
  Created by Paulius Jasėnas, September 27, 2019.
  Released into the public domain.
*/
#ifndef MeLineArray_h
#define MeLineArray_h

#include "Arduino.h"

class LineArray
{
  public:
    LineArray(int pin);
    uint8_t getData();
  private:
    int _pin;
    uint8_t _Sensor_Data[3];
};



#endif