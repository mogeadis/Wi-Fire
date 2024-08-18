#ifndef RECEIVER_H
#define RECEIVER_H

// Include Libraries
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include "utilities.h"

// Define Macros
#define CE_PIN 8
#define CSN_PIN 10
#define MSG_SIZE 3
#define CHANNEL 121
#define ADDRESS_WIDTH 3
#define PA_LEVEL RF24_PA_MAX
#define DATA_RATE RF24_250KBPS
#define THIS_NODE 1

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
extern unsigned int last_id;

// Declare Functions
void initializeRX();
bool receiveData();

#endif