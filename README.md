# mqtt-sonoff
code for esp8266 projects, including home automation, using sonof relays and mqtt broker

https://www.itead.cc/smart-home/sonoff-wifi-wireless-switch.html

intended to be fairly generic (within the SONOFF hardware). Logic is intended to happen elsewhere, communicated via MQTT topics. 
intended for use with Node-Red (but Node-Red is not required)
Anything else that can write/read to an MQTT broker would work.

MQTT topics are used for opening/closing the relay and optionally getting temperature/humidity

Configuration

makes use of WifiManager for connection to WiFi, MQTT broker settings, device role, and device nickname

device nickname is used as a prefix for MQTT topics

device role is FAN or SWITCH

SWITCH ... just turn on/off the relay, based on MQTT topic NICKNAME-Power

FAN ... controls relay like SWITCH does, but also periodically set value on NICKNAME-Temperature and NICKNAME-Humidity

Button Press

Short press on button to toggle relay manually.

Long press to wipe the wifimanager settings and reboot (to allow reconfiguration of wifi and other settings)

Issues:

It's my first github project. I'm sure there are lots of stylistic issues. 

Credits

https://github.com/tzapu/SonoffBoilerplate

