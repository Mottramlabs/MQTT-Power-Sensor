
/*  Wifi Setup and operations. This uses DHCP and will be assigned an IP by the router

*/

// Compose report to return as required, LED and Relay not the same!
String Status_Report()  {

  // WiFi Version
  long rssi = WiFi.RSSI();
 
  String Report = String(RMSCurrent) + ", " + My_MAC + ", " +  WiFi_SSID + ", " + rssi + "dB, " + String(Heart_Value);

  return Report;

} // End of function


void WiFi_Startup(const char* ssid, const char* password) {

  WiFi_SSID = ssid;               // Set Access point name used by report

  // Static IP Option, set the IP and router details in the custom config file
#ifdef STATIC_IP
  // Static IP Setup
  WiFi.config(ip, gateway, subnet);
  Serial.println("Static IP Mode");
#else
  Serial.println("DHCP Mode");
#endif

  Serial.print("Connecting to "); Serial.print(ssid); Serial.print("  ");

  // Connect to wifi and turn off access point mode
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  int TimeOut = 0;  // Reset timeout counter

  // Loop while not connected and timeout timer still running
  while ((WiFi.status() != WL_CONNECTED) & (TimeOut < 100)) {

    // Print connection progress ticker
    Status_LED_Off;
    delay(50);
    Status_LED_On;
    delay(50);
    Serial.print(".");
    TimeOut ++;
  }

  // Timed out or connected?
  if (WiFi.status() == WL_CONNECTED) {


    // Get MAC address, 6 characters in an array
    byte mac[6];  WiFi.macAddress(mac);

    My_MAC = "";

    // Make a string of the MAC with colons "0" padding and upper case results
    for (int i = 0; i <= 5; i++) {

      // Add leading zero if missing
      String M = String(mac[i], HEX); M.toUpperCase();
      if (M.length() < 2) {
        M = "0" + M;
      } // End of padding

      My_MAC = My_MAC + M;

      // Add colon of required
      if (i < 5) {
        My_MAC = My_MAC;
      }

    } // End of loop

    // Make MAC address array used for Client ID
    My_MAC.toCharArray(MAC_array, (My_MAC.length() + 1));

    // Print connection report
    Serial.println("");
    Serial.print("WiFi connected, "); Serial.print("DHCP IP Address = "); Serial.print(WiFi.localIP());
    Serial.print(", "); Serial.println(Status_Report());

  }

  else {
    Serial.println(" No Wifi Connection!");
  } // End of else

} // End of wifi startup



void Get_Wifi() {

  Serial.begin(115200);

  Serial.println(""); Serial.println(""); Serial.println("* Starting up *");

  //While not connected to wifi
  while (WiFi.status() != WL_CONNECTED) {


    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying 1 - "); WiFi_Startup(SSID_1, Password_1);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying 2 - "); WiFi_Startup(SSID_2, Password_2);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying 3 - "); WiFi_Startup(SSID_3, Password_3);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Trying 4 - "); WiFi_Startup(SSID_4, Password_4);      // WiFi start
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Trying access points finished trying again!");

    }

  } // End of while loop

} // End of function


