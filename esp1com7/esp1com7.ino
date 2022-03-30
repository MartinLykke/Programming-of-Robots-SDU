#include "WiFi.h"
#include "ESPAsyncWebServer.h"

#include <Wire.h>


 // defines pins numbers
const int trigPin = 12;
const int echoPin = 14;
// defines variables
long duration;
int distance;
// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/


//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);



void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  Serial.println();

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

      // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  
  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "squakweee");
  });
  
  
  // Start server
  server.begin();
}
 
void loop(){
  
}
