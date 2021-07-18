/***************************************************************************************
  To use this sketch you must install the TTN ESP32 BLE Provisioning APP from gGoogle Play
  https://play.google.com/store/apps/details?id=org.rgot.BLE_TEST
  this program was tested with heltech boards (Heltec Wifi Lora 32 & Heltec Wireless Stick)

  When running press the user button (named PROG on board)  the on board Led Light 
  and the Bluetooth Low Energy (BLE) is power on.
  On the Android application you can see a new device named "RGOT_xxx" where xxx is the hardware devEui.

  When you tap on this device, you can complete a form with devEUI, AppEui and AppKey.
  On the keyboard press Save (enter) to save the parameter.
  When finish press the back arrow, then the esp32 board reboot and take your new parameters.

*/

///////////////////////////////////////////////////////////////////////////////////////////
//     ___  _   _ ___ ___  _   _
//    / _ \| | | |_ _/ _ \| | | |
//   | | | | |_| || | | | | |_| |
//   | |_| |  _  || | |_| |  _  |
//    \___/|_| |_|___\___/|_| |_|
//   R   E   S   E   A   R   C   H
///////////////////////////////////////////////////////////////////////////////////////////
//  Author: Tjark Ziehm
//  Licinse: MIT
//  created:
//  code:
//  implemented Sensors:
//  sensirion: https://www.sensirion.com/en/environmental-sensors/particulate-matter-sensors-pm25/
//  Database: couchDB
///////////////////////////////////////////////////////////////////////////////////////////
//
//  TODO:
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////
//  When running press the user button (named PROG on board)  the on board Led Light
//  and the Bluetooth Low Energy (BLE) is power on.
//  On the Android application you can see a new device named "RGOT_xxx" where xxx is the hardware devEui.
///////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <TTN_BLE_esp32.h>
#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"
//#include "messurment.h"
#include <iostream>
#include <string>
#include <Wire.h>
#include "I2C.h"
#include "I2CScanner.h"
#include "CJMCU811.h"

// wireless stick pinout LoraWan
#define UNUSED_PIN 0xFF
#define SS 18       // LoRa_CS
#define RST_LoRa 16 // OLED_RST
#define DIO0 26     // LoRa_DIO0
#define DIO1 35     // LoRa_DIO1
#define DIO2 34     // LoRa_DIO2
#define LED 25

//#define uint8_t payloadSensor[0];

///////////////////////////////////////////////////////////////////////////////////////////

// wireless stick pinout
// pin 22 = SCL / Feinstaub
// pin 23 = SDA / Feinstaub
// pin = 2 Temp/Humidity/PRessure
// pin 22 && 23 Gas Channel

///////////////////////////////////////////////////////////////////////////////////////////

#define INTERVAL 30000
TTN_esp32 ttn;
TTN_BLE_esp32 ble;
TTN_CayenneLPP lpp;

///////////////////////////////////////////////////////////////////////////////////////////
/*
void message(const uint8_t* payload, size_t size, int rssi)
{
    Serial.println("-- MESSAGE");
    Serial.print("Received " + String(size) + " bytes RSSI= " + String(rssi) + "dB");

    for (int i = 0; i < size; i++)
    {
        Serial.print(" " + String(payload[i]));
        // Serial.write(payload[i]);
    }

    Serial.println();
}
*/
///////////////////////////////////////////////////////////////////////////////////////////
/*

Serial.println("joining");

    String word = "Device joined";
    int wordSize = sizeof(word);
    uint8_t payload[wordSize];

    
    while (payload[x] =! '\0')
    {
      payload[x] = word[x];

    }
    
    // TODO: write in loop
    payload[0] = word[0];
    payload[1] = word[1];
    payload[2] = word[2];
    payload[3] = word[3];
    payload[4] = word[4];
    payload[5] = word[5];
    payload[6] = word[6];
    payload[7] = word[7];
    payload[8] = word[8];
    payload[9] = word[9];
    payload[10] = word[10];
    payload[11] = word[11];
    payload[12] = word[12];
    payload[13] = word[13];

    ttn.sendBytes(payload,sizeof(word));
  void createPayLoadArray()
  {
  uint8_t payload[13];

  byte temperatur = 0;
  byte humidity = 0;
  byte pressure = 0;
  byte pm1 = 0;
  byte pm2 = 0;
  byte pm4 = 0;
  byte pm5 = 0;
  byte pm10 = 0;
  byte averagePM = 0;
  byte numberOfPM1 = 0; 
  byte numberOfPM2 = 0;
  byte numberOfPM4 = 0;
  byte numberOfPM5 = 0;
  byte numberOfPM10 = 0;

  payload[0] = temperatur;
  payload[1] = humidity;
  payload[2] = pressure;
  payload[3] = pm1;
  payload[4] = pm2;
  payload[5] = pm4;
  payload[6] = pm5;
  payload[7] = pm10;
  payload[8] = averagePM;
  payload[9] = numberOfPM1;
  payload[10] = numberOfPM2;
  payload[11] = numberOfPM4;
  payload[12] = numberOfPM5;
  payload[13] = numberOfPM10;
  
  LMIC_setTxData2(1, payload, sizeof(payload), 0);
  Serial.println("Package added to the array");
  }

*/
///////////////////////////////////////////////////////////////////////////////////////////
/*
uint wordArray [11];
void convertToASCII(string letter)
{
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        wordArray[i] = x;
    }
}
*/
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
void receiveEvent(int anzahl)
{
  while (Wire.available())
  {
    Wire.read();
  }

  digitalWrite(23, !digitalRead(23));
}

///////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  /*
  Serial.begin(115200);
  // I2C Slave:
  pinMode(23, OUTPUT);

  Wire.begin(23, 22, 1);
  Wire.onReceive(receiveEvent);
  */
  //setupI2CScanner();
  setupCJMCU811();
  //setupMessurment();

  // I2C Master:
  /*
  Serial.println("I2C Übertragung gestartet.");
  setupI2C_Master();
  Serial.println("I2C Übertragung abgeschlossen.");
  */
  //Serial.println(payloadSensor[0]);

  /*
	ttn.begin();
  // ttn.onMessage(message);
	if (ttn.restoreKeys()) {// provisioning with restored key from NVS
    Serial.println("Device information:" );
		Serial.println("appEui : "+ ttn.getAppEui());
    Serial.println("devEui : "+ ttn.getDevEui());		
    Serial.println("appEui : "+ ttn.getFrequency());
    Serial.println("appEui : "+ ttn.getDatarate());
    Serial.println("appEui : "+ ttn.getFrameCounter());
    Serial.println("appEui : "+ ttn.getPort());
    Serial.println("appEui : "+ ttn.getTXPower());
    Serial.println("------------------------------------");
		ttn.join();
		
	}
	else
	{
		Serial.println("No key are provisioned, please press the User Button\n\
                    then launch the \'TTN ESP32 Prosioning\' Android App \n\
                    Select the RGOT_... device and provisioning the keys\n\
                    Quit the android App, then the esp32 restart...	");
	}
	pinMode(KEY_BUILTIN, INPUT);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
  */
}

///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  //loopI2CScanner();
  loopCJMCU811();
  //I2C-Master Code:
  //Serial.println("I2C Übertragung loop gestartet.");
  //loopI2C();
  //Serial.println("I2C Übertragung loop abgeschlossen.");
  /*
  static bool jonction = false;
	static float nb = 0.0;
	static unsigned previoumillis = 0;
	if (!digitalRead(KEY_BUILTIN) && !ble.getInitialized())
	{
		ttn.stop();
		ble.begin();			
			digitalWrite(LED, HIGH);	
		while (!digitalRead(KEY_BUILTIN));
			
	}
	
	if (ttn.isJoined())
	{
		if (!jonction)
		{
			ttn.showStatus();
			jonction = true;
		}
		if (millis() - previoumillis > INTERVAL)
		{
			if (ttn.isRunning())
			{
			nb += 0.1;
			lpp.reset();
      // int number = loopMessurment

			lpp.addTemperature(1, nb);
      lpp.addDigitalInput(2,nb);
      
			if (ttn.sendBytes(lpp.getBuffer(), lpp.getSize(), 1, 1)) {
				Serial.printf("erfolgreich gesendet : %d %x %02X%02X\n", lpp.getBuffer()[0], lpp.getBuffer()[1], lpp.getBuffer()[2], lpp.getBuffer()[3]);
			}
			}
			
			previoumillis = millis();
		}
	}
	else {
		if (ttn.isRunning())
		{
			Serial.print(".");
			delay(500);
		}
			
		}	   

    */
}