//_____D1_class_SimpleMqttOta.cpp_____________210418-210418_____
// The SimpleMqttOta class is suitable for D1 mini (ESP8266) and
// D1mini ESP32 and extends the class SimpleMqtt (PubSubClient)
// OTA functionality (over the air programming).
// Created by Karl Hartinger, April 17, 2021.
// Changes:
// 2021-04-18 New
// Hardware: WeMos D1 mini OR D1 mini ESP32
// Released into the public domain.

#include "D1_class_SimpleMqtt.h"
#include "D1_class_SimpleMqttOta.h"

// *************************************************************
//    constructor & co
// *************************************************************

SimpleMqttOta::SimpleMqttOta(String sssid, String spwd, String smqtt_server, 
  String topicbase, String ota_hostname, String ota_password):
  SimpleMqtt(sssid, spwd, smqtt_server, topicbase, ota_hostname),
  ota_password_{ota_password}
{
}

//_______setup OTA (Over-the-Air-Update)________________________
void SimpleMqttOta::setupOta()
{
 Serial.println("setupOta(): sMQTTClientName="+sMQTTClientName);
 MDNS.begin(sMQTTClientName.c_str());
 ArduinoOTA.setHostname(sMQTTClientName.c_str());
 //ArduinoOTA.setHostname("192.168.0.55");
 ArduinoOTA.setPassword(ota_password_.c_str());
 ArduinoOTA.onStart([]() {
  String type;
  if (ArduinoOTA.getCommand() == U_FLASH)
   type = "sketch";
  else // U_SPIFFS
   type = "filesystem";
  // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
  if(DEBUG_MQTT) Serial.println("setupOta: Start updating " + type);
 });
 ArduinoOTA.onEnd([]() {
  if(DEBUG_MQTT) Serial.println("\nsetupOta: End");
 });
 ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  if(DEBUG_MQTT) Serial.printf("setupOta: Progress: %u%%\r", (progress / (total / 100)));
 });
 ArduinoOTA.onError([](ota_error_t error) {
  if(DEBUG_MQTT) {
   Serial.printf("setupOta: Error[%u]: ", error);
   if (error == OTA_AUTH_ERROR)
    Serial.println("Auth Failed");
   else if (error == OTA_BEGIN_ERROR)
    Serial.println("Begin Failed");
   else if (error == OTA_CONNECT_ERROR)
    Serial.println("Connect Failed");
   else if (error == OTA_RECEIVE_ERROR)
    Serial.println("Receive Failed");
   else if (error == OTA_END_ERROR)
    Serial.println("End Failed");
  }
 });
 ArduinoOTA.begin();
 if(DEBUG_MQTT) Serial.println("setupOta: OTA ready");
}

// *************************************************************
// setter and getter methods
// *************************************************************

//_______extend getsLocalIP with OTA-setup______________________
String SimpleMqttOta::getsLocalIP() {
 if(DEBUG_MQTT) Serial.println("getsLocalIP() mit setupOta()");
 sMyIP=WiFi.localIP().toString();
 setupOta();                                // setup OTA
 return sMyIP;
}

//_______set OTA hostname_____________________________________
void SimpleMqttOta::setOtaHostname(String hostname) {
 sMQTTClientName=hostname;
}

//_____set OTA password_______________________________________
void SimpleMqttOta::setOtaPassword(String password) {
 ota_password_=password;
}

// *************************************************************
//    mqtt (main) loop control
// *************************************************************

//_______control mqtt in main loop (true: with reconnect)_______
// calls checkMQTT(); that MUST be called every loop
bool SimpleMqttOta::doLoop(void) { 
 return(doLoop(true)); 
}

//_______control mqtt and OTA in main loop (without reconnect)__
// calls checkMQTT(); that MUST be called every loop
// return: true=PubSubClient loop() done
bool SimpleMqttOta::doLoop(bool tryToReconnect)
{
 ArduinoOTA.handle();
 //Serial.println("SimpleMqttOta::doLoop - ArduinoOTA.handle()");
 return SimpleMqtt::doLoop(tryToReconnect);
}

