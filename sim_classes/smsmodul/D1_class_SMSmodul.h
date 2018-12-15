//_____D1_class_SMSmodul.h___________________181215-181215_____
// D1 mini class for sending and receiving SMS with a
// SIM800C GSM GPRS module STM32
// Hardware: (1) WeMos D1 mini
//           (2) Battery Shield for WEMOS D1 mini
//           (3) Selfmade SIM800C 9pol ProtoBoard Shield with
//               SIM800C GSM GPRS module STM32
// Created by Karl Hartinger, December 15, 2018.
// Last modified: -
// Released into the public domain.

#ifndef D1_CLASS_SMSmodul_H
#define D1_CLASS_SMSmodul_H
#define SMSMOD_SWS            true     //software serial
//#define SMSMOD_SWS           false     //hardware serial
#include "Arduino.h"                   // D5,D6

#if SMSMOD_SWS
 #include <SoftwareSerial.h>
#endif

#define  SMSMOD_PIN_SWS_TX      D5     // D5 SW Serial send
#define  SMSMOD_PIN_SWS_RX      D6     // D6 SW Serial receive
#define  SMSMOD_CRLF          "\r"     // sim carriage return
#define  SIMMOD_WAIT_SEC         4     // sim command timeout
#define  SIMMOD_SMS_MEM       "ME"     // ME=modem, SM=sim card
#define  SIMMOD_SMS_NUM         21     // sms# ME: 21, SM:1
//-----status---------------------------------------------------
#define SMSMOD_OK                0     // success
#define SMSMOD_ERR_ATE1          1     // ERROR while ATE1
#define SMSMOD_ERR_CMGF          2     // ERROR while AT+CMGF
#define SMSMOD_ERR_CPMS          4     // ERROR while AT+CPMS
#define SMSMOD_ERR_CNMI          5     // ERROR while AT+CNMI
#define SMSMOD_ERR_NOGT          6     // ERROR no input sign >
#define SMSMOD_ERR_SEND          7     // ERROR while sending sms
#define SMSMOD_ERR_CMGD          8     // ERROR while deleting
#define SMSMOD_ERR_SNUM          9     // ERROR wrong sms number
#define SMSMOD_ERR_NMEM         10     // ERROR memory not set
#define SMSMOD_ERR_READ         11     // ERROR: SMS not read
#define SMSMOD_ERR_NOSM         12     // ERROR: No SMS
#define SMSMOD_ERR_CMGL         13     // ERROR: SMS not listed
#define SMSMOD_ERR_NSMS         14     // ERROR: wrong number of SMS

//_____info about a SMS_________________________________________
struct SMS {
 int number=-1;
 String phone="";
 String date="";
 String text="";
};

class SMSmodul {
 //-----properties----------------------------------------------
 protected:
  int    status;                       // state of sms module
  int    pinRx_;                       // software serial pin RX
  int    pinTx_;                       // software serial pin TX
  String crlf_;                        // end of sms command
  String mem_;                         // "SM", "ME", "MT"
  int    numofSms1_;                   // number 1. sms location
  String sCmd;                         // command string
  String sResult;                      // answer of modem 
#if SMSMOD_SWS
  SoftwareSerial *seri;                // software serial
#endif
 //-----constructor & co----------------------------------------
 public:
  SMSmodul();
  SMSmodul(String mem);               // mem + default pins
  SMSmodul(int pinRx, int pinTx);     // pins + default mem
  SMSmodul(int pinRx, int pinTx, String mem);  //
  ~SMSmodul();
  void setup();
  void setup(int pinRx, int pinTx, String mem);
 //-----setter, getter, working methods-------------------------
 public: 
  int    begin();                      // start module
  int    getStatus();                  // get status as int
  String getsStatus();                 // get status as text
  int    sendSMS(SMS sms1);            // send a sms
  bool   isSMS();                      // true: sms received
  SMS    readSMS(int num);             // read SMS num
  SMS    readSMS1();                   // read first SMS
  int    deleteSMS1();                 // delete first SMS
 //-----special functions---------------------------------------
  int    setMem(String mem);           // set memory for sms
  int    deleteSMS(int num);           // delete SMS number num
  String listAllSMS();                 // list all sms as string
  int    numberOfSMS();                // number of SMS
 //-----helper functions---------------------------------------- 
  String getsCommand();                // get last command
  String getsResult(bool raw_=true);   // last modem answer
//String getsResult();                 // last modem answer
  String sendCmd(String cmd);          // send AT command
  String sendCmd(String cmd, int numEnd); //
  String sendCmd(String cmd, int numEnd, char cEnd);
  String sendCmd(String cmd, int numEnd, char cEnd, int sec);
  int    countOccurrence1in2(String sFind, String sBasic);
  void   write(char c);
};
#endif
