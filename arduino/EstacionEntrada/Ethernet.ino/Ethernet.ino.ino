#include <UIPEthernet.h>
#include <SPI.h>

uint8_t myIP[] = { 10, 20, 184, 127 };
uint8_t sndIP[] = { 8, 8, 8, 8 };
uint8_t myMAC[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

uint16_t rcvPort = 27000;
uint16_t sndPort = 27000;

byte sndBuffer[256];
byte rcvBuffer[256];

EthernetUDP udp;

void setup()
{
    Serial.begin(115200);
    Ethernet.begin(myMAC, IPAddress(myIP));
    udp.begin(rcvPort);

    for(int i=0; i<sizeof(sndBuffer); i++)
    {
        sndBuffer[i] = i;        // just to see something in Wireshark;
    }
}

void loop()
{
    udp.beginPacket(IPAddress(sndIP), sndPort);
    udp.write((byte *)sndBuffer, sizeof(sndBuffer));
    udp.endPacket();

    Serial.println("Packet Sent");

   int packetSize = udp.parsePacket();

   if(packetSize > 0)
       Serial.println("Something Received");
}
