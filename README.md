# MQTT Mains Power Sensor
The sensor uses a Non-invasive Split Core Current Transformer type 100A SCT-013-000. available on eBay.
The sensor samples the current value every second or so and publishes it to a topic via an MQTT broker.
A watchdog is also provided that kicks in after a few minutes if it does not receive an MQTT message, this can be turned off if preferred.

I have included the Gerber files for the PCB layout and the source files for Kicad. There maybe issues with the custom libraries I used if so I will unload those lib files also.



