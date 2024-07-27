#include "transmitter.h"

//////////////////////////////////////////////////

// Define Variables
RF24 radio(CE_PIN,CSN_PIN);
const byte tx_address[ADDRESS_WIDTH + 1] = "TX0";
const byte rx_address[ADDRESS_WIDTH + 1] = "RX0";

Data packet;
Data ack;
char payload[MSG_SIZE + 1] = "OFF";

//////////////////////////////////////////////////

// Define Functions
void initializeTX()
{
    Serial.println("SYSTEM BOOTING");
    lcdMsg("SYSTEM BOOTING",2,1,0);
    delay(MSG_DELAY/2);
    if(radio.begin() && radio.isChipConnected())
    {
        Serial.println("SUCCESSFUL\n");
        lcdMsg("SUCCESSFUL",4,2);
        delay(MSG_DELAY);
    }
    else
    {
        Serial.println("UNSUCCESSFUL\n");
        lcdMsg("UNSUCCESSFUL",3,2);
        delay(MSG_DELAY);
        while (true){}
    }
    radio.enableDynamicAck();
    radio.setChannel(CHANNEL);
    radio.setPALevel(PA_LEVEL);
    radio.setDataRate(RF24_250KBPS);
    radio.setAddressWidth(ADDRESS_WIDTH);
    radio.openWritingPipe(rx_address);
    radio.openReadingPipe(1, tx_address);
    packet.id = 0;
}

bool transmitData()
{
    byte retries;
    bool success;
    char result[8];
    unsigned long msg_t0, msg_t1, msg_dt;
    unsigned long ack_t0, ack_t1, ack_dt;

    ack_dt = 0;
    retries = 0;
    success = false;
    strcpy(payload,"OFF");
    strcpy(result,"Failure");

    msg_t0 = micros();
    radio.stopListening();
    radio.write(&packet,sizeof(packet),true);
    ack_t0 = micros();
    while(!success && retries < ACK_RETRIES)
    {
        if(ack_dt > ACK_DELAY)
        {
            retries++;
            radio.stopListening();
            radio.write(&packet,sizeof(packet),true);
            ack_t0 = micros();
        }
        radio.startListening();
        if(radio.available())
        {
            radio.read(&ack,sizeof(ack));
            if(ack.id == packet.id && ack.node == packet.node && ack.channel == packet.channel)
            {
                success = true;
                strcpy(result,"Success");
                strcpy(payload,ack.message);
            }
        }
        ack_t1 = micros();
        ack_dt = ack_t1 - ack_t0;
    }
    msg_t1 = micros();
    msg_dt = msg_t1 - msg_t0;

    Serial.print("Sent Packet: #");
    Serial.print(packet.id);
    Serial.print(" <");
    Serial.print(packet.message);
    Serial.print("> to Node ");
    Serial.print(packet.node);
    Serial.print(" (Channel ");
    Serial.print(packet.channel);
    Serial.print(") | Time Elapsed: ");
    Serial.print(msg_dt);
    Serial.print("us (");
    Serial.print(retries);
    Serial.print(" Retries) | Result: ");
    Serial.print(result);
    Serial.print(" | Payload: <");
    Serial.print(payload);
    Serial.print(">");
    Serial.println();

    return success;
}

void requestStatus(byte node,byte channel)
{
    packet.id++;
    packet.node = node;
    packet.channel = channel;
    strcpy(packet.message,"REQ");
    transmitData();

    byte current_channel;
    current_channel = (node - 1) + (channel - 1) * NUM_OF_NODES;
    if(!strcmp(payload,"OFF"))
    {
        levels[current_channel] = 0;
    }
    if(!strcmp(payload,"ONL"))
    {
        levels[current_channel] = 1;
    }
    if(!strcmp(payload,"SET"))
    {
        levels[current_channel] = 2;
    }
    if(!strcmp(payload,"ARM"))
    {
        levels[current_channel] = 3;
    }
    if(!strcmp(payload,"PYR"))
    {
        levels[current_channel] = 4;
    }
}

void armChannels(byte node,byte channel)
{
    packet.id++;
    packet.node = node;
    packet.channel = channel;
    strcpy(packet.message,"ARM");
    transmitData();

    byte current_channel;
    current_channel = (node - 1) + (channel - 1) * NUM_OF_NODES;
    if(!strcmp(payload,"OFF"))
    {
        levels[current_channel] = 0;
    }
    if(!strcmp(payload,"ONL"))
    {
        levels[current_channel] = 1;
    }
    if(!strcmp(payload,"SET"))
    {
        levels[current_channel] = 3;
    }
    if(!strcmp(payload,"ARM"))
    {
        levels[current_channel] = 2;
    }
}

void fireChannels(byte node,byte channel)
{
    packet.id++;
    packet.node = node;
    packet.channel = channel;
    strcpy(packet.message,"PYR");
    transmitData();

    byte current_channel;
    current_channel = (node - 1) + (channel - 1) * NUM_OF_NODES;
    if(!strcmp(payload,"OFF"))
    {
        levels[current_channel] = 0;
    }
    if(!strcmp(payload,"ONL"))
    {
        levels[current_channel] = 1;
    }
    if(!strcmp(payload,"SET"))
    {
        levels[current_channel] = 2;
    }
    if(!strcmp(payload,"ARM"))
    {
        levels[current_channel] = 4;
    }
}

//////////////////////////////////////////////////