/*
  MeLineArrayJBG.cpp - Library for reading Makeblock Line Array.
  Created by Paulius Jasėnas, September 27, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MeLineArray.h"

LineArray::LineArray(int pin) {
	pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
	_pin = pin;
}

uint8_t LineArray::getData() {  
    long time_out_flag = 0;

    // set the pin mode to output and set the pin value to LOW
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);

    // wait .98 seconds then set the pin value to HIGH
    delayMicroseconds(980);
    digitalWrite(_pin, HIGH);

    // wait 40 ms
    delayMicroseconds(40);

    // set the pin to a known good pullup value for a baseline
    pinMode(_pin, INPUT_PULLUP);

    // wait 50 ms
    delayMicroseconds(50); 

    // prepare a non-blocking timer
    time_out_flag = millis();

    // get the pin value
    while((digitalRead(_pin) == 0)&&((millis() - time_out_flag) < 6)); 
    time_out_flag = millis();

    // get another reading for the pin value
    while((digitalRead(_pin) == 1)&&((millis() - time_out_flag) < 6));

    
    for(uint8_t k=0; k<3; k++)
    {
        // zero out the array element
        _Sensor_Data[k] = 0x00;
        
        for(uint8_t i=0;i<8;i++)
        {
            // set the timeout flag
            time_out_flag = millis(); 

            // wait for 6 ms (non-blocking)
            while(digitalRead(_pin) == 0&&((millis() - time_out_flag) < 6));

            // get the current time in microseconds
            uint32_t HIGH_level_read_time = micros();

            // reset the timeout flag
            time_out_flag = millis();

            // wait for 6ms (non-blocking) 
            while(digitalRead(_pin) == 1&&((millis() - time_out_flag) < 6));

            // get the elapsed interval in microseconds
            HIGH_level_read_time = micros() - HIGH_level_read_time;

            // if the elapsed time is between 50-100 microseconds
            if(HIGH_level_read_time > 50 && HIGH_level_read_time < 100)  
            {
                // 'or' the value into the array element using
                // a right shift by the current loop counter value
                _Sensor_Data[k] |= (0x80 >> i);
            }
        }
    }

    // test to see whether the value of array element one is the 
    // same as the negated value of array element zero.
    if (_Sensor_Data[1] == (uint8_t)(~(uint8_t)_Sensor_Data[0]))
    {
       // if the values are the same return the value of array element zero
       return _Sensor_Data[0];
    }
}