#include "password.h"

//////////////////////////////////////////////////

// Define Variables
char password[PASSWORD_LENGTH+1];

//////////////////////////////////////////////////

// Define Functions
void reset_password()
{
    strcpy(password,DEFAULT_PASSWORD);
    if(RESET)
    {
        for(byte i = 0; i < PASSWORD_LENGTH; i++)
        {
            EEPROM.write(i,DEFAULT_PASSWORD[i]);
        }
        Serial.print("PASSWORD RESET");
        lcd_msg("PASSWORD RESET",2,1,0);
        delay(MSG_DELAY/2);
        Serial.print("RESTART DEVICE");
        lcd_msg("RESTART DEVICE",2,2);
        delay(MSG_DELAY/2);
        while(true){}
    } 
}

void load_password()
{
    for(byte i = 0; i < PASSWORD_LENGTH; i++)
    {
        password[i] = EEPROM.read(i);
    }
    password[PASSWORD_LENGTH] = '\0';
}

void store_password(char password[])
{
    for(byte i = 0; i < PASSWORD_LENGTH; i++)
    {
        EEPROM.write(i,password[i]);
    }
}

void print_password(char password[],bool mask)
{
    if(mask)
    {
        byte password_length = strlen(password);
        char masked_password[password_length + 1];

        memset(masked_password,'*',password_length);
        masked_password[password_length] = '\0';

        Serial.print(masked_password);
        Serial.print('\n');
        lcd_msg(masked_password,7,2,2);
    }
    else
    {
        Serial.print(password);
        Serial.print('\n');
        lcd_msg(password,7,2,2);
    }
}

void enter_password()
{
    char input_password[PASSWORD_LENGTH+1] = {'\0'};
    Serial.println("ENTER PASSWORD");
    lcd_msg("ENTER PASSWORD",2,1,1);
    print_password(input_password);

    while(true)
    {
        char key = keypad.getKey();
        if(key)
        {
            if((0 <= char_to_byte(key)) && (char_to_byte(key) <= 9))
            {
                if(strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    print_password(input_password);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                print_password(input_password);
            }
            else if(key == '#')
            {
                if(strcmp(input_password,password))
                {
                    if(strlen(input_password) == PASSWORD_LENGTH)
                    {
                        Serial.println("\nACCESS REFUSED\n");
                        lcd_msg("ACCESS REFUSED",2,1,0);
                        delay(MSG_DELAY);
                        Serial.println("ENTER PASSWORD");
                        lcd_msg("ENTER PASSWORD",2,1,0);
                    }
                }
                else
                {
                    Serial.println("\nACCESS GRANTED\n");
                    lcd_msg("ACCESS GRANTED",2,1,0); 
                    delay(MSG_DELAY);
                    break;
                }
                strcpy(input_password,"");
                print_password(input_password);
            }
        }
    }
    return;
}

void update_password()
{
    bool update = true;
    char input_password[PASSWORD_LENGTH+1] = {'\0'};
    Serial.println("OLD PASSWORD");
    lcd_msg("OLD PASSWORD",3,1,1);
    print_password(input_password);

    while(update)
    {
        char key = keypad.getKey();
        if(key)
        {
            if((0 <= char_to_byte(key)) && (char_to_byte(key) <= 9))
            {
                if (strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    print_password(input_password,true);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                print_password(input_password,true);
            }
            else if(key == '#')
            {
                if(strcmp(input_password,password))
                {
                    if(strlen(input_password) == PASSWORD_LENGTH)
                    {
                        Serial.println("\nWRONG PASSWORD");
                        lcd_msg("WRONG PASSWORD",2,1,0);
                        delay(MSG_DELAY);
                        Serial.println("\nOLD PASSWORD");
                        lcd_msg("OLD PASSWORD",3,1,0);
                    }
                }
                else
                {
                    Serial.println("\nNEW PASSWORD\n");
                    lcd_msg("NEW PASSWORD",3,1,0);
                    break;
                }
                strcpy(input_password,"");
                print_password(input_password);
            }
            else if(key == 'D')
            {
                Serial.println("CANCELLING UPDATE\n");
                lcd_msg("CANCELLING",4,1,0);
                lcd_msg("UPDATE",6,2,-1);
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
            if((0 <= char_to_byte(key)) && (char_to_byte(key) <= 9))
            {
                if(strlen(input_password) < PASSWORD_LENGTH)
                {
                    char digit[2] = {key,'\0'};
                    strcat(input_password,digit);
                    print_password(input_password,false);
                }
            }
            else if(key == '*')
            {
                input_password[strlen(input_password) - 1] = '\0';
                print_password(input_password,false);
            }
            else if(key == '#')
            {
                if(strlen(input_password) == PASSWORD_LENGTH)
                {
                    strcpy(password,input_password);
                    store_password(password);
                    Serial.println("\nSUCCESSFUL UPDATE\n");
                    lcd_msg("SUCCESSFUL",4,1,0);
                    lcd_msg("UPDATE",6,2,-1);
                    delay(MSG_DELAY);
                    break;
                }       
                strcpy(input_password,"");
                print_password(input_password);
            }
            else if(key == 'D')
            {
                Serial.println("CANCELLING UPDATE\n");
                lcd_msg("CANCELLING",4,1,0);
                lcd_msg("UPDATE",6,2,-1); 
                delay(MSG_DELAY);
                break;
            }
        }
    }
    return;
}

//////////////////////////////////////////////////