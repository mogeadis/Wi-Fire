/**************************************************************************************************
Filename: utilities.h

Description: This header file sets up various functionalities of the transmitter unit

Author: Alexandros Iliadis
Project: Wi-Fire (TX)
Date: July 2023
**************************************************************************************************/

#ifndef UTILITIES_H
#define UTILITIES_H

// Include Libraries
#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Define Macros
#define RED_LED 6
#define GREEN_LED 5
#define KEYPAD_COLS 4
#define KEYPAD_ROWS 4
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDRESS 0x27
#define MSG_DELAY 2000
#define NUM_OF_NODES 3
#define CHANNELS_PER_NODE 2
#define NUM_OF_CHANNELS NUM_OF_NODES*CHANNELS_PER_NODE

// Declare Variables
extern char key;
extern char keys[KEYPAD_ROWS][KEYPAD_COLS];
extern byte row_pins[KEYPAD_ROWS];
extern byte col_pins[KEYPAD_COLS];
extern Keypad keypad;
extern LiquidCrystal_I2C lcd;
extern byte levels[NUM_OF_CHANNELS];
extern char status[5][4];
extern bool selected_channels[NUM_OF_CHANNELS];
extern byte custom1[8];
extern byte custom2[8];
extern byte custom3[8];
extern byte custom4[8];
extern byte custom5[8];
extern byte custom6[8];

// Declare Functions
void lcdMsg(const char msg[],byte col = 1,byte row = 1,byte clear = -1);
void lcdCustom(byte character,byte col,byte row);
byte charToByte(char CHAR);
byte getColorValue(byte ratio);
void indicateStatus();
void printStatus();

#endif