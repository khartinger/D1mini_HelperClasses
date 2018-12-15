//_____D1_class_SMSmodul.cpp_________________181215-181215_____
// D1 mini class for sending and receiving SMS with a
// SIM800C GSM GPRS module STM32
// Hardware: (1) WeMos D1 mini
//           (2) Battery Shield for WEMOS D1 mini
//           (3) Selfmade SIM800C 9pol ProtoBoard Shield with
//               SIM800C GSM GPRS module STM32
// Created by Karl Hartinger, December 15, 2018.
// Last modified: -
// Released into the public domain.

#include "D1_class_SMSmodul.h"

//**************************************************************
//    constructor & co
//**************************************************************

//_____default constructor______________________________________
SMSmodul::SMSmodul() { setup(-1,-1,""); }

//_____constructor: default pins, specified memory for sms______
SMSmodul::SMSmodul(String mem) { setup(-1,-1, mem); }
 
//_____constructor: specified pins, default memory for sms______
SMSmodul::SMSmodul(int pinRx, int pinTx) 
{ setup(pinRx, pinTx, ""); } 
 
//_____constructor: specified pins, memory for sms______________
SMSmodul::SMSmodul(int pinRx, int pinTx, String mem)
{ setup(pinRx, pinTx, mem); }

//_____destructor_______________________________________________
SMSmodul::~SMSmodul() {
#if SMSMOD_SWS
 delete(seri); 
#endif
};

//_____setup SMSmodul__________________________________________
void SMSmodul::setup() { setup(-1,-1,""); }

//_____setup SMSmodul__________________________________________
void SMSmodul::setup(int pinRx, int pinTx, String mem)
{
 //-----set software serial pins and memory---------------------
 if(pinRx>=0) pinRx_=pinRx; else pinRx_=SMSMOD_PIN_SWS_RX;
 if(pinTx>=0) pinTx_=pinTx; else pinTx_=SMSMOD_PIN_SWS_TX;
 String mem_=SIMMOD_SMS_MEM;
 if((mem=="SM")||(mem=="ME")||(mem=="MT")) mem_=mem;
 if(mem_="ME") numofSms1_=21; else numofSms1_=1;
 crlf_=SMSMOD_CRLF;
 status=SMSMOD_OK;
 //-----begin software serial-----------------------------------
#if SMSMOD_SWS
 sResult="SoftSerial";
 delete(seri);
 seri=new SoftwareSerial(pinRx_,pinTx_); // RX,TX
 seri->begin(9600);                    // start software serial
 seri->listen();                       // listen to soft SeriSW
 seri->flush();                        // wait clear out buffer
 while(seri->available()) {            // + empty incomming
  seri->read(); delay(1);              // + buffer
 }
  
#else
 sResult="HardSerial";
 Serial.begin(9600);
 Serial.flush();                       // wait clear out buffer
 while(Serial.available()) {           // + empty incomming
  Serial.read(); delay(1);             // + buffer
 }
#endif
}

//**************************************************************
//    setter, getter, working methods
//**************************************************************

//_____begin = start sms module (setup module)__________________
// if a command fails, it will be repeated once
int SMSmodul::begin()
{
 if(mem_="ME") numofSms1_=21; else numofSms1_=1;
 //-----finish old sms, if a send-error occurred----------------
 //sendCmd("\x1A");                      // just for safety
 //-----turn echo on (better for debug)-------------------------
 sCmd="ATE1";                          // echo 0=off, 1=on
 sResult=sendCmd(sCmd,2,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,2,'\n');        // send command
  status=SMSMOD_ERR_ATE1;              // set status to error
  return status;                       //
 }
 //-----set sms text format-------------------------------------
 sCmd="AT+CMGF=1";                     // use text format
 sResult=sendCmd(sCmd,2,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,2,'\n');        // send command
  status=SMSMOD_ERR_CMGF;              // set status to error
  return status;                       //
 }
 //-----set preferred message storage to modem (ME)-------------
 sCmd="AT+CPMS=\""+mem_+"\",\""+mem_+"\",\""+mem_+"\"";
 sResult=sendCmd(sCmd,4,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,4,'\n');        // send command
  status=SMSMOD_ERR_CPMS;              // set status to error
  return status;                       //
 }
 //-----configuration message routing---------------------------
 sCmd="AT+CNMI=2,1,2,1,0";             // info on receiving
 sResult=sendCmd(sCmd,2,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,2,'\n');        // send command
  status=SMSMOD_ERR_CNMI;              // set status to error
  return status;                       //
 }
 status=SMSMOD_OK;
 return status;
}

//_____get status as int________________________________________
int SMSmodul::getStatus() { return status; }

//_____get status as String_____________________________________
String SMSmodul::getsStatus() {
 switch(status) {
  case SMSMOD_OK: return("OK");
  case SMSMOD_ERR_ATE1: return("ERROR: wrong answer for echo (ATE1)");
  case SMSMOD_ERR_CMGF: return("ERROR while AT+CMGF");
  case SMSMOD_ERR_CPMS: return("ERROR while AT+CPMS");
  case SMSMOD_ERR_CNMI: return("ERROR while AT+CNMI");
  case SMSMOD_ERR_NOGT: return("ERROR: No input sign >");
  case SMSMOD_ERR_SEND: return("ERROR while sending sms");
  case SMSMOD_ERR_CMGD: return("ERROR while AT+CMGD");
  case SMSMOD_ERR_SNUM: return("ERROR: Wrong SMS number");
  case SMSMOD_ERR_NMEM: return("ERROR: memory not set");
  case SMSMOD_ERR_READ: return("ERROR: SMS not read");
  case SMSMOD_ERR_NOSM: return("ERROR: No SMS");
  case SMSMOD_ERR_CMGL: return("ERROR: not all SMS listed");
  case SMSMOD_ERR_NSMS: return("ERROR: wrong number of SMS");
  default: return("Unknown state="+status);
 }
}

//_____send a sms (try 2x)______________________________________
int SMSmodul::sendSMS(SMS sms1)
{
 String s1;                            // help command string
 String txt2=sms1.text+"\x1A";         // sms text (end 1A)
 //-----finish old sms, if a send-error occurred----------------
 //sendCmd("\x1A");                      // just for safety
 //-----send sms------------------------------------------------
 sCmd="AT+CMGS=\""+sms1.phone+"\""+SMSMOD_CRLF; // cmd send sms
 sResult=sendCmd(sCmd,1,'>');          // "send sms" to modem
 if(sResult.indexOf(">")<0) {          // no input sign 
  sendCmd("\x1A",1,'\n',1);            // just for safety
  s1=sendCmd("AT",2,'\n');             // modem ok?
  if(s1.indexOf("OK")<0)
  {
   delay(100);                         // wait a little bit
   s1=sendCmd("AT",2,'\n');            // modem ok?
   if(s1.indexOf("OK")<0) {
    status=SMSMOD_ERR_NOGT;
    return status;
   }
   delay(100);                         // wait a little bit
  }
  //-----2nd trial send command---------------------------------
  sResult=sendCmd(sCmd,1,'>');          // "send sms" to modem
  if(sResult.indexOf(">")<0) {
   status=SMSMOD_ERR_NOGT;
   return status;
  } 
 }
 //-----got input sign, send sms text---------------------------
 sResult=sendCmd(txt2,7,'\r');         // send text to modem
 if(sResult.indexOf("OK")<0)
  { status=SMSMOD_ERR_SEND; return status; }
 status=SMSMOD_OK;
 return status;
}

//_____did a sms come in?_______________________________________
// return: true=yes, false=no
bool SMSmodul::isSMS()
{
 SMS sms1=readSMS(numofSms1_);
 if(sms1.text!="") return true;
 return false;
}
/* 
 unsigned char c;                     // char
 bool bRet=false;                     // return value
 size_t len;

#if SMSMOD_SWS
 len=seri->available();
 if(len<1) return bRet;               // no char seceived
 //-----clear buffer--------------------------------------------
 delay(50);                           // wait a little bit
 while(len>0) {                       // while chars here...
  c=seri->read();                     // ...read char
  if(c==0x0D) bRet=true;              // SMS received
  len=seri->available();              //  more chars?
 };
#else
 len=Serial.available();
 if(len<1) return bRet;               // no char seceived
 //-----clear buffer--------------------------------------------
 delay(50);                           // wait a little bit
 while (len>0) {                      // while chars here...
  c=Serial.read();                    // ...read char
  if(c==0x0D) bRet=true;              // SMS received
  len=Serial.available();             // more chars?
 };
#endif
 return bRet;
}
*/

//_____read a certain SMS with given number_____________________
// return: SMS
SMS SMSmodul::readSMS(int num)
{
 SMS sms1;                             // result SMS
 String s1;                            // help string
 int iPos1, iPos2;                     // index SMS string
 if(num<0) 
  { status=SMSMOD_ERR_SNUM; return sms1; }
 sCmd="AT+CMGR="+String(num);          // read certain SMS
 sResult=sendCmd(sCmd, 6, '\r', SIMMOD_WAIT_SEC+2);
 //Serial.println(getsResult(false)); 
 if(sResult.indexOf("OK")<0) 
  { status=SMSMOD_ERR_READ; return sms1; }
 //-----take string to pieces-----------------------------------
 if(sResult.indexOf("CMGR:")<0)
 { status=SMSMOD_ERR_NOSM; return sms1; }
 int ok_=true;
 String phone_, date_, text_;
 iPos1=2+sResult.indexOf(",\"");
 iPos2=sResult.indexOf("\",", iPos1);
 if(iPos2>iPos1) phone_=sResult.substring(iPos1,iPos2);
 else ok_=false;
 iPos1=2+sResult.indexOf(",\"",iPos2+2);
 iPos2=sResult.indexOf("\"",iPos1+1);
 if(iPos2>iPos1) date_=sResult.substring(iPos1,iPos2);
 else ok_=false;
 iPos1=iPos2+3;
 iPos2=-1+sResult.indexOf("OK",iPos1+1);
 if(iPos2>iPos1) {
  while(((sResult.charAt(iPos2)=='\r')||
         (sResult.charAt(iPos2)=='\n'))&&iPos2>iPos1) iPos2--;
  text_=sResult.substring(iPos1,iPos2+1);
 }
 else ok_=false;
 if(!ok_) status=SMSMOD_ERR_READ;
 else {
  sms1.number=num;
  sms1.phone=phone_;
  sms1.date=date_;
  sms1.text=text_;
  status=SMSMOD_OK;
 }
 return sms1;
}

//_____read first SMS in used memory____________________________
SMS SMSmodul::readSMS1() { return(readSMS(numofSms1_)); }

//_____delete first SMS in used memory__________________________
// return: ERROR code
int SMSmodul::deleteSMS1() { return(deleteSMS(numofSms1_)); }

//**************************************************************
//    special functions
//**************************************************************

//_____set memory for sms_______________________________________
int SMSmodul::setMem(String mem) {
 if((mem=="SM")||(mem=="ME")||(mem=="MT")) {
  mem_=mem;
  if(mem_="ME") numofSms1_=21; else numofSms1_=1;
  sCmd="AT+CPMS=\""+mem_+"\",\""+mem_+"\",\""+mem_+"\"";
  sResult=sendCmd(sCmd);                // send command
  if(sResult.indexOf("OK")<0) status=SMSMOD_ERR_CPMS;
  else status=SMSMOD_OK;
  return status;
 }
 status=SMSMOD_ERR_NMEM; 
 return status;
}

//_____delete a certain SMS_____________________________________
// return: ERROR code
int SMSmodul::deleteSMS(int num)
{
 if(num<1) return SMSMOD_ERR_SNUM;     //
 sCmd="AT+CMGD="+String(num);          // read certain SMS
 sResult=sendCmd(sCmd,2,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,2,'\n');        // send command
  status=SMSMOD_ERR_CMGD;              // set status to error
  return status;                       //
 }
 status=SMSMOD_OK;                     // set status to OK
 return status;                        // 
}

//_____list all SMS in used memory______________________________
String SMSmodul::listAllSMS()
{
 int iNum=numberOfSMS();               //
 int sec=SIMMOD_WAIT_SEC+iNum/2;       // more time for answer
 sCmd="AT+CMGL=\"ALL\"";               // read all messages
 sResult=sendCmd(sCmd,(3*iNum+2),'\n',sec); // send command
 if(sResult.indexOf("OK")<0) status=SMSMOD_ERR_CMGL;
 else status=SMSMOD_OK;
 return sResult;
}

//_____number of saved SMS______________________________________
// return number of SMS or -1 on error
int SMSmodul::numberOfSMS()
{
 sCmd="AT+CPMS?";                      // command string
 int iPos1, iPos2, iNum;               // helper vars
 sResult=sendCmd(sCmd,4,'\n');         // send command
 if(sResult.indexOf("OK")<0) {         // try again 
  delay(100);                          // wait a little bit
  sResult=sendCmd(sCmd,4,'\n');        // send command
  status=SMSMOD_ERR_NSMS;              // set status to error
  return -1;                           //
 }
 iPos1=2+sResult.indexOf("\",");
 if(iPos1<0) { status=SMSMOD_ERR_NSMS; return -1; }
 iPos2=sResult.indexOf(",",iPos1);
 if((iPos2<0)||(iPos2<=iPos1))
  { status=SMSMOD_ERR_NSMS; return -1; }
 iNum=sResult.substring(iPos1, iPos2).toInt();
 status=SMSMOD_OK;
 return iNum;
}

//**************************************************************
//    helper functions
//**************************************************************

//_____get last command_________________________________________
String SMSmodul::getsCommand() { return sCmd; }

//_____result of last modem request_____________________________
// if replace_=true: replace \r by # and \n by ~
String SMSmodul::getsResult(bool raw_) { 
 if(raw_) return sResult; 
 String s1=sResult;
 s1.replace("\n", "~");
 s1.replace("\r", "#");
 return s1; 
}

//_____send a standard command to SIM800C_______________________
String SMSmodul::sendCmd(String cmd) { 
 return(sendCmd(cmd, 4, '\r', SIMMOD_WAIT_SEC));
}

//_____send a standard command to SIM800C_______________________
String SMSmodul::sendCmd(String cmd, int numEnd) { 
 return(sendCmd(cmd, numEnd, '\r', SIMMOD_WAIT_SEC));
}

//_____send a standard command to SIM800C_______________________
String SMSmodul::sendCmd(String cmd, int numEnd, char cEnd) { 
 return(sendCmd(cmd, numEnd, cEnd, SIMMOD_WAIT_SEC));
}

//_____send a command to SIM800C________________________________
// sEnd  : End-String (or character as String)
// numEnd: how often should end string be found in answer
// return: modem answer string or "" on error
String SMSmodul::sendCmd(String cmd, int numEnd, char cEnd, int sec)
{
 int    i=0;                           // receive byte counter
 char   c;                             // received byte
 String sRet="";                       // answer string
 String cmd2=cmd+SMSMOD_CRLF;          // command + carriage ret
 bool   finished=false;                // command finished
 int    len;                           // number of chars
 //-----just for safety: empty receive buffer-------------------
#if SMSMOD_SWS
 while((len=seri->available())>0) { seri->read(); } // read old
#else                                      
 while((len=Serial.available())>0) { Serial.read(); }
#endif
 delay(80);                            // wait a little bit
 //-----send command--------------------------------------------
#if SMSMOD_SWS
 seri->print(cmd2);                    // send command
#else
 Serial.print(cmd2);                   // send command
#endif
 delay(20);                            // wait a little bit
 //-----receive answer------------------------------------------
 unsigned long tEnd=sec*1000+millis(); // end time
 int cntEnd=0;                         // number of cr
 while(!finished && (millis()<tEnd)) 
 {
  yield();
  int len;
#if SMSMOD_SWS
  len=seri->available();
#else
  len=Serial.available();
#endif
  if(len>0) {
#if SMSMOD_SWS
   c=seri->read();                     // read char
#else
   c=Serial.read();                    // read char
#endif
   sRet+=String((char)c);              // add char to answer
   if(c==cEnd) cntEnd++;               // 
   if(cntEnd>=numEnd) finished=true;   // 
  }
  else
   delay(20);
 }
 return sRet;                          // return answer string
}

//_____count occurence of a specific string in another string___
int SMSmodul::countOccurrence1in2(String sFind, String sBasic)
{
 int iPos=0;
 int iNum=0;
 int iLen=sFind.length();
 while(sBasic.indexOf(sFind,iPos)>=0) {
  iPos=sBasic.indexOf(sFind, iPos)+iLen;
  iNum++;
 }
 return iNum;
}

//_____just for test: write a character to (software) serial____
void SMSmodul::write(char c) {
#if SMSMOD_SWS
 seri->write(c);
#else
 Serial.write(c);
#endif
}
