/*
                       ___  _   _ ___ ___  _   _ 
                     / _ \| | | |_ _/ _ \| | | |
                    | | | | |_| || | | | | |_| |
                    | |_| |  _  || | |_| |  _  |
                     \___/|_| |_|___\___/|_| |_|
                    R   E   S   E   A   R   C   H
Name: LoRa.h
Creator: by Francois Riotte, edited by Tjark Ziehm
Board: Heltec Wireless Stick
homepage: https://ohioh.de, https://github.com/ohioh/Wireless-Stick-Gecko
device: https://heltec.org/project/wireless-stick/
License:MIT
Version: 0.9
Date: 11.07.2021
Task: 
*/
/*Tasks and Workload

*/
/*
  TODO: 


*/
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
#include "TTN_BLE_esp32.h"
#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"
#include "blinkLED.h"

// wireless stick pinout

// Intervall to repeat the sending process
// TODO: brint the interval as an given input
#define INTERVAL 30000

TTN_esp32 ttn;
TTN_BLE_esp32 ble;
TTN_CayenneLPP lpp;

void setupLoRa() {
	
    Serial.begin(115200);
    Serial.println("Starting");
	ttn.begin();

    // provisioning with restored key from NVS
	if (ttn.restoreKeys()) {
		Serial.println("devEui : "+ ttn.getDevEui());
		Serial.println("appEui : "+ ttn.getAppEui());
		ttn.join();
		Serial.println("joining");
	}
	else
	{
		Serial.println("No key are provisioned, please press the User Button\n\
                        then launch the \'TTN ESP32 Prosioning\' Android App \n\
                        Select the OHIOH_... device and provisioning the keys\n\
                        Quit the android App, then the esp32 restart...	");
	}
	pinMode(KEY_BUILTIN, INPUT);
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
}

/* Loop takes input to send via LoRaWan */
void loopLoRa() {

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
			
                /*adding the Temerature to the send Bytes*/
                lpp.reset();
			    lpp.addTemperature(1, nb);

			    if (ttn.sendBytes(lpp.getBuffer(), lpp.getSize(), 1, 1)) 
                {
				    Serial.printf("envoi reussi : %d %x %02X%02X\n", lpp.getBuffer()[0], lpp.getBuffer()[1], lpp.getBuffer()[2], lpp.getBuffer()[3]);
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

 }


/* Loop takes input to send via LoRaWan */
// The input float sensordata takes the information single time and send it to TTN Backend
//addDigitalInput(uint8_t channel, uint8_t value)
//addAnalogInput(uint8_t channel, float value)
void loopLoRaDataDigital(char16_t sensordata) {

	static bool jonction = false;
	static float data = sensordata;
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
			    
				/*get the data by function from the server or direct*/
				/* TODO: seperate time loop in main function */
			
                /*adding the Temerature to the send Bytes*/
                lpp.reset();
			    // lpp.addDigitalInput(1, data);
				lpp.addAnalogInput(1, data);

				digitalWrite(LED, HIGH);
				delay(500);

			    if (ttn.sendBytes(lpp.getBuffer(), lpp.getSize(), 1, 1)) 
                {
				    Serial.printf("Sent: %d %x %02X%02X\n", lpp.getBuffer()[0], lpp.getBuffer()[1], lpp.getBuffer()[2], lpp.getBuffer()[3]);
			    	digitalWrite(LED, LOW);
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

 }