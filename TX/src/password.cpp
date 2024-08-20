/**************************************************************************************************
Filename: password.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: Wi-Fire (TX)
Date: September 2023
**************************************************************************************************/

#include "password.h"

// Define Variables
char password[PASSWORD_LENGTH + 1];

// Define Functions
void resetPassword()
{
    strcpy(password,DEFAULT_PASSWORD);
    if(RESET)
    {
        for(byte i = 0; i < PASSWORD_LENGTH; i++)
        {
            EEPROM.write(i,DEFAULT_PASSWORD[i]);
        }
        Serial.print("PASSWORD RESET");
        lcdMsg("PASSWORD RESET",2,1,0);
        delay(MSG_DELAY/2);
        Serial.print("RESTART DEVICE");
        lcdMsg("RESTART DEVICE",2,2);
        delay(MSG_DELAY/2);
        while(true){}
    } 
}

void loadPassword()
{
    for(byte i = 0; i < PASSWORD_LENGTH; i++)
    {
        password[i] = EEPROM.read(i);
    }
    password[PASSWORD_LENGTH] = '\0';
}

void storePassword(char password[])
{
    for(byte i = 0; i < PASSWORD_LENGTH; i++)
    {
        EEPROM.write(i,password[i]);
    }
}

void printPassword(char password[],bool mask)
{
    if(mask)
    {
        byte password_length = strlen(password);
        char masked_password[password_length + 1];

        memset(masked_password,'*',password_length);
        masked_password[password_length] = '\0';

        Serial.print(masked_password);
        Serial.print('\n');
        lcdMsg(masked_password,7,2,2);
    }
    else
    {
        Serial.print(password);
        Serial.print('\n');
        lcdMsg(password,7,2,2);
    }
}

void enterPassword()
{
    char input_password[PASSWORD_LENGTH + 1] = {'\0'};
    Serial.println("ENTER PASSWORD");
    lcdMsg("ENTER PASSWORD",2,1,1);
    printPassword(input_password);
    while(true)
    {
        char key = keypad.getKey();
        if(key)
        {
            if((0 <= charToByte(key)) && (charToByte(key) <= 9))
            {
                if(strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    printPassword(input_password);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                printPassword(input_password);
            }
            else if(key == '#')
            {
                if(strcmp(input_password,password))
                {
                    if(strlen(input_password) == PASSWORD_LENGTH)
                    {
                        Serial.println("\nACCESS REFUSED\n");
                        lcdMsg("ACCESS REFUSED",2,1,0);
                        delay(MSG_DELAY);
                        Serial.println("ENTER PASSWORD");
                        lcdMsg("ENTER PASSWORD",2,1,0);
                    }
                }
                else
                {
                    Serial.println("\nACCESS GRANTED\n");
                    lcdMsg("ACCESS GRANTED",2,1,0); 
                    delay(MSG_DELAY);
                    break;
                }
                strcpy(input_password,"");
                printPassword(input_password);
            }
        }
    }
    return;
}

void updatePassword()
{
    bool update = true;
    char input_password[PASSWORD_LENGTH + 1] = {'\0'};
    Serial.println("OLD PASSWORD");
    lcdMsg("OLD PASSWORD",3,1,1);
    printPassword(input_password);
    while(update)
    {
        char key = keypad.getKey();
        if(key)
        {
            if((0 <= charToByte(key)) && (charToByte(key) <= 9))
            {
                if (strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    printPassword(input_password,true);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                printPassword(input_password,true);
            }
            else if(key == '#')
            {
                if(strcmp(input_password,password))
                {
                    if(strlen(input_password) == PASSWORD_LENGTH)
                    {
                        Serial.println("\nWRONG PASSWORD");
                        lcdMsg("WRONG PASSWORD",2,1,0);
                        delay(MSG_DELAY);
                        Serial.println("\nOLD PASSWORD");
                        lcdMsg("OLD PASSWORD",3,1,0);
                    }
                }
                else
                {
                    Serial.println("\nNEW PASSWORD\n");
                    lcdMsg("NEW PASSWORD",3,1,0);
                    break;
                }
                strcpy(input_password,"");
                printPassword(input_password);
            }
            else if(key == 'D')
            {
                Serial.println("CANCELLING UPDATE\n");
                lcdMsg("CANCELLING",4,1,0);
                lcdMsg("UPDATE",6,2,-1);
                delay(MSG_DELAY);
                update = false;
                break;
            }
        }
    }
    strcpy(input_password,"");
    while(update)
    {
        char key = keypad.getKey();
        if(key)
        {
            if((0 <= charToByte(key)) && (charToByte(key) <= 9))
            {
                if(strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    printPassword(input_password,false);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                printPassword(input_password,false);
            }
            else if(key == '#')
            {
                if(strlen(input_password) == PASSWORD_LENGTH)
                {
                    strcpy(password,input_password);
                    storePassword(password);
                    Serial.println("\nSUCCESSFUL UPDATE\n");
                    lcdMsg("SUCCESSFUL",4,1,0);
                    lcdMsg("UPDATE",6,2,-1);
                    delay(MSG_DELAY);
                    break;
                }       
                strcpy(input_password,"");
                printPassword(input_password);
            }
            else if(key == 'D')
            {
                Serial.println("CANCELLING UPDATE\n");
                lcdMsg("CANCELLING",4,1,0);
                lcdMsg("UPDATE",6,2,-1); 
                delay(MSG_DELAY);
                break;
            }
        }
    }
    return;
}