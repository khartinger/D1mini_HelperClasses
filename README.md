# Comfortable and simple D1 mini helper classes
Sketch: -, Version 2019-01-09   
[Deutsche Version](./LIESMICH.md "Deutsche Version")   

This repository contains a lot of helper classes for the Wemos D1 mini.    
Example programs for how to use the classes see repository `D1mini_oop`.

__*How to use the classes*__   
1. Make a directory `src` inside the (Arduino) working directory.   
2. Copy directory (or directories) that contain the source code into directory `src`.   
3. Add `#include` line in ino file like   
```
#include "src/dout/D1_class_Dout.h"
```

### Data logger classes
This classes often are used for the D1 mini data logger shield (microSD + DS1307RTC Shield).   
| class      | purpose   |
|------------|-----------|
| DS1307     | get/set date and time from/to real time clock DS1307 |
| SDfile     | file management on micro SD card                     |
| TimeHttp   | get date and time from a server by http request      |

### EPD-classes (electronic paper display)
Every directory contains some classes for controlling a EPD by SPI or over a IS602-I2C-SPI-bridge:   
* SPI connection class `EpdConnection`,
* paint classes `EpdPaint` and `EpdPainter`,
* class for painting a bar (`EpdPainterBar`) and
* class to adjust a certain display `Epd_` (names see table below)

| directory         | purpose                                       |
|-------------------|---------------------------------------------|
| epd_0154bw        | class Epd_ for 2-color 1.54 inch EPD (200x200 black-white) |
| epd_0154red       | class Epd_ for 3-color 1.54 inch EPD (200x200 black-white-red) |
| epd_0290bw        | class Epd_ for 2-color 2.90 inch EPD (296x128 black-white) |
| epd_i2c_0154bw    | class Epd_ for 2-color 1.54 inch EPD (200x200 black-white) and IS602 bridge |
| epd_i2c_ 0290bw   | class Epd_ for 2-color 2.90 inch EPD (296x128 black-white) and IS602 bridge |

###Epd font editor   
The directory epd_fonteditor contains ods-files to generate your own characters for a  e-paper display.   
Character sizes: 16x8, 20x11 and 24x11.   

###Font directory
The directory `epd_fonts` contains the file `fonts.h`and c files with fonts for electronic paper displays (EPD) with different char sizes:     
__ASCII values 32..127__: font8.c (8x5), font12.c (12x7), font16.c (16x11), font20.c (20x14), font24.c (24x17); font_20x11.c (20x11), font_24x11.c (24x11)    
__ASCII values 32..255__: font16x8_255.c (16x8), font20x11_255.c (20x11), font_24x11_255.c (24x11)   
__ASCII values 32..255, characters in program memory__: pmfont_24x11_255.c (24x11)   

###Directory "images"   
The directory contains some picures.

###Input/output classes
| class   | purpose                             |
|---------|-------------------------------------|
| Ain     | analog input &nbsp; (Default: Pin A0)                 |
| Din     | digital input &nbsp; (Default: Button at D3)         |
| Dout    | digital output (Default: blue LED on D1mini) &nbsp;  |

###MQTT classes 
| class          | purpose                      |
|----------------|------------------------------|
| PubSubClient    | class to send and receive MQTT messages by WLAN |   
| MqttClientKH    | Extension of class `PubSubClient` for easy data transmission |   

###OLED classes
OLED classes are used to display text on a 0.66" D1 mini OLED shield (SSD1306, 64x48, I2C, 7bit-address 0x3C or 0x3D). Only 6 lines with 10 chars can be displayed.   
Special: char(158) = Euro sign instead of Pt (Pesetas) (158=9E)   
The code is strongly based on Adafruit libs   
* Adafruit_SSD1306-esp8266-64x48.zip and
* Adafruit-GFX-Library-1.1.5.zip   

To avoid problems with installed classes, Adafruit names in this class have a leading underline.   
Use this class, if you have problems with the Adafruit classes especially after an update of the libraries.

| class       | purpose    |
|--------------|----------|
| Screen1      | class to display text on a 0.66" OLED shield.  |   
| Screen1a     | Extended class `Screen1` for scrolling. |   
| Screen_64x48 | Basic functions for OLED shield 0.66" 64x48 pixel. |

_Examples_
* `screen6(3,"Demo",'l');`  ..... Write the text "Demo" with align left in line 3 of a screen with 6 lines.    
* `screen6i(4,"XXX",'r');`  ..... Write the text "XXX" inverted with align right in line 4 of a screen with 6 lines.    
* `screen6iClear(1,"Demo",'c');`  ..... Clear display, then write the text "Demo" inverted and centered in line 1 of a screen with 6 lines.    

### Scrolling
The screens _screen6_, _screen5_, _screen4_ and _screen4B_ located in the files  `D1_class_Screen1a.h` and `D1_class_Screen1a.cpp` allow scrolling a text. Write the text in the next, invisible line. (Eg for screen6: line 7 and so on.)

### OLED font editor
Directory `oled_fonteditor` contains ods-files to create your own characters for a OLED.   
Character size(s): 5x8.   

###Sensor classes
| class    | purpose                        |
|----------|--------------------------------|
| AM2322   |  Class for temperature and humidity i2c sensor AM2322.   <br>Temperature -40&deg;..+80&deg;C, +-0,5&deg;C/+-0,2&deg;C, 16bit; Humidity 0%..99,0%, +-3%/+-0,1%, 16bit. Default i2c address is 0x5C. |
| BH1750   | Class for i2c digital light sensor BH1750.   <br>Default i2c address is 0x23 (other option 0x5C). |
| BME280   | Class for temperature, humidity and pressure/altitude i2c sensor BME280.   <br>Temperature -40&deg;C...85&deg;C +-1&deg;, 0,01&deg;C resolution, humidity 0%...100% +-3%RH absolut, 0,008%RH resolution, pressure 300...1100hPa +-1,0hPa. Default i2c address is 0x76 (other 0x77). |
| SHT30    | Class for temperature and humidity i2c sensor SHT30.   <br>Temperature -40&deg;C...125&deg;C +-0,7% (0&deg;..+65&deg;C, +-0,3&deg;C),     Humidity  +-3%RH. Default i2c address is 0x45 (other 0x44). |

###SIM classes

| class         | purpose                        |
|---------------|--------------------------------|
| GSMmodule     | D1 mini class for sending and receiving SMS with a SIM800C GSM GPRS module STM32.   <br>Select software or hardware serial by constructor: No value or `true` selects software serial (D5=Tx, D6=RX), `false` selects hardware serial |     
| GSMmodule0    | D1 mini class for sending and receiving SMS with a SIM800C GSM GPRS module STM32.   <br>Select software or hardware serial by #define-command in file `D1_class_GSMmodule0.h`:   <br>`#define GSMMOD_SWS true //software serial`<br>Advantage: hardware serial needs less memory after compiling. Disadvantage: You have to edit file `D1_class_GSMmodule0.h` |
| GSMmodule     | D1 mini class for sending and receiving SMS with a SIM800C GSM GPRS module STM32.   <br>Select software or hardware serial by constructor: No value or `true` selects software serial (D5=Tx, D6=RX), `false` selects hardware serial.   <br>Class directory also contains source code for software serial. |     

###Miscellaneous classes 
| class         | purpose                             |
|---------------|-------------------------------------|
| statemachine  | class to create a statemachine.   <br>Examples for methodes:<br> `Statemachine statemachine(STATE_MAX, STATE_DELAY);`, `int state=loopBegin();`, `switch(state)`, `unsigned long duration=loopEnd();` |   
  
