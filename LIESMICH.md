# Praktische und einfache Hilfsklassen f&uuml;r den D1 mini
Sketch: -, Version 2020-12-10   
[English Version](./README.md "English Version")   

Dieses Repository enth&auml;lt Hilfsklassen f&uuml;r den Wemos D1 mini.   
Anwendungsbeispiele f&uuml;r diese Klassen befinden sich unter anderem im Repository `D1mini_oop`.   

__*Verwendung der Klassen*__   
1. Erstelle ein Verzeichnis `src` im aktuellen (Arduino) Arbeitsverzeichnis.   
2. Kopiere das Verzeichnis (oder die Verzeichnisse) mit den Quellcode-Dateien ins Verzeichnis `src`.   
3. F&uuml;ge die entsprechende `#include` Anweisung in die ino-Datei ein, zB
```
#include "src/dout/D1_class_Dout.h"
```

### Datenlogger-Klassen
Diese Klassen werden meist in Verwendung mit einem Datenlogger-Shield (microSD + DS1307RTC Shield) verwendet.   
| Klasse   | Zweck                                                        |
|----------|--------------------------------------------------------------|
| DS1307   | Hole/setze Datum und Uhrzeit bei Real Time Clock DS1307      |
| SDfile   | Dateimanagement auf micro SD card                            |
| TimeHttp | Hole Datum und Uhrzeit von einem Server mittels HTTP-Request |

### EPD-Klassen (electronic paper display)
Jedes Verzeichnis enth&auml;lt mehrere Klassen, die zur Ansteuerung der EPD direkt &uuml;ber SPI oder eine IS602-I2C-SPI-Br&uuml;cke notwendig sind:   
* die SPI-Verbindungsklasse `EpdConnection`,
* die Zeichenklassen `EpdPaint` und `EpdPainter`,
* eine Klasse zum Zeichnen einer Balken-Anzeige (`EpdPainterBar`) sowie
* die Anpassungsklasse an ein bestimmtes Display `Epd_` (Name siehe folgende Tabelle)

| Verzeichnis       | Zweck                                       |
|-------------------|---------------------------------------------|
| epd_0154bw        | Klasse Epd_ f&uuml;r ein zweif&auml;rbiges 1,54 Inch EPD (200x200 schwarz-wei&szlig;) |
| epd_0154red       | Klasse Epd_ f&uuml;r ein dreif&auml;rbiges 1,54 Inch EPD (200x200 schwarz-wei&szlig;-rot) |
| epd_0290bw        | Klasse Epd_ f&uuml;r ein zweif&auml;rbiges 2,90 Inch EPD (296x128 schwarz-wei&szlig;) |
| epd_i2c_0154bw    | Klasse Epd_ f&uuml;r ein zweif&auml;rbiges 1,54 Inch EPD (200x200 schwarz-wei&szlig;) &uuml;ber IS602-Br&uuml;cke |
| epd_i2c_ 0290bw   | Klasse Epd_ f&uuml;r ein zweif&auml;rbiges 2,90 Inch EPD (296x128 schwarz-wei&szlig;) &uuml;ber IS602-Br&uuml;cke |

### Epd Fonteditor   
Das Verzeichnis epd_fonteditor enth&auml;lt ods-Dateien zum Erstellen eigener Zeichen f&uuml;r ein E-Paper Display.   
Unterst&uuml;tzte Zeichengr&ouml;&szlig;en: 16x8, 20x11 und 24x11.   

### Font-Verzeichnis (Zeichens&auml;tze)
Das Verzeichnis `epd_fonts` enth&auml;lt die Datei `fonts.h` sowie C-Dateien mit Fonts f&uuml;r Electronic Paper Displays (EPD) mit verschiedenenen Zeichengr&ouml;&szlig;en:     
__ASCII-Werte 32..127__: font8.c (8x5), font12.c (12x7), font16.c (16x11), font20.c (20x14), font24.c (24x17); font_20x11.c (20x11), font_24x11.c (24x11)    
__ASCII-Werte 32..255__: font16x8_255.c (16x8), font20x11_255.c (20x11), font_24x11_255.c (24x11)   
__ASCII-Werte 32..255, Zeichen im Programmspeicher__: pmfont_24x11_255.c (24x11)   

### Verzeichnis "images"   
Das Verzeichnis enth&auml;lt verschiedene Bilder.

### Ein-/Ausgabe-Klassen
| Klasse   | Zweck                               |
|----------|-------------------------------------|
| Ain      | Einlesen des Analog-Eingangs (Pin A0) und Transformation der Werte in einen bestimmten Wertebereich  |
| Din      | Digitale Eingabe &nbsp; (Vorgabe: Taster an D3)       |
| Dout     | Digitale Ausgabe (Vorgabe: Blaue LED des D1mini)      |
| relay2   | Schalten eines Relais (ein | aus | um)   |   

### MQTT-Klassen 
| Klasse          | Zweck                        |
|-----------------|------------------------------|
| PubSubClient    | Klasse zum Senden und Empfangen von MQTT-Nachrichten &uuml;ber das WLAN |   
| MqttClientKH    | Erweiterung der Klasse `PubSubClient` zur einfacheren Daten&uuml;bertragung |   
| MqttClientKH2   | Diverse Verbesserungen der Klasse `MqttClientKH` (zB Trennung der WiFi- und MQTT-Methoden) |   
| SimpleMqtt      | Erweiterung der Klasse `PubSubClient` f&uuml;r ein einfaches Erstellen von MQTT-Anwendungen f&uuml;r D1mini und ESPD1mini. Es wird ein Basis-Topic definiert, Aktionen werden &uuml;ber  /get, und /set-Nachrichten durchgef&uuml;hrt und Antworten werden &uuml;ber /ret-Topics zur&uuml;ckgeschickt.   |   

### OLED-Klassen
OLED-Klassen dienen zur Text-Darstellung auf dem 0,66" D1 mini OLED Shield (SSD1306, 64x48, I2C, 7bit-Adresse 0x3C bzw. 0x3D). Es k&ouml;nnen maximal 6 Zeilen mit 10 Zeichen dargestellt werden.   
Besonderheit: char(158) = Euro-Zeichen statt Pt (Pesetas) (158=9E)   
Der Code basiert auf den Adafruit libs
* Adafruit_SSD1306-esp8266-64x48.zip und
* Adafruit-GFX-Library-1.1.5.zip   

Um Probleme mit installierten Klassen zu vermeiden, haben Namen ein vorgestelltes Underline-Zeichen _.

| Klasse       | Zweck    |
|--------------|----------|
| Screen1      | Klasse zur Anzeige von Text auf einem 0,66" gro&szlig;en OLED Shield.  |   
| Screen1a     | Enth&auml;lt die um das Scrollen erg&auml;nzte Klasse `Screen1` |   
| Screen_64x48 | Basisfunktionen nur f&uuml;r OLED shield 0,66" 64*48 pixel. |
| Screen096    | Klasse zur Anzeige von Text auf einem 0,96" gro&szlig;en OLED Shield.  |   


_Beispiele f&uuml;r Text-Bildschirme_   
* `screen6(3,"Demo",'l');`  ..... Schreiben des Textes "Demo" linksb&uuml;ndig in Zeile 3 des Bildschirms mit 6 Zeilen.
* `screen6i(4,"XXX",'r');`  ..... Schreiben des Textes "XXX" invertiert und rechtsb&uuml;ndig in Zeile 4 des Bildschirms mit 6 Zeilen.   
* `screen6iClear(1,"Demo",'c');`  ..... L&ouml;schen des Bildschirms, schreiben des Textes "Demo" invertiert und zentriert in die Zeile 1 des sechszeiligen Bildschirms.

_Scrollen_   
Die Bildschirme _screen6_, _screen5_, _screen4_ und _screen4B_ der Dateien `D1_class_Screen1a.h` und `D1_class_Screen1a.cpp` erm&ouml;glichen das Scrollen eines Textes. Dazu wird der Text in die n&auml;chste, nicht sichtbare Zeile geschrieben. (ZB bei screen6: Zeile 7 usw.)

### OLED Fonteditor
Das Verzeichnis `oled_fonteditor` enth&auml;lt ods-Dateien zum Erstellen eigener Zeichen f&uuml;r das OLED.   
Unterst&uuml;tzte Zeichengr&ouml;&szlig;en: 5x8.   

### Sensor-Klassen
| Klasse   | Zweck                          |   
|----------|--------------------------------|   
| AM2322   |  Klasse f&uuml;r den I2C Temperatur- und Feuchtigkeitssensor AM2322.   <br>Temperatur -40&deg;..+80&deg;C, +-0,5&deg;C/+-0,2&deg;C, 16bit; Feuchtigkeit 0%..99,0%, +-3%/+-0,1%, 16bit. I2C-Vorgabeadresse ist 0x5C. |   
| BH1750   | Klasse f&uuml;r den I2C Helligkeitssensor BH1750.   <br>I2C-Vorgabeadresse ist 0x23 (andere 0x5C). |   
| BME280   | Klasse f&uuml;r den I2C Temperatur-, Feuchtigkeits- und Druck-/H&ouml;hensensor BME280.   <br>Temperatur -40&deg;C...85&deg;C +-1&deg;, 0,01&deg;C Aufl&ouml;sung, Feuchtigkeit 0%...100% +-3%RH absolut, 0,008%RH Aufl&ouml;sung, Druck 300...1100hPa +-1,0hPa. I2C-Vorgabeadresse ist 0x76 (andere 0x77). |   
| SHT30    | Klasse f&uuml;r den I2C Temperatur- und Feuchtigkeitssensor SHT30.   <br>Temperatur -40&deg;C...125&deg;C +-0,7% (0&deg;..+65&deg;C, +-0,3&deg;C), Feuchtigkeit  +-3%RH. I2C-Vorgabeadresse ist 0x45 (andere 0x44). |   
### SIM-Klassen
| Klasse        | Zweck                               |
|---------------|-------------------------------------|
| GSMmodule     | Klasse zum Senden und Empfangen von SMS mittels SIM800C GSM GPRS module STM32.   <br>Wahl, ob Software- oder Hardware-serielle Schnittstelle im Konstruktor (Keine Angabe oder `true`: Software D5=Tx, D6=RX, `false`=Hardware Serial).  |     
| GSMmodule0    | Klasse zum Senden und Empfangen von SMS mittels SIM800C GSM GPRS module STM32.   <br>Wahl, ob Software- oder Hardware-serielle Schnittstelle mittels #define-Anweisung in der Datei `D1_class_GSMmodule0.h`:   <br>`#define GSMMOD_SWS true //software serial`<br>   Vorteil: Bei Hardware-Seriell weniger Speicherbedarf nach Kompilieren. Nachteil: Eingriff in Datei `D1_class_GSMmodule0.h` erforderlich.  |   
| GSMmodule2    | Klasse zum Senden und Empfangen von SMS mittels SIM800C GSM GPRS module STM32.   <br>Wahl, ob Software- oder Hardware-serielle Schnittstelle im Konstruktor (Keine Angabe oder `true`: Software D5=Tx, D6=RX, `false`=Hardware).   <br>Quellcode-Dateien f&uuml;r die Software-serielle Schnittstelle sind im Klassen-Verzeichnis gespeichert. |     

### Verschiedene Klassen 
| Klasse        | Zweck                               |
|---------------|-------------------------------------|
| statemachine  | Klasse zum einfachen Erstellen einer Statemaschine.   <br>Beispiele f&uuml;r Methoden sind<br> `Statemachine statemachine(STATE_MAX, STATE_DELAY);`, `int state=loopBegin();`, `switch(state)`, `unsigned long duration=loopEnd();` |   

