#include <Arduino.h>
#include <SPI.h>
#define led 25
  
int blinkingLED(int timeOff, int timeOn)
{ 
    /* code */
    pinMode(led,OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);
    delay(timeOn);
    digitalWrite(led, LOW);
    delay(timeOff);  
}
  
