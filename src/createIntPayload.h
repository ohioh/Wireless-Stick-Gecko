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

#include <Arduino.h>
#include <TTN_esp32.h>
#include "TTN_CayenneLPP.h"


///////////////////////////////////////////////////////////////////////////////////////////
// 4-Bits
void  message1() {

    uint8_t payload[0];
    int var = 54321;

    payload[0] = var;   

    LMIC_setTxData2(0, payload, sizeof(payload),0);
    Serial.println("Package added.");
}
///////////////////////////////////////////////////////////////////////////////////////////
// 8-Bits
void  message2() {

    uint8_t payload[1];
    int var = 54321;

    payload[0] = var >> 8;
    payload[1] = var;

    LMIC_setTxData2(1, payload, sizeof(payload),0);
    Serial.println("Package added.");
}
///////////////////////////////////////////////////////////////////////////////////////////
// 16-bit long var example: 1234567890
void  message4() {
    uint8_t payload[1];
    long var = 1234567890;

    payload[0] = var >> 24 ;
    payload[1] = var >> 16;
    payload[2] = var >> 8;
    payload[2] = var;

    LMIC_setTxData2(3, payload, sizeof(payload),0);
    Serial.println("Package added.");
}

///////////////////////////////////////////////////////////////////////////////////////////
// 64-bit
void  message8() {
    uint8_t payload[1];
    int var = 54321;

    payload[0] = var >> 8;
    payload[1] = var;

    LMIC_setTxData2(1, payload, sizeof(payload),0);
    Serial.println("Package added.");
}

///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
// Send message
void sendMessage(const uint8_t* payload, size_t size, int rssi)
{
    uint8_t payload[0];

    Serial.println("-- MESSAGE");
    Serial.print("Received " + String(size) + " bytes RSSI= " + String(rssi) + "dB");

    for (int i = 0; i < size; i++)
    {
        Serial.print(" " + String(payload[i]));
        // Serial.write(payload[i]);
    }

    Serial.println();
}