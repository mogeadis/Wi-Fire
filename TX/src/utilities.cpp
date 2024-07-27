#include "utilities.h"

//////////////////////////////////////////////////

// Define Variables
char key = 'C';
char keys[KEYPAD_ROWS][KEYPAD_COLS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte row_pins[KEYPAD_ROWS] = {8,7,4,3};
byte col_pins[KEYPAD_COLS] = {A0,A1,A2,A3};
Keypad keypad = Keypad(makeKeymap(keys),row_pins,col_pins,KEYPAD_ROWS,KEYPAD_COLS);
LiquidCrystal_I2C lcd(LCD_ADDRESS,LCD_COLS,LCD_ROWS);

byte levels[NUM_OF_CHANNELS] = {0};
char status[5][4] = {"OFF","ONL","SET","ARM","PYR"};

bool selected_channels[NUM_OF_CHANNELS] = {0};

byte custom1[8] =
{
	0b00100,
	0b01100,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b01110,
	0b11111
};
byte custom2[8] =
{
	0b01110,
	0b10001,
	0b00001,
	0b00010,
	0b00100,
	0b01000,
	0b11111,
	0b11111
};
byte custom3[8] =
{
	0b11111,
	0b00010,
	0b00100,
	0b00010,
	0b00001,
	0b10001,
	0b01110,
	0b11111
};
byte custom4[8] =
{
	0b00010,
	0b00110,
	0b01010,
	0b10010,
	0b11111,
	0b00010,
	0b00010,
	0b11111
};
byte custom5[8] =
{
	0b11111,
	0b10000,
	0b11110,
	0b00001,
	0b00001,
	0b10001,
	0b01110,
	0b11111
};
byte custom6[8] =
{
	0b00110,
	0b01000,
	0b10000,
	0b11110,
	0b10001,
	0b10001,
	0b01110,
	0b11111
};

//////////////////////////////////////////////////

// Define Functions
void lcdMsg(const char msg[],byte col,byte row,byte clear)
{
    char clear_line[LCD_COLS];
    memset(clear_line,' ',LCD_COLS);
    switch(clear)
    {
        case 0:
        {
            lcd.clear();
            break;
        }
        case 1:
        {
            lcd.setCursor(0,0);
            lcd.print(clear_line);
            break;
        }
        case 2:
        {
            lcd.setCursor(0,1);
            lcd.print(clear_line);
            break;
        }
        default:
        {
            break;
        }
    }
    lcd.setCursor(col - 1,row - 1);
    lcd.print(msg);
}

void lcdCustom(byte character,byte col,byte row)
{
    lcd.setCursor(col - 1,row - 1);
    lcd.write(character);
}

byte charToByte(char CHAR)
{
    byte BYTE = CHAR - '0';
    return BYTE;
}

byte getColorValue(byte ratio)
{
    byte value;
    value = 255 - map(ratio,0,100,0,255);
    return value;
}

void indicateStatus()
{
    byte max_level = 0;
    for(byte i = 0; i < 6; i++)
    {
        if(selected_channels[i] == 1)
        {
            max_level = max(levels[i],max_level);
        }    
    }

    byte red_value;
    byte green_value;
    if(!strcmp(status[max_level],"OFF"))
    {
        red_value = getColorValue(0);
        green_value = getColorValue(0);
    }
    else if(!strcmp(status[max_level],"ONL"))
    {
        red_value = getColorValue(100);
        green_value = getColorValue(0);
    }
    else if(!strcmp(status[max_level],"SET"))
    {
        red_value = getColorValue(100);
        green_value = getColorValue(10);
    }
    else if(!strcmp(status[max_level],"ARM"))
    {
        red_value = getColorValue(100);
        green_value = getColorValue(50);
    }
    else if(!strcmp(status[max_level],"PYR"))
    {
        red_value = getColorValue(0);
        green_value = getColorValue(50);
    }
    
    analogWrite(RED_LED,red_value);
    analogWrite(GREEN_LED,green_value);
}

void printStatus()
{
    lcd.clear();
    Serial.println();
    byte col,row;
    for(byte i = 0; i < NUM_OF_CHANNELS; i++)
    {
        switch(i + 1)
        {
            case 1:
            {
                col = 2;
                row = 1;
                break;
            }
            case 2:
            {
                col = 7;
                row = 1;
                break;
            }
            case 3:
            {
                col = 12;
                row = 1;
                break;
            }
            case 4:
            {
                col = 2;
                row = 2;
                break;
            }
            case 5:
            {
                col = 7;
                row = 2;
                break;
            }
            case 6:
            {
                col = 12;
                row = 2;
                break;
            } 
        }
        Serial.print(i + 1);
        Serial.print(status[levels[i]]);
        Serial.print(" ");
        lcd.setCursor(col - 1,row - 1);
        lcd.print(i + 1);
        lcd.print(status[levels[i]]);
        if(selected_channels[i] == 1)
        {
            lcdCustom(i + 1,col,row);
        }
    }
    Serial.println('\n');
}

//////////////////////////////////////////////////