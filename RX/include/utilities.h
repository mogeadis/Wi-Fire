#ifndef UTILITIES_H
#define UTILITIES_H

//////////////////////////////////////////////////

// Include Libraries
#include <Arduino.h>

//////////////////////////////////////////////////

// Declare Variables
#define THRESHOLD 100
#define FIRING_TIME 3000
#define NUM_OF_CHANNELS 2

extern byte LDR_PINS[NUM_OF_CHANNELS];
extern byte RED_PINS[NUM_OF_CHANNELS];
extern byte GREEN_PINS[NUM_OF_CHANNELS];
extern byte TRIGGER_PINS[NUM_OF_CHANNELS];

extern byte levels[NUM_OF_CHANNELS];
extern char status[5][4];

extern unsigned long timer[NUM_OF_CHANNELS];

//////////////////////////////////////////////////

// Declare Functions
byte getColorValue(byte ratio);
void indicateStatus();

//////////////////////////////////////////////////

#endif