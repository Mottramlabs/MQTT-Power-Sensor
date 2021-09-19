/*
    variables and functions used by this project
*/


// Heatbeat items
#define Heartbeat_Range   99                      // event count max value
#define Heatbeat    1000                          // heartbeat timer value, in mS

// Watchdog items
volatile int Watchdog_Timout = 1200;              // time in seconds before watchdog times out, 1200 = 1200 seconds or 20 minutes

// Heatbeat timer
int Heart_Value = 0;                              // timer
long LastMsg = 0;                                 // message sent counter

// Custom default values
String WiFi_SSID = "None";                        // SSID string
String My_MAC = "";                               // MAC address, tobe read from ESP8266
char MAC_array[13] = "000000000000";              // MAC definition
String My_IP = "";                                // IP address

volatile int Report_Request = 0;                  // set to 1 if report required
String Mode = "Boot";                            // default message event


// ********************************************************************************************************
// ************************ project specific variables ****************************************************
// ********************************************************************************************************

// I/O and product variables
#define Network_LED 2

// MLP191020 and A/D items
double Value = 0;                   // array for results
#define Cal_value 1500

// ********************************************************************************************************
// ************************ watchdog items ****************************************************************
// ********************************************************************************************************

#include <Ticker.h>
Ticker secondTick;
volatile int watchdogCount = 0;

// watchdog timer function, watchdog is clear when the ststus report is requested by a GET request
void ISRwatchdog() {
  watchdogCount++;
  if (watchdogCount == Watchdog_Timout) {
    Serial.println();
    Serial.println("The watchdog bites !!!!!");
    ESP.reset();
  } // end of timeout test
} // end of watchdog count
