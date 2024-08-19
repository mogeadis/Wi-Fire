/**************************************************************************************************
Filename: transmitter.h

Description: This header file sets up the wireless communication of the transmitter unit

Author: Alexandros Iliadis
Project: Wi-Fire (TX)
Date: July 2023
**************************************************************************************************/

#ifndef TRANSMITTER_H
#define TRANSMITTER_H

// Include Libraries
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include "utilities.h"

// Define Macros
#define CE_PIN 9
#define CSN_PIN 10
#define MSG_SIZE 3
#define CHANNEL 121
#define ADDRESS_WIDTH 3
#define PA_LEVEL RF24_PA_MAX
#define DATA_RATE RF24_250KBPS
#define ACK_DELAY 4000
#define ACK_RETRIES 3

// Declare Variables
extern RF24 radio;
extern const byte tx_address[ADDRESS_WIDTH + 1];
extern const byte rx_address[ADDRESS_WIDTH + 1];
typedef struct
{
    byte node;
    byte channel;
    unsigned int id;
    char message[MSG_SIZE + 1];
} Data;
extern Data packet;
extern Data ack;
extern char payload[MSG_SIZE + 1];

// Declare Functions
void initializeTX();
bool transmitData();
void requestStatus(byte node,byte channel);
void armChannels(byte node,byte channel);
void fireChannels(byte node,byte channel);

#endif