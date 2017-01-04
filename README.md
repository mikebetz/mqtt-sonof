# mqtt-sonof
code for esp8266 projects, including home automation, using sonof relays and mqtt broker


intended for use with Node-Red (but Node-Red is not required)
MQTT topics used for setting relay status and optionally getting temperature/humidity

Configuration

makes use of WifiManager for connection to WiFi, MQTT broker settings, device role, and device nickname

device nickname is used as a prefix for MQTT topics

device role is FAN or SWITCH

SWITCH ... just turn on/off the relay, based on MQTT topic NICKNAME-Power

FAN ... controls relay like SWITCH does, but also periodically set value on NICKNAME-Temperature and NICKNAME-Humidity

Button Press

Short press on button to toggle relay manually.

Long press to wipe the wifimanager settings and reboot (to allow reconfiguration of wifi and other settings)

issues:

It's my first github project. I'm sure there are lots of stylistic issues. Including ... issues are listed here instead of Issues.

does not actually use the port number for the mqtt broker. Currently hard-coded as 1883 (for Mosca)

pin numbers for relay and temperature are hard-coded

device type for temperature sensor is hard-coded DHT22

frequency of temperature reading is hard-coded

reset after long-press is not clean ... requires toggling the power to recover

lots of dead code to clean up (pre-github)
