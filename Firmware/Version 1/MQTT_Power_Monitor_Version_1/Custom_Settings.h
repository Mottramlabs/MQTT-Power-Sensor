/* Connection detials for WiFi and board functions
*/

// Select Static IP Mode, uncomment below to enable
//#define STATIC_IP
IPAddress ip(192, 168, 1, 33);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Add your Wifi details below
const char* SSID_1 = "AP";
const char* Password_1 = "Password";

const char* SSID_2 = "AP";
const char* Password_2 = "Password";

const char* SSID_3 = "AP";
const char* Password_3 = "Password";

const char* SSID_4 = "AP";
const char* Password_4 = "Password";

// MQTT Broker
const char* mqtt_server = "192.168.1.10";
// MQTT Topics
const char* InStatus = "Power/Status";
const char* InControl = "Power/Control";
String Broadcast_All = "*ALL";                    // Message used to broadcast to all devices subscribed to above topic

// Heatbeat items
#define Heartbeat_Range   99                      // Event count max value
#define Heatbeat    1000                         // Heartbeat timer value, in mS

// Watchdog items
volatile int Watchdog_Timout = 1200;              // Time in seconds before watchdog times out, 1200 = 1200 seconds or 20 minutes

// Heatbeat timer
int Heart_Value = 0;                              // Timer
long LastMsg = 0;                                 // Message sent counter

// Custom default values
String WiFi_SSID = "None";                        // SSID string
String My_MAC = "";                               // MAC address, tobe Read from ESP8266
char MAC_array[13] = "000000000000";              // Better MAC definition
//String Mode = "Off";                            // Default mode
volatile int Report_Request = 0;                  // Set to 1 if report required
String Event = "Boot";                            // Default

// I/O
#define Status_LED 2                              // D4
#define Status_LED_On   digitalWrite(Status_LED, HIGH)
#define Status_LED_Off  digitalWrite(Status_LED, LOW)

// Power monitor items
double Calib = 1;//10.545662
double Kilos;
unsigned long StartMillis;
unsigned long EndMillis;
double RMSCurrent;
int RMSPower;
int PeakPower;


void ReadPower ()      // Method to read information from CTs
{
  int Current = 0;
  int MaxCurrent = 0;
  int MinCurrent = 1023;
  int PeakCurrent = 0;

  // Needs to sample for at least one and half mains cycles or > 30mS
  for (int j = 0 ; j <= 600 ; j++)
  {

    //         digitalWrite(D8, HIGH);
    Current =  analogRead(A0);    //Reads A/D input and records maximum and minimum current
    //        digitalWrite(D8, LOW);

    if (Current >= MaxCurrent)
      MaxCurrent = Current;

    if (Current <= MinCurrent)
      MinCurrent = Current;
  } // End of samples loop

  PeakCurrent = MaxCurrent - MinCurrent;


RMSCurrent = PeakCurrent;

 // http://www.referencedesigner.com/rfcal/vrms-to-vpeak-conversion.php
 // RMSCurrent = (PeakCurrent * 0.3535) / Calib; //Calculates RMS current based on maximum value and scales according to calibration
 // RMSPower = 248 * RMSCurrent;  //Calculates RMS Power Assuming Voltage 240VAC, change to 110VAC accordingly

} // End of function


