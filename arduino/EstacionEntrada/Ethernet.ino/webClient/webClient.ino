#include <EtherCard.h>
#define LED 11 //led del teensy 2.0

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;
const int RESET = 12; //Hardware reset para el ESP8266
const char website[] PROGMEM = "10.20.184.70";

void setup () {
  pinMode(RESET,OUTPUT); //Teensy con ESP8266
  reset();               //Teensy con ESP8266
  pinMode(LED,OUTPUT);   //Teensy
  Serial.begin(57600);
  Serial.println(F("\n[webClient]"));

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, 8) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  

  // or provide a numeric IP address instead of a string
  //byte hisip[] = { 10,20,184,70 };
  ether.hisip[0] = 10;
  ether.hisip[1] = 20;
  ether.hisip[2] = 184;
  ether.hisip[3] = 70;

  ether.printIp("SRV: ", ether.hisip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 5000;
    ether.browseUrl(PSTR("/standby.php"), "", website, my_callback);
    Serial.println("Sending a request...");
  }
}
// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}
void reset()
{
  digitalWrite(RESET,LOW);
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(RESET,HIGH);
  digitalWrite(LED,LOW);
}
