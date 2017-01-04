#ifndef MAIN_INCLUDE_H

#define MAIN_INCLUDE_H

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <PubSubClient.h> // mqtt

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


extern "C" {
  #include "user_interface.h"
}

// for strcat, strcpy
#include <stdio.h>
#include <string.h>

// saved parameters
char mqtt_server[40];
char mqtt_port[6] = "1883";
char device_role[10] = ""; // FAN or SWITCH
char mqtt_nickname[20]; // example "Fan02";
// end saved parameters

//flag for saving data
bool shouldSaveConfig = false;


// long/short button press
long buttonTimer = 0;
long longPressTime = 20000;
bool buttonActive = false;
bool longPressActive = false;


int useDHT = 0;

// broker topics will be the nickname dash suffix
// if Fan02 is the nickname
// one of the topics would be
// Fan02-Power

#define POWER_FEED_SUFFIX "Power"
#define TEMPERATURE_FEED_SUFFIX "Temperature"
#define HUMIDITY_FEED_SUFFIX "Humidity"

// the following are defined in Setup()
char POWER_FEED[100]; // sub
char TEMPERATURE_FEED[100];  //= "Fan02-Temperature"; // pub
char HUMIDITY_FEED[100];  //= "Fan02-Humidity"; // pub


int enableSerial = 1; // 0 none, 1 errors & startup, 2 verbose

// Pins
const int pinLED = 13; // output
const int pinRelay = 12; // output
const int pinRunMode = 0; // input

#define DHTPIN 14     // what digital pin we're connected to. perhaps 14 or 4
const int pinTemperature = DHTPIN; // input

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTTYPE DHT21   // DHT 21 (AM2301) /// perhaps DHT22

// end of normally-replaceable constants


int current_relay_power = 0;
int RELAY_POWER_ON = 1;
int RELAY_POWER_OFF = 0;


int new_temperature = -1000;
float new_humidity;
float new_heatIndex;

int old_temperature = -1000;
float old_humidity;
float old_heatIndex;


const int LEDOn = 0;
int LED_status = 1 - LEDOn;
int networkSafeMode = 0;

//const int fanOn = 0;

int enableServer = 1;
int enableClient;

int netFailCount = 0;

//#include <Adafruit_Sensor.h>
//#include <DHT_U.h>

#include "DHT.h"

DHT dht(DHTPIN, DHTTYPE, 30); // , 11); // 11 is timing for esp8266-01
//DHT dht(DHTPIN, DHTTYPE, 11); // , 11); // 11 is timing for esp8266-01


//#include <Ticker.h>
//Ticker ticker_control;

long readTempLastMS = 0;
long readTempLastMax = 10000;

long sampleTempLastMS = 0;
long sampleTempLastMax = 60000;

//long fanLastMS = 0;
//long fanLastMax = 60000;

long msPerSample = 60000;
long sampleMSTotal = 0;
float sampleTotal = 0;
float sampleTotalRH = 0;


// forward declarations

boolean my_publish(const char* topic, char* value);
void relay_power(int power);
void setFeaturesFromRole();
//void do_fan_control();

// for main_include_h
#endif
