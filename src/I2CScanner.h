/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Arduino.h>

void setupI2CScanner()
{
    Serial.begin(115200);
    Serial.println("I2C basic SCL Pin:");
    Serial.println(SCL);
    Serial.println("I2C basic SDA Pin:");
    Serial.println(SDA);
    Serial.println("\nI2C Scanner");
    Wire.begin(22, 23, 400000);

    Serial.println("\nI2C Scanner");
}

void loopI2CScanner()
{
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknow error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("done\n");
    }
    delay(5000);
}
