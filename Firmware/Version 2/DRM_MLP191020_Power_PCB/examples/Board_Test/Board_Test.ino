/*
    A simple library demo thatat reads an MLP191020 - 1-channel CT sesnor boards
    Based On:   EmonLib https://github.com/openenergymonitor/EmonLib
    Auther:     David Mottram
    Updated:    4th September 2021
*/

#include <ESP8266WiFi.h>              // needed for EPS8266
#include <WiFiClient.h>               // WiFi client

// I/O items
#define Network_LED 2

// library for the MLP191020 PCB
#define Cal_value 1500
#include <MLP191020.h>
// make an instance of MLP191020
MLP191020 My_PCB(Cal_value);

double Value = 0;                     // result

void setup() {

  // start the serial connection
  Serial.begin(115200); Serial.println(""); Serial.println(""); Serial.println("Up and Clackin!");
  Serial.println(__FILE__);

  // setup I/O
  pinMode(Network_LED, OUTPUT); digitalWrite(Network_LED, HIGH);

} // end of setup


void loop() {

  // read A/D values and store in value
  Value = My_PCB.power_sample();

  // report results
  delay(200);

  // print the values
  digitalWrite(Network_LED, HIGH);

  String Report = String(Value) + "    ";
  Serial.println(Report);

  // only used to make the LED flash visable
  delay(10);

  digitalWrite(Network_LED, LOW);

  delay(1000);

} // end of loop
