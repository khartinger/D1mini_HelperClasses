//_____D1_class_SimpleMqttOta.h_______________210418-210418_____
// The SimpleMqttOta class is suitable for D1 mini (ESP8266) and
// D1mini ESP32 and extends the class SimpleMqtt (PubSubClient)
// OTA functionality (over the air programming).
// Created by Karl Hartinger, April 17, 2021.
// Changes:
// 2021-04-18 New
// Hardware: WeMos D1 mini OR D1 mini ESP32
// Released into the public domain.

#ifndef D1_CLASS_SIMPLEMQTTOTA_H
#define D1_CLASS_SIMPLEMQTTOTA_H
#include "Arduino.h"                   // D1, ...
#if defined(ESP8266) || defined(D1MINI)
 #include <ESP8266WiFi.h>              // network connection
 #include <ESP8266mDNS.h>              //
 #include <WiFiUdp.h>                  //
 #include <ArduinoOTA.h>               // Over-the-Air-Update
#endif
#if defined(ESP32) || defined(ESP32D1)
 #include <ESPmDNS.h>                  // DNS
 #include <WiFi.h>                     // network connection
 #include <WiFiUdp.h>                  //
 #include <ArduinoOTA.h>               // Over-the-Air-Update
#endif
#include "D1_class_SimpleMqtt.h"       // MQTT basic methods
#include "EEPROM.h"                    // to save mqtt base

class SimpleMqttOta : public SimpleMqtt {
 //------properties---------------------------------------------
 protected:
  String ota_password_;                // OTA password

 //------constructor & co---------------------------------------
 public:
  //_____constructor____________________________________________
  SimpleMqttOta(String sssid, String spwd, String smqtt_server,
   String topicbase, String ota_hostname, String ota_password);

  //_____initialize all properties. Called by constructor(s)____
  //_______setup OTA (Over-the-Air-Update)______________________
  void setupOta();

 //------setter and getter methods------------------------------
  //_____extend getsLocalIP with OTA-setup______________________
  String getsLocalIP();
  //_____set OTA hostname_______________________________________
  void   setOtaHostname(String hostname);
  //_____set OTA password_______________________________________
  void   setOtaPassword(String password);

 //------working methods----------------------------------------
  //_____control mqtt in main loop (with reconnect)_____________
  bool   doLoop(void);                 // calls checkMQTT();
  //_____control mqtt and OTA in main loop (without reconnect)__
  bool   doLoop(bool tryToReconnect);

};
#endif