## ESP8266 - Power Sensor (Using a Wemos D1 Mini)

The sensor PCB uses a split core current transformer (CT) to sense the AC current flowing through a mains cable, a typical CT would be the SCT-013-000 (Current Type) capable of measuring up to 100A  available on eBay. The current transformers output is applied to a burden resistor (22 ohm) which is biased at around half of the ESP8266's supply voltage (3.3V). The ESP8266's own A/D is then used to measure voltage developed across this burden resistor.  The A/D used in the ESP8266 has an input voltage range of 0-1V but the Wemos adds a resistor divider to allow for a 0-3.3V input range to the Wemos board. 

Included are the PCB files with schematic, a simple 3D printable case and some sample firmware for the ESP8266.

###### Firmware Version 1

Using the ESP8266's own A/D (10-bit) to measure the output of the current transformer, this version measure the peak values of the mains sine wave then calculating the RMS voltage value.

###### Firmware Version 2

This is based of the EmonLib https://github.com/openenergymonitor/EmonLib library. This works different from version 1 and as some digital filtering which improves resolution at lower power levels.

