#ifndef PASSWORD_H
#define PASSWORD_H

// Include Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "utilities.h"

// Define Macros
#define RESET false
#define PASSWORD_LENGTH 4
#define DEFAULT_PASSWORD "0000"

// Declare Variables
extern char password[PASSWORD_LENGTH + 1];

// Declare Functions
void resetPassword();
void loadPassword();
void storePassword(char password[]);
void printPassword(char password[],bool mask = true);
void enterPassword();
void updatePassword();

#endif