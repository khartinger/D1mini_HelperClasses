# D1 mini: Verschiedene Hilfsklassen
Version 2018-10-05   
[English version](./README.md "English version")   

## Klasse Statemachine 

Die einfache Klasse Statemachine dient zum Erstellen eines Zustandsz&auml;hlers. Dieser z&auml;hlt von `1` bis zu `stateMax` und jeder Schritt dauert eine vorgegebene Zeit. 

### Verwendung
Zur Verwendung der Zustandsz&auml;hlers (statemachine) muss man lediglich ein Objekt definieren und zu Beginn und am Ende der `loop()`-Funktion die Methoden `loopBegin()` und `loopEnd()` aufrufen.
```   
Statemachine statemachine(STATE_MAX, STATE_DELAY);
//...
void loop() {
 int state=statemachine.loopBegin();
 //...do states...

 statemachine.loopEnd();
}
```   

### Klassendiagramm Statemachine

| Klasse Statemachine             |           |
| ------------------------------- | --------- |
| + Statemachine()                | Vorgabekonstruktor. Setzt stateMax und stateDelay auf Vorgabewerte (10, 200ms) |   
| <nobr>+ Statemachine(state_max, int state_delay)</nobr> | Konstruktor, setzt stateMax und stateDelay auf die angegebenen Werte |   
| ~ setup()                       | Setzt Eigenschaften auf Vorgabewerte (wird vom Konstruktor aufgerufen) |   
| __*Setter-/Gettermethoden*__ | <hr> |
| + setStateMax(int state_max)    | Setzt die maximale Z&auml;hlernummer |   
| + setStateDelay(int stateDelay) | Setzt die Wartezeit pro Zustand in Millisekunden (state) |   
| + int getStateMax()             | Liefert die Nummer des gr&ouml;&szlig;ten Zustands |   
| + int  getStateDelay()          | Liefert die eingestellte Wartezeit pro Zustand in Millisekunden |   
| + int getState()                | Liefert die Nummer des aktuellen Zustands |   
| + int getDuration()             | Liefert die aktuelle Dauer des derzeitigen Zustands in Millisekunden |   
| __*Arbeitsmethoden*__ | <hr> |
| + int loopBegin()               | Aufruf zu Beginn der loop()-Funktion. Startet die Zeitmessung und liefert die Nummer des States zur&uuml;ck.  |   
| + unsigned long loopEnd()       | Aufruf am Ende er loop()-Funktion. Erh&ouml;ht den Z&auml;hlerstand und liefert die Dauer des aktuellen Zustands in Millisekunden. (Sollte stateDelay sein) |   

&nbsp;

|  *Eigenschaften*            |                                            |
| --------------------------- | ------------------------------------------ |
| ~ int stateCounter          | Z&auml;hler (z&auml;hlt von 1 bis stateMax) |   
| ~ int stateMax              | Maximalwert des Z&auml;hlers  |   
| ~ int stateDelay            | Wartezeit pro Zustand (State) |   
| ~ unsigned long beginMillis | Startzeit des Loops in ms |
