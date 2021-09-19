void callback(char* topic, byte* payload, unsigned int length_1) {

  //  Serial.print("Message length = "); Serial.println(length);

  // Make a string of the received message
  String  Message_Arrived = "";
  for (unsigned int i = 0; i < length_1; i++) {
    Message_Arrived = Message_Arrived + ((char)payload[i]);
  }

  // Serial.print("Message arrived and made into string: "); Serial.println(Message_Arrived);

  // Is the message for only you? Either contains your MAC address or ALL (broadcast)
  if (Message_Arrived.indexOf(My_MAC) >= 0 || Message_Arrived.indexOf(Broadcast_All) >= 0) {

    Serial.print("Valid Message: "); Serial.print(topic); Serial.print("  "); Serial.println(Message_Arrived);


    // Valid message received, remove the headers either All or Mac
    // Remove *ALL if present
    if  (Message_Arrived.indexOf(Broadcast_All) >= 0) {
      Message_Arrived.replace(Broadcast_All, "");       // Remove the command string characters
    } // End of strip and test for ALL broadcast

    // Remove the MAC number if present
    if  (Message_Arrived.indexOf(My_MAC) >= 0) {
      Message_Arrived.replace(My_MAC, "");       // Remove the command string characters
    } // End of strip and test for ALL broadcast



    // *********** Test for Reboot ***********
    if ((Message_Arrived.indexOf("REBOOT") >= 0) ) {
      Event = "REBOOT";
    } // End of reboot test

    Report_Request = 1;

  } // End of a valid message received

  // Watchdog Clear watchdog
  watchdogCount = 0;
  yield();


} // End of callback


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT Broker connection...");
    // Attempt to connect

    // Make MAC address array used for Client ID
    char  MAC_array[My_MAC.length()];
    My_MAC.toCharArray(MAC_array, (My_MAC.length() + 1));

    // Connect client and use MAC address array as the Client ID
    if (client.connect(MAC_array)) {

      Serial.println("connected");
      Serial.print("This is the client ID Used: "); Serial.println(MAC_array);

      // Once connected, publish an announcement...
      Report_Request = 1;   // Request a report after power up

      // ... and resubscribe
      client.subscribe(InControl);
      delay(10);  // It needs a delay here else does not subsribe correctly!
      Serial.print("Sunbscribed to: "); Serial.println(InControl);

    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} // End of reconnect

