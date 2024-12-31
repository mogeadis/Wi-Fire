/**************************************************************************************************
Filename: receiver.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: Wi-Fire (RX)
Date: September 2023
**************************************************************************************************/

#include "receiver.h"

// Define Variables
RF24 radio(CE_PIN, CSN_PIN);
const byte tx_address[ADDRESS_WIDTH + 1] = "TX0";
const byte rx_address[ADDRESS_WIDTH + 1] = "RX0";
Data packet;
Data ack;
unsigned int last_id = 0;

// Define Functions
void initializeRX()
{
    Serial.println("SYSTEM BOOTING");
    if(radio.begin() && radio.isChipConnected())
    {
        Serial.println("SUCCESSFUL\n");
    }
    else
    {
        Serial.println("UNSUCCESSFUL\n");
        while(true){}
    }
    radio.enableDynamicAck();
    radio.setChannel(CHANNEL);
    radio.setPALevel(PA_LEVEL);
    radio.setDataRate(DATA_RATE);
    radio.setAddressWidth(ADDRESS_WIDTH);
    radio.openWritingPipe(tx_address);
    radio.openReadingPipe(1,rx_address);
    radio.startListening();
}

bool receiveData()
{
    bool new_data = false;
    if(radio.available())
    {
        radio.read(&packet,sizeof(packet));
        if(packet.node == THIS_NODE)
        {
            if(packet.id != last_id)
            {
                last_id = packet.id;
                new_data = true;
            }

            ack.id = packet.id;
            ack.node = packet.node;
            ack.channel = packet.channel;
            strcpy(ack.message,status[levels[ack.channel - 1]]);

            radio.stopListening();
            radio.write(&ack,sizeof(ack),true);
            radio.startListening();

            Serial.print("Received Packet: #");
            Serial.print(packet.id);
            Serial.print(" <");
            Serial.print(packet.message);
            Serial.print("> on Node ");
            Serial.print(packet.node);
            Serial.print(" (Channel ");
            Serial.print(packet.channel);
            Serial.print(")");
            Serial.print(" | Payload: <");
            Serial.print(ack.message);
            Serial.print(">");
            Serial.println();
        }
    }
    return new_data;
}