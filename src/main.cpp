#include <Arduino.h>
#include <SPI.h>
#include "blinkLED.h"
#include "getChipID.h"
#include "LEDCSoftwareFade.h"
#include "eeprom_class.h"
#include "eeprom_write.h"
#include "deepSleepMode.h"
#include "getNetBIOS.h"
#include "startFreeRTOS.h"
#include "getTime.h"
#include "LoRaWan.h"



void setup() {
  Serial.begin(115200);
  blinkingLED(50,1000);  
  blinkingLED(150,1000);  
  blinkingLED(250,1000);  
  blinkingLED(500,1000);  

  getChipID();  

  /*startEEPROM_Class();*/
  /*startEEPROM_Write();*/
  setupNetBIOS();
  /*setupFreeRTOS();*/
  setupGetTime();
  setupLoRaWan();
  
}

void loop() {
  /*blinkingLED(100, 100);"""*/
  /*startFader();*/
  /*loopEEPROM_Write();*/
  /*setupDeepSleep();*/
  loopLoRaWan();
  
}