##########################################################################
/*
                       ___  _   _ ___ ___  _   _ 
                     / _ \| | | |_ _/ _ \| | | |
                    | | | | |_| || | | | | |_| |
                    | |_| |  _  || | |_| |  _  |
                     \___/|_| |_|___\___/|_| |_|
                    R   E   S   E   A   R   C   H
Name: main.cpp
Creator: Tjark Ziehm
Board: Heltec Wireless Stick
homepage: https://ohioh.de, https://github.com/ohioh/Wireless-Stick-Gecko
device: https://heltec.org/project/wireless-stick/
Pin-Out: https://resource.heltec.cn/download/Wireless_Stick/Wireless_Stick.pdf
License:MIT
Version: 0.9
Date: 11.07.2021
Task: Handle multicore processing to messure plugged in sensors and send
      via LoRaWan to TTN Network-Backend
*/##########################################################################
/*Tasks and Workload

*/##############################-TODO-#######################################
/*
  TODO: 

*/############################################################################

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
#include "LoRa.h"

############################################################################

############################################################################

void setup() {

  Serial.begin(115200);
  blinkingLED(50,1000);  
  blinkingLED(150,1000);  
  blinkingLED(250,1000);  
  blinkingLED(500,1000);  
  getChipID(); 
  setupNetBIOS();  
  setupGetTime();  
  /*startEEPROM_Class();*/
  /*startEEPROM_Write();*/
  /*setupFreeRTOS();*/
  
}
############################################################################

############################################################################
void loop() {

  /*blinkingLED(100, 100);"""*/
  /*startFader();*/
  /*loopEEPROM_Write();*/
  /*setupDeepSleep();*/
  
}
############################################################################