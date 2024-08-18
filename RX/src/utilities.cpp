#include "utilities.h"

// Define Variables
byte LDR_PINS[NUM_OF_CHANNELS] = {A1,A2};
byte RED_PINS[NUM_OF_CHANNELS] = {3,6};
byte GREEN_PINS[NUM_OF_CHANNELS] = {5,9};
byte TRIGGER_PINS[NUM_OF_CHANNELS] = {2,7};
byte levels[NUM_OF_CHANNELS] = {0};
char status[5][4] = {"OFF","ONL","SET","ARM","PYR"};
unsigned long timer[NUM_OF_CHANNELS] = {0};

// Define Functions
byte getColorValue(byte ratio)
{
    byte value;
    value = 255 - map(ratio,0,100,0,255);
    return value;
}

void indicateStatus()
{
    for(byte i = 0; i < NUM_OF_CHANNELS; i++)
    {
        byte red_value;
        byte green_value;
        if(!strcmp(status[levels[i]],"OFF"))
        {
            red_value = getColorValue(0);
            green_value = getColorValue(0);
        }
        else if(!strcmp(status[levels[i]],"ONL"))
        {
            red_value = getColorValue(100);
            green_value = getColorValue(0);
        }
        else if(!strcmp(status[levels[i]],"SET"))
        {
            red_value = getColorValue(100);
            green_value = getColorValue(15);
        }
        else if(!strcmp(status[levels[i]],"ARM"))
        {
            red_value = getColorValue(100);
            green_value = getColorValue(50);
        }
        else if(!strcmp(status[levels[i]],"PYR"))
        {
            red_value = getColorValue(0);
            green_value = getColorValue(50);
        }
        analogWrite(RED_PINS[i],red_value);
        analogWrite(GREEN_PINS[i],green_value);
    }
}