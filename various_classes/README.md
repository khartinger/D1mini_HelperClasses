# D1 mini: Various helper classes
Version 2018-10-05   
[German version](./LIESMICH.md "German version")   

## State machine

The simple class statemachine helps to make a state counter, that counts from `1` to `stateMax`. Every step lasts a given time. 

### Usage
To build a statemachine define a object and call the methods `loopBegin()` and `loopEnd()` at the beginning and end of function `loop()`.
```   
Statemachine statemachine(STATE_MAX, STATE_DELAY);
//...
void loop() {
 int state=statemachine.loopBegin();
 //...do states...

 statemachine.loopEnd();
}
```   

### Class diagram Statemachine

| class Statemachine              |           |
| ------------------------------- | --------- |
| + Statemachine()                | Default constructor. Sets stateMax and stateDelay to default values (10, 200ms) |   
| <nobr>+ Statemachine(state_max, int state_delay)</nobr> | Constructor, that sets stateMax and stateDelay to given values |   
| ~ setup()                       | Set properties to default values (called by constructors) |   
| __*Setter-/Gettermethodes*__ | <hr> |
| + setStateMax(int state_max)    | Set maximum counter value |   
| + setStateDelay(int stateDelay) | Set delay time of every state (milliseconds) |   
| + int getStateMax()             | Get maximum value of state counter |   
| + int  getStateDelay()          | Get delay time per state (milliseconds) |   
| + int getState()                | Get number of this state |   
| + int getDuration()             | Get duration of this state until this moment (milliseconds) |   
| __*Arbeitsmethoden*__ | <hr> |
| + int loopBegin()               | Call method at beginning of loop()-function. Starts time measuring and returns number of state.  |   
| + unsigned long loopEnd()       | Call method at end of loop()-function. Increases counter value and returns duration of this state im milliseconds. (Should be  stateDelay) |   

&nbsp;

|  *properties*               |                                            |
| --------------------------- | ------------------------------------------ |
| ~ int stateCounter          | counter (counts from 1 to stateMax) |   
| ~ int stateMax              | counter maximum value  |   
| ~ int stateDelay            | delay per state |   
| ~ unsigned long beginMillis | start time of loop in ms |
