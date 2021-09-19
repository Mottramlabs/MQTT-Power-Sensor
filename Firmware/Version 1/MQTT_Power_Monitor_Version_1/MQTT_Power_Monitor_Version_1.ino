/*
  MQTT with ESP8266 and Power Monitor 5th December 2017
  David Mottram
  See Custom_Settings.h for Wifi and MQTT settings
*/

#include <ESP8266WiFi.h>                    // Needed for EPS8266
#include <WiFiClient.h>                     // WiFi client

// Watchdog items
#include <Ticker.h>
Ticker secondTick;
volatile int watchdogCount = 0;

#include "Custom_Settings.h"                // Custom and Wifi Connection and board details.

WiFiClient espClient;                       // For ESP8266 boards
#include <PubSubClient.h>                   // http://pubsubclient.knolleary.net/api.html
PubSubClient client(espClient);             // ESP pubsub client
#include "WiFi_Functions.h"                 // Read wifi datak
#include "MQTT_Functions.h"                 // MQTT Functions


// Watchdog timer, watchdog is clear when the ststus report is requested by a GET request
void ISRwatchdog() {
  watchdogCount++;
  if (watchdogCount == Watchdog_Timout) {
    Serial.println();
    Serial.println("The watchdog bites !!!!!");
    ESP.reset();
  } // end of timeout test
} // end of watchdog count


void setup(void) {
  delay(500);

  pinMode(Status_LED, OUTPUT);                // Status LED
  Status_LED_Off;

  secondTick.attach(1, ISRwatchdog);          // Start watchdog time

  Get_Wifi();                                 // Connect to WiFi, try upto 4 Access Points. This needs tobe very soone after reset!

  client.setServer(mqtt_server, 1883);        // Set the MQTT server and port
  client.setCallback(callback);               // MQTT callback

  LastMsg = millis();                         // Reset Heartbeat

} // End of setup


void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  // Headbeat or report requested
  if ((millis() - LastMsg) > Heatbeat || Report_Request == 1) {

    LastMsg = millis();
    Report_Request = 0;

    // Update event progress counter
    ++Heart_Value;
    if (Heart_Value > Heartbeat_Range) {
      Heart_Value = 1;
    }
    // Heartbeat timed out


    Status_LED_Off;
    ReadPower();
    Status_LED_On;
    Serial.print(RMSCurrent); Serial.print(" Amps  "); Serial.print(RMSPower); Serial.println(" W");


    // Get a Report Make and make as an array
    String Report = Status_Report();
    char Report_array[(Report.length() + 1)];
    Report.toCharArray(Report_array, (Report.length() + 1));

    // Display a report when publishing
    Serial.print("Published To topic: "); Serial.print(InStatus); Serial.print("  -  Report Sent: "); Serial.println(Report_array);


    // Send a status report
    client.publish(InStatus, Report_array);


    if (Event == "REBOOT") {
      Serial.println("Rebooting.......................");
      // For ESP32 or ESP8266
      ESP.restart();
    } // End of reboot request

  } // End of heartbeat timer

} // End of Loop



