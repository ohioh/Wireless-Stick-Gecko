#include <Arduino.h>
#include <SPI.h>
#define led 25
  
int blinkingLED ()
{ 
    /* code */
    pinMode(led,OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);  
}
  
