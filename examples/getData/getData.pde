#include <MeLineArray.h>

LineArray lineArray(12);

/*
 * mBot Ports:
 * Port 1  ==  12
 * Port 2  ==  10
 * Port 3  ==  A3
 * Port 4  ==  A1
 */

void setup() 
{
    // open the serial port at 9600
    Serial.begin(9600);

    // wait one second
    delay(100);

    // print the start message to the serial monitor
    Serial.println("Start.....");
}

void loop()
{
    // print the value retrieved from the sensor
    Serial.print(millis());
    Serial.print(": ");
    Serial.println(lineArray.getData(), BIN);
    
}