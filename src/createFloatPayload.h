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
void message1(const uint8_t* payload, size_t size, int rssi)
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
///////////////////////////////////////////////////////////////////////////////////////////
void  message1() {
    uint8_t payload[1];
    int var = 54321;

    payload[0] = var >> 8;
    payload[1] = var;

    LMIC_setTxData2(1, payload, sizeof(payload),0);
    Serial.println("Package added.");
}
///////////////////////////////////////////////////////////////////////////////////////////
void  message4() {
    uint8_t payload[1];
    int var = 54321;

    payload[0] = var >> 8;
    payload[1] = var;

    LMIC_setTxData2(1, payload, sizeof(payload),0);
    Serial.println("Package added.");
}
///////////////////////////////////////////////////////////////////////////////////////////
void  message8() {
    uint8_t payload[1];
    int var = 54321;

    payload[0] = var >> 8;
    payload[1] = var;

    LMIC_setTxData2(1, payload, sizeof(payload),0);
    Serial.println("Package added.");
}
///////////////////////////////////////////////////////////////////////////////////////////