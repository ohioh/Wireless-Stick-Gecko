#include <WiFi.h>
#include <NetBios.h>


const char* ssid = "TP-Link_2G";
const char* password = "Test1234!";

void setupNetBIOS() {
  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /*NBNS.begin("ESP");*/
}
