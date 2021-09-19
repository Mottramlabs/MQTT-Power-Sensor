/*
  Basic CT test using a Wemos D1 Mini

  Based on this article https://www.the-diy-life.com/simple-arduino-home-energy-meter/
*/


#include <ESP8266WiFi.h>                      // Needed for EPS8266
#include <WiFiClient.h>                       // WiFi client

// I/O
#define Status_LED 2                          // D4
#define Status_LED_On   digitalWrite(Status_LED, HIGH)
#define Status_LED_Off  digitalWrite(Status_LED, LOW)

// Power monitor items
double Calib = 3.27;
double Kilos;
unsigned long StartMillis;
unsigned long EndMillis;
double RMSCurrent;
int RMSPower;
int PeakPower;
int LineVolts = 230;


void ReadPower ()      // Method to read information from the CT
{
  int Current = 0;
  int MaxCurrent = 0;
  int MinCurrent = 1023;
  int PeakCurrent = 0;

  // Needs to sample for at least one and half mains cycles or > 30mS
  for (int j = 0 ; j <= 600 ; j++)
  {

    Current =  analogRead(A0);    //Reads A/D input and records maximum and minimum current

//delayMicroseconds(100);

    if (Current >= MaxCurrent)
      MaxCurrent = Current;

    if (Current <= MinCurrent)
      MinCurrent = Current;

  } // End of samples loop

  PeakCurrent = MaxCurrent - MinCurrent;

  RMSCurrent = (PeakCurrent * 0.3535) / Calib; //Calculates RMS current based on maximum value and scales according to calibration
  RMSPower = LineVolts * RMSCurrent;  //Calculates RMS Power Assuming Voltage 240VAC, change to 110VAC accordingly

  // http://www.referencedesigner.com/rfcal/vrms-to-vpeak-conversion.php
  // RMSCurrent = (PeakCurrent * 0.3535) / Calib; //Calculates RMS current based on maximum value and scales according to calibration
  // RMSPower = 248 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 240VAC, change to 110VAC accordingly

} // End of function


void setup(void) {
  delay(500);

  Serial.begin(115200);
  Serial.println(""); Serial.println("Hello");

  pinMode(Status_LED, OUTPUT);                // Status LED
  Status_LED_On;

} // End of setup


void loop() {

 delay(500);

  ReadPower();
  Serial.print(RMSCurrent); Serial.print(" Amps  "); Serial.print(RMSPower); Serial.println(" W");

} // End of Loop
