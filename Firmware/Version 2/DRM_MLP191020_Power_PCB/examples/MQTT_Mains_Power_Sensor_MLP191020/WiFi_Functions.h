/*
    Wifi Setup and operation. Cycles through 4 Wifi access points until a connection is made.
*/

// compose a custom report to send by MQTT
String Status_Report()  {

  // WiFi Version
  long rssi = WiFi.RSSI();

  String Report = Mode + ", " + String(Value) + ", ";
  Report = Report + My_MAC + ", " + WiFi_SSID + ", " + rssi + "dB, " + My_IP + ", " + String(Heart_Value);

  // clear the event message
  if (Mode != "Test") {
    Mode = "None";
  }

  return Report;

} // End of function


// start up Wifi and make a connection
void WiFi_Startup(const char* ssid, const char* password) {

  WiFi_SSID = ssid;               // Set Access point name used by report

  // static IP Option, set the IP and router details in the custom config file
#ifdef STATIC_IP
  // static IP Setup
  WiFi.config(ip, gateway, subnet);
  Serial.println("Static IP Mode");
#else
  Serial.println("DHCP Mode");
#endif

  Serial.print("Connecting to "); Serial.print(ssid); Serial.print("  ");

  // connect to wifi and turn off access point mode
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  // reset timeout counter
  int TimeOut = 0;

  // loop while not connected and timeout timer still running
  while ((WiFi.status() != WL_CONNECTED) & (TimeOut < 100)) {

    // Print connection progress ticker
    Serial.print(".");
    delay(100);
    digitalWrite(Network_LED, HIGH);
    delay(100);
    digitalWrite(Network_LED, LOW);
    TimeOut ++;

  } // end connection loop

  // if connected
  if (WiFi.status() == WL_CONNECTED) {

    // get MAC address, 6 characters in an array
    byte mac[6];  WiFi.macAddress(mac);

    My_MAC = "";

    // make a string of the MAC with colons "0" padding and upper case results
    // the MAC address is used as the products MQTT device address
    for (int i = 0; i <= 5; i++) {

      // add leading zero if missing
      String M = String(mac[i], HEX); M.toUpperCase();
      if (M.length() < 2) {
        M = "0" + M;
      } // end of padding

      My_MAC = My_MAC + M;

      // add colon of required
      if (i < 5) {
        My_MAC = My_MAC;
      }

    } // end of loop

    // get the wifi IP address
    ip = WiFi.localIP();

    // make a string of that IP address array
    My_IP = WiFi.localIP().toString();

    // make MAC address array used for Client ID
    My_MAC.toCharArray(MAC_array, (My_MAC.length() + 1));

    // print a connection report
    Serial.println("");
    Serial.print("WiFi connected, "); Serial.print("DHCP IP Address = "); Serial.println(WiFi.localIP());
    Serial.println(__FILE__);

  } // end of connected

  // not connected!
  else {
    Serial.println(" No Wifi Connection!");
  } // end of else

} // end of wifi startup


// cycle through the WiFi access points until a connection is made
void Get_Wifi() {

  // start the serial connection
  Serial.begin(115200); Serial.println(""); Serial.println(""); Serial.println("* Starting up *");

  //  while not connected to wifi
  while (WiFi.status() != WL_CONNECTED) {

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying Access Point 1 - "); WiFi_Startup(SSID_1, Password_1);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying Access Point 2 - "); WiFi_Startup(SSID_2, Password_2);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying Access Point 3 - "); WiFi_Startup(SSID_3, Password_3);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying Access Point 4 - "); WiFi_Startup(SSID_4, Password_4);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Trying access points failed trying again!");
    }

  } // end of while loop

} // end of function
