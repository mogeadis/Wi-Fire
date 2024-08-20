/**************************************************************************************************
Filename: main.cpp

Description: This source file sets up the core functionality of the transmitter unit

Author: Alexandros Iliadis
Project: Wi-Fire (TX)
Date: September 2023
**************************************************************************************************/

#include <Arduino.h>
#include "utilities.h"
#include "transmitter.h"
#include "password.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("\n============================================================================================");
    Serial.println("                                       EXECUTING PROGRAM                                      ");
    Serial.println("============================================================================================\n");
    lcd.init();
    lcd.clear();
    delay(500);
    lcd.backlight();
    lcd.createChar(1,custom1);
    lcd.createChar(2,custom2);
    lcd.createChar(3,custom3);
    lcd.createChar(4,custom4);
    lcd.createChar(5,custom5);
    lcd.createChar(6,custom6);
    initializeTX();
    digitalWrite(RED_LED,HIGH);
    digitalWrite(GREEN_LED,HIGH);
    pinMode(RED_LED,OUTPUT);
    pinMode(GREEN_LED,OUTPUT);
    resetPassword();
    loadPassword();
    enterPassword();
}

void loop()
{
    if(!key)
    {
        key = keypad.getKey();
    }
    if(key)
    {
        byte num_of_selected = 0;
        byte *selection = nullptr;
        switch(key)
        {
            default:
            {
                num_of_selected = 1;
                selection = new byte[num_of_selected]{charToByte(key)};
                break;
            }
            case '7':
            {
                num_of_selected = 2;
                selection = new byte[num_of_selected]{1,4};
                break;
            }
            case '8':
            {
                num_of_selected = 2;
                selection = new byte[num_of_selected]{2,5};
                break;
            }
            case '9':
            {
                num_of_selected = 2;
                selection = new byte[num_of_selected]{3,6};
                break;
            }
            case 'A':
            {
                num_of_selected = 3;
                selection = new byte[num_of_selected]{1,2,3};
                break;
            }
            case 'B':
            {
                num_of_selected = 3;
                selection = new byte[num_of_selected]{4,5,6};
                break;
            }
            case 'C':
            {
                num_of_selected = 6;
                selection = new byte[num_of_selected]{1,2,3,4,5,6};
                break;
            }
            case '#':
            {
                byte num_of_eligible = 0;
                byte num_of_armed = 0;  
                for(byte node = 1; node <= NUM_OF_NODES; node++)
                {
                    for(byte channel = 1; channel <= CHANNELS_PER_NODE; channel++)
                    {
                        byte current_channel = (node - 1) + (channel - 1)*NUM_OF_NODES;
                        if(selected_channels[current_channel] == 1 && (!strcmp(status[levels[current_channel]],"SET") || !strcmp(status[levels[current_channel]],"ARM")))
                        {
                            num_of_eligible++;
                        }
                        if(selected_channels[current_channel] == 1 && !strcmp(status[levels[current_channel]],"ARM"))
                        {
                            num_of_armed++;
                        }
                        if(selected_channels[current_channel] == 1 && !strcmp(status[levels[current_channel]],"SET"))
                        {
                            armChannels(node,channel);
                        }
                    } 
                }
                if(num_of_armed == num_of_eligible)
                {
                    for(byte node = 1; node <= NUM_OF_NODES; node++)
                    {
                        for(byte channel = 1; channel <= CHANNELS_PER_NODE; channel++)
                        {
                            byte current_channel = (node - 1) + (channel - 1)*NUM_OF_NODES;
                            if(selected_channels[current_channel] == 1 && !strcmp(status[levels[current_channel]],"ARM"))
                            {
                                armChannels(node,channel);
                            }
                        } 
                    }
                }
                break;
            }
            case '*':
            {
                for(byte node = 1; node <= NUM_OF_NODES; node++)
                {
                    for(byte channel = 1; channel <= CHANNELS_PER_NODE; channel++)
                    {
                        byte current_channel = (node - 1) + (channel - 1)*NUM_OF_NODES;
                        if(selected_channels[current_channel] == 1 && !strcmp(status[levels[current_channel]],"ARM"))
                        {
                            fireChannels(node,channel);
                        }
                    } 
                }
                break;
            }
            case '0':
            {
                digitalWrite(RED_LED,HIGH);
                digitalWrite(GREEN_LED,HIGH);
                lcdMsg("SYSTEM",6,1,0);
                lcdMsg("LOCKED",6,2,-1);
                Serial.println("SYSTEM LOCKED\n");
                while(true)
                {
                    char unlock_key = keypad.getKey();
                    if(unlock_key == '0')
                    {
                        enterPassword();
                        break;
                    }
                }
                break;
            }
            case 'D':
            {
                digitalWrite(RED_LED,HIGH);
                digitalWrite(GREEN_LED,HIGH);
                lcdMsg("PASSWORD",5,1,0);
                lcdMsg("UPDATE",6,2,-1);
                Serial.println("PASSWORD UPDATE\n");
                delay(MSG_DELAY);
                updatePassword();
                break;
            }
        }
        if(selection != nullptr)
        {
            for(byte i = 0; i < NUM_OF_CHANNELS; i++)
            {
                selected_channels[i] = 0;
            }
            for(byte i = 0; i < num_of_selected; i++)
            {
                selected_channels[selection[i] - 1] = 1;
            }
            for(byte node = 1; node <= NUM_OF_NODES; node++)
            {
                for(byte channel = 1; channel <= CHANNELS_PER_NODE; channel++)
                {
                    byte current_channel = (node - 1) + (channel - 1)*NUM_OF_NODES;
                    if(selected_channels[current_channel] == 1)
                    {
                        requestStatus(node,channel);
                    } 
                } 
            }
        }
        printStatus();
        indicateStatus();
        key = '\0';
        delete[] selection;
    }
}