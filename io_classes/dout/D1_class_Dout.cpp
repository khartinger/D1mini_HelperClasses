//_____D1_class_Dout.cpp______________________170402-200414_____
// D1 mini class for digital output, e.g. leds.
// Default: pin D4=GPIO2 (blue led), output not inverted (0->0V)
//          value logical 0
// Changes 2017-12-03:
// + devide (old) D1_class_Dout.h into *.h and *.cpp
// + processing of invert_ now in on() / off() (instead of set)
// + toggle(), getDuration(), Dout(bool) added
//
// Hardware: (1) WeMos D1 mini
//
// Created by Karl Hartinger, December 03, 2017.
// Changes:
// * 2020-04-14 add start value to constructor
// Released into the public domain.

#include "D1_class_Dout.h"

//**************************************************************
//    constructor & co
//**************************************************************

//_____constructor (default digital out is D4, not inverted)____
Dout::Dout() { setup(D4, false, 0); }

//_____constructor with output pin number (=GPIO, not inverted)_
Dout::Dout(int num) { setup(num, false, 0); }

//_____constructor (default outpin is D4), set invert___________
// example: declare blue led on D1mini: Dout led_blue(true);
Dout::Dout(bool invert) { setup(D4, invert, 0); }

//_____constructor with pin number and set invert_______________
Dout::Dout(int num, bool invert) { setup(num, invert, 0); }

//_____constructor with pin number and start value______________
Dout::Dout(int num, int startvalue)
{ setup(num, false, startvalue); }

//_____constructor with pin number, set invert and start value__
Dout::Dout(int num, bool invert, int startvalue)
{ setup(num, invert, startvalue); }

//_____setup output pin_________________________________________
void Dout::setup(int num, bool invert, int startvalue)
{
 invert_=invert;                       // 
 doutNum_=num;                         // pin number (e.g. D4)
 pinMode(doutNum_, OUTPUT);            // set pin to output
 if(invert) {
  if(startvalue!=0) startvalue=0; else startvalue=1;
 } else
 {
  if(startvalue!=0) startvalue=1; else startvalue=0;
 }
 val_=1-startvalue;                    // force digitalWrite
 set(startvalue);                      // in set ;)
}

//**************************************************************
//     setter, getter, working methods
//**************************************************************

//_____set digital output pin physical: 0=0V, 1=3V3_____________
void Dout::set(int val)
{
 int vout_;
 if(val==val_) return;                 // nothing to change
 val_=val;                             // save new value
 lastMilli_=millis();                  // new start
 digitalWrite(doutNum_, val_);         // do output
}

//_____turn digital output logical on (can be 3V3 or 0V)________
void Dout::on(void)  { if(invert_) set(0); else set(1); }

//_____turn digital output logical off (can be 0V or 3V3)_______
void Dout::off(void) { if(invert_) set(1); else set(0); }

//_____toggle digital output____________________________________
void Dout::toggle(void) { set(1-val_); }

//_____get duration of this signal______________________________
unsigned long  Dout::getDuration(void) 
  { return (millis()- lastMilli_); }
