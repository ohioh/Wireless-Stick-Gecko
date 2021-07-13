
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
*/
/*Tasks and Workload
  TODO: 

*/

#include <Arduino.h>
#include <SPI.h>
#include <own/blinkLED.h>
#include <own/getChipID.h>
#include <own/LEDCSoftwareFade.h>
#include <own/eeprom_class.h>
#include <own/eeprom_write.h>
#include <own/deepSleepMode.h>
#include <getNetBIOS.h>
#include <own/startFreeRTOS.h>
#include <own/getTime.h>
#include <own/LoRa.h>



void setup() {

  Serial.begin(115200);
  /*
  blinkingLED(50,1000);  
  blinkingLED(150,1000);  
  blinkingLED(250,1000);  
  blinkingLED(500,1000);  
  getChipID(); 
  setupNetBIOS();  
  setupGetTime(); 
  startEEPROM_Class();
  startEEPROM_Write();
  setupFreeRTOS();
  */
  getChipID(); 
  setupLoRa();

  // set variables for the sensordata
  


  
}

void loop() {

  /*
  blinkingLED(100, 100);
  startFader();
  loopEEPROM_Write();
  setupDeepSleep();
  */
  char16_t data[] = hello; // or "z\u00df\u6c34\U0001f34c"
  loopLoRaDataDigital(data);

  
}
