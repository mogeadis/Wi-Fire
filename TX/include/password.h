#ifndef PASSWORD_H
#define PASSWORD_H

//////////////////////////////////////////////////

// Include Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "utilities.h"

//////////////////////////////////////////////////

// Declare Variables
#define RESET false
#define PASSWORD_LENGTH 4
#define DEFAULT_PASSWORD "0000"
extern char password[PASSWORD_LENGTH+1];

//////////////////////////////////////////////////

// Declare Functions
void reset_password();
void load_password();
void store_password(char password[]);
void print_password(char password[],bool mask = true);
void enter_password();
void update_password();

//////////////////////////////////////////////////

#endif