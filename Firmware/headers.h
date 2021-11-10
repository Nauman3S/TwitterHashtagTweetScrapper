
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif

#if defined(ARDUINO_ARCH_ESP8266)
ESP8266WebServer server;
#elif defined(ARDUINO_ARCH_ESP32)
WebServer server;
#endif
#include <PubSubClient.h>
#include "SoftwareStack.h"

#if defined(ARDUINO_ARCH_ESP8266)
#ifdef AUTOCONNECT_USE_SPIFFS
FS &FlashFS = SPIFFS;
#else
#include <LittleFS.h>
FS &FlashFS = LittleFS;
#endif
#elif defined(ARDUINO_ARCH_ESP32)
#include <SPIFFS.h>
fs::SPIFFSFS &FlashFS = SPIFFS;
#endif
#include "neoTimer.h"

#define GET_CHIPID() ((uint16_t)(ESP.getEfuseMac() >> 32))

unsigned long lastPub = 0;
unsigned int updateInterval = 2000;

SoftwareStack ss; //SS instance

String mac = (WiFi.macAddress());
char __mac[sizeof(mac)];

const char *mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char *mqtt_user = "testUser";
const char *mqtt_pass = "testUser@123";
const char *mqtt_client_name = __mac; //"12312312312332212";// any random alphanumeric stirng
//////////////////////////////
#define BUFFER_SIZE 250
String incoming = "";
String incomingTopic = "";
WiFiClient wclient;
PubSubClient mqttClient(wclient);

String LastUpdated = "";
String internetStatus = "Not-Connected";
String connectionMode = "WiFi";
