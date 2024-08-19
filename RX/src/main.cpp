/**************************************************************************************************
Filename: main.cpp

Description: This source file sets up the core functionality of the receiver units

Author: Alexandros Iliadis
Project: Wi-Fire (RX)
Date: July 2023
**************************************************************************************************/

#include <Arduino.h>
#include "utilities.h"
#include "receiver.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("\n============================================================================================");
    Serial.println("                                       EXECUTING PROGRAM                                      ");
    Serial.println("============================================================================================\n");
    initializeRX();
    for(byte i = 0; i < NUM_OF_CHANNELS; i++)
    {
        levels[i] = 1;
        pinMode(LDR_PINS[i],INPUT);
        digitalWrite(RED_PINS[i],HIGH);
        pinMode(RED_PINS[i],OUTPUT);
        digitalWrite(GREEN_PINS[i],HIGH);
        pinMode(GREEN_PINS[i],OUTPUT);
        digitalWrite(TRIGGER_PINS[i],LOW);
        pinMode(TRIGGER_PINS[i],OUTPUT);
    }
}

void loop()
{
    if(receiveData())
    {
        byte channel = packet.channel - 1;
        if(!strcmp(packet.message,"ARM"))
        {
            if(!strcmp(status[levels[channel]],"SET"))
            {
                levels[channel]++;
            }
            else if(!strcmp(status[levels[channel]],"ARM"))
            {
                levels[channel]--;
            }
        }
        if(!strcmp(packet.message,"PYR"))
        {
            if(!strcmp(status[levels[channel]],"ARM"))
            {
                levels[channel]++;
                timer[channel] = millis();
            }
        }
    }
    indicateStatus();
    for(byte i = 0; i < NUM_OF_CHANNELS; i++)
    {
        int ldr_value = analogRead(LDR_PINS[i]);
        if(!strcmp(status[levels[i]],"ONL"))
        {
            if(ldr_value >= THRESHOLD)
            {
                levels[i]++;
            }
        }
        if(!strcmp(status[levels[i]],"SET"))
        {
            if(ldr_value < THRESHOLD)
            {
                levels[i]--;
            }
        }
        if(!strcmp(status[levels[i]],"ARM"))
        {
            if(ldr_value < THRESHOLD)
            {
                levels[i] = 1;
            }
        }
        if(!strcmp(status[levels[i]],"PYR"))
        {
            digitalWrite(TRIGGER_PINS[i],HIGH);
            if(ldr_value < THRESHOLD || millis() - timer[i] >= FIRING_TIME)
            {
                digitalWrite(TRIGGER_PINS[i],LOW);
                levels[i] = 1;
                timer[i] = 0;
            }
        }
    }
}