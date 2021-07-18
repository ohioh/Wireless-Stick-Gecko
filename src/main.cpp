#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <esp32-hal-uart.h>

#include <Sensors.hpp>
#include "sensirion_arch_config.h"
#include <sensirion_uart.h>
#include <sps30.h>
#include <wiring_private.h> // pinPeripheral() function

#define DHTPIN 18
#define led 25
#define LEDR 17
#define LEDG 12
#define LEDB 13
#define SELPIN 33
#define DHTTYPE DHT22
#define BAUDRATE 115200 // baud rate of SPS30
#define PIN_UART_RX 11
#define PIN_UART_TX 10

Adafruit_SGP30 sgp;
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
uint64_t counter = 0;

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity)
{
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity);                                                                // [mg/m^3]
    return absoluteHumidityScaled;
}

Uart Serial2(&sercom1, PIN_UART_RX, PIN_UART_TX, SERCOM_RX_PAD_0,
             UART_TX_PAD_2);

void SERCOM1_Handler()
{
    Serial2.IrqHandler();
}

int16_t sensirion_uart_select_port(uint8_t port)
{
    return 0;
}

int16_t sensirion_uart_open()
{
    Serial2.begin(BAUDRATE);
    pinPeripheral(PIN_UART_TX, PIO_SERCOM);
    pinPeripheral(PIN_UART_RX, PIO_SERCOM);

    while (!Serial)
    {
        delay(100);
    }
    return 0;
}

int16_t sensirion_uart_close()
{
    Serial2.end();
    return 0;
}

int16_t sensirion_uart_tx(uint16_t data_len, const uint8_t *data)
{
    return Serial2.write(data, data_len);
}

int16_t sensirion_uart_rx(uint16_t max_data_len, uint8_t *data)
{
    int16_t i = 0;

    while (Serial2.available() > 0 && i < max_data_len)
    {
        data[i] = (uint8_t)Serial2.read();
        i++;
    }

    return i;
}

void sensirion_sleep_usec(uint32_t useconds)
{
    delay((useconds / 1000) + 1);
}

int anzahlMessungen = 0;

void messureTemperatur()
{
    dht.begin();
    sensor_t sensor;
    delayMS = sensor.min_delay / 1000;
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
        Serial.println(F("Error reading temperature!"));
    }
    else
    {
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
        Serial.println(F("------------------------------------"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
        Serial.println(F("Error reading humidity!"));
    }
    else
    {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
        Serial.println(F("------------------------------------"));
    }
    delay(2000);
}

void messureCO2()
{
    if (!sgp.begin())
    {
        Serial.println("Sensor not found :(");
        while (1)
            ;
    }

    // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
    //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
    // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
    //float temperature = 22.1; // [°C]
    //float humidity = 45.2; // [%RH]
    //sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

    if (!sgp.IAQmeasure())
    {
        Serial.println("Measurement failed");
        return;
    }
    Serial.print("TVOC ");
    Serial.print(sgp.TVOC);
    Serial.print(" ppb\t");
    Serial.print("eCO2 ");
    Serial.print(sgp.eCO2);
    Serial.println(" ppm");

    if (!sgp.IAQmeasureRaw())
    {
        Serial.println("Raw Measurement failed");
        return;
    }
    Serial.print("Raw H2 ");
    Serial.print(sgp.rawH2);
    Serial.print(" \t");
    Serial.print("Raw Ethanol ");
    Serial.print(sgp.rawEthanol);
    Serial.println("");
    Serial.println(F("------------------------------------"));
    delay(2000);
}

void setLEDR()
{
    /* code */
    pinMode(LEDR, OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(LEDR, HIGH);
    delay(1000);
    digitalWrite(LEDR, LOW);
}

void setLEDG()
{
    /* code */
    pinMode(LEDG, OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(LEDG, HIGH);
    delay(1000);
    digitalWrite(LEDG, LOW);
}

void setLEDB()
{
    /* code */
    pinMode(LEDB, OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(LEDB, HIGH);
    delay(1000);
    digitalWrite(LEDB, LOW);
}

void blinkingLED()
{
    /* code */
    pinMode(led, OUTPUT);
    // put your main code here, to run repeatedly:
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
    delay(2000);
}

void onSensorDataOk()
{
    Serial.print("-->[MAIN] PM1.0: " + sensors.getStringPM1());
    Serial.print(" PM2.5: " + sensors.getStringPM25());
    Serial.print(" PM10: " + sensors.getStringPM10());
    Serial.print(" PM1: " + sensors.getStringPM1());
}

void onSensorDataError(const char *msg)
{
    Serial.println(msg);
}

void messurePM()
{
    Serial.println("Start messure sps30.");

    sensors.setSampleTime(5);                       // config sensors sample time interval
    sensors.setOnDataCallBack(&onSensorDataOk);     // all data read callback
    sensors.setOnErrorCallBack(&onSensorDataError); // [optional] error callback
    delay(500);
    Serial.println("wakeup sensirion...");
    sensors.sps30.wakeup();
    delay(1000);
    sensors.loop(); // read sensor data and showed it
    delay(1000);
    sensors.sps30.sleep();
    counter++;
}

void messureSPS30()
{
}

void setup()
{
    Serial.begin(115200);
    //sensors.init(sensors.Sensirion);
    while (!Serial)
    {
        delay(10);
    } // Wait for serial console to open!
    setLEDR();
    blinkingLED();
    setLEDG();
    blinkingLED();
    setLEDB();
    blinkingLED();
    sensors.init(sensors.Sensirion);
    blinkingLED();
    blinkingLED();
    sensirion_uart_open();
    blinkingLED();
    delay(500);
    Serial.println("start to messure from the sensors:");
}

void loop()
{

    messureTemperatur();
    setLEDB();

    messureCO2();
    setLEDG();
    anzahlMessungen = anzahlMessungen + 1;
    delay(2000);
    messureSPS30();
    //messurePM();
    setLEDR();
    delay(2000);

    Serial.println(anzahlMessungen);
}
