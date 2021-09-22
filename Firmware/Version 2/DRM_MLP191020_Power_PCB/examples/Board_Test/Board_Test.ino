/*
    A simple library demo thatat reads an MLP191020 - 1-channel CT sesnor boards
    Based On:   EmonLib https://github.com/openenergymonitor/EmonLib
    Auther:     David Mottram
    Updated:    22nd September 2021
*/

#include <ESP8266WiFi.h>              // needed for EPS8266
#include <WiFiClient.h>               // WiFi client

// I/O items
#define Network_LED 2

// library for the MLP191020 PCB
#define Cal_value 1500

// values for reporting
#define Voltage 230
#define CT_Cal 17.619
#define Min_Usable_Value 0.3
#define Reporting_Delay 500

// https://github.com/Mottramlabs/MQTT-Power-Sensor
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

  // calc Amps, zero the value if below usable value
  float Amps = Value / CT_Cal;

  // if below min usable value then zero
  if (Value < Min_Usable_Value) {
    Amps = 0;
  } // end if

  int Watts = Amps * Voltage;

  // display report
  Serial.print("Value: "); Serial.print(Value); Serial.print(" - Amps: "); Serial.print(Amps); Serial.print("A - Watts: "); Serial.print(Watts); Serial.print("W");
  Serial.println("");

  // flash the LED
  digitalWrite(Network_LED, HIGH); delay(10); digitalWrite(Network_LED, LOW);

  delay(Reporting_Delay);

} // end of loop
