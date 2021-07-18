#include <Wire.h>
#include <Arduino.h>
using namespace std;

class I2C_Test
{
    /////////////////////////////////////////////////////////////////////////////////////
public:
    I2C_Test();
    static int getAnzahl();
    // statische Membermethode kann auf nur
    // statische Membervariablen zugreifen

private:
    static int anzahl;
};

// Initialisierung der statischen Membervariablen
int I2C_Test::anzahl = 0;

I2C_Test::I2C_Test()
{
    anzahl = 4;
}

int I2C_Test::getAnzahl()
{
    return anzahl;
}
///////////////////////////////////////////////////////////////////////////////////////////

/*
int main(){

}
*/

///////////////////////////////////////////////////////////////////////////////////////////

// Slave Recieve Code
/*
void receiveI2C()
{

    bool check = Wire.available();

    Serial.println("[Slave]:heck i2C:");

    if (check)
        Serial.println("[Slave]:Wire avaible.");
    else
        Serial.println("[Slave]:Wire not avaible");

    while (check == 1)
    {
        Wire.read();
    };

    Serial.println("[Slave]:Wire read.");
    //digitalWrite(21, !digitalRead(21));
    pinMode(LED_BUILTIN, HIGH);
};

void setupI2C_Slave()
{
    pinMode(LED_BUILTIN, LOW);
    Serial.println("[Slave]:Recieve package can start.");
    Wire.begin(42);
    //Wire.onReceive(receiveI2C);
};
*/
///////////////////////////////////////////////////////////////////////////////////////////

// Master
void setupI2C_Master()
{
    Wire.begin();
    Serial.println("[Master]:Begin Wire i2C.");
};

void loopI2C_Master()
{
    Serial.println("[Master]:Send via i2C.");
    Wire.beginTransmission(42);
    Wire.write(0);
    boolean allesgut = Wire.endTransmission();
    Serial.println("[Master]:i2C transger done.");
    delay(1000);
};
