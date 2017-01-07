# mqtt-sonoff
code for esp8266 projects, including home automation, using sonoff relays and mqtt broker

Sonoff relays are an inexpensive packaging of an ESP8266, a relay, a power supply and a case, with an optional temperature sensor. They come preloaded with software, but can be reprogrammed if one solders on a short header strip (4 or 5 pins, depending on SONOFF model).

https://www.itead.cc/smart-home/sonoff-wifi-wireless-switch.html

This project is intended to be fairly generic (within the SONOFF hardware). Logic is intended to happen elsewhere, communicated via MQTT topics. 
Designed for use with Node-Red (but Node-Red is not required) Anything else that can write/read to an MQTT broker would work.

MQTT topics are used for opening/closing the relay and optionally getting temperature/humidity

Configuration

makes use of WifiManager for connection to WiFi, MQTT broker settings, device role, and device nickname

device nickname is used as a prefix for MQTT topics

device role is FAN or SWITCH

SWITCH ... just turn on/off the relay, based on MQTT topic NICKNAME-Power. Relay is normally GPIO 13.

FAN ... controls relay like SWITCH does, but also periodically set value on NICKNAME-Temperature and NICKNAME-Humidity

io pin numbers for relay, LED and button can be changed from the defaults of 13, 12, and 0

Over the Air updating is included

Button Press:

Normally on GPIO 0

Short press on button to manually toggle relay (and update the NICKNAME-Power topic appropriately).

Long press (10seconds+) to wipe the wifimanager settings and reboot (to allow reconfiguration of wifi and other settings)

Issues:

It's my first github project. I'm sure there are lots of stylistic issues. 

Credits

https://github.com/tzapu/SonoffBoilerplate

